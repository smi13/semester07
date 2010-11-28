#include <windows.h>
#include <d3dx9.h>

#include "Library/cglD3D.h"

#include "lab1_app.h"
#include "comdef.h"
#include "axes.h"
#include "render_context.h"

using namespace cg_labs;

const float s_rMouseWheel2Zoom = 0.05f;

lab1App::lab1App( int nW, int nH, void *hInst, int nCmdShow ) : 
   cglApp(nW, nH, hInst, nCmdShow), _camera(DEG2RAD(10), DEG2RAD(10), 5.0f)
{
   setDevice(m_pD3D->getDevice());
   float wh_ratio = (float)GetSystemMetrics(SM_CXSCREEN) / GetSystemMetrics(SM_CYSCREEN);

   D3DXMATRIX matProj;
   D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, wh_ratio, 1.0f, 100.0f);

   // Some rendering settings. Specific for Lab1, though.
   m_pD3D->getDevice()->SetTransform(D3DTS_PROJECTION, &matProj);
   m_pD3D->getDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);   
   m_pD3D->getDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
   m_pD3D->getDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

   SetWindowText((HWND)m_hWnd, getWindowText());

   m_nClearColor = D3DCOLOR_XRGB(0, 0, 0);

   // Constructing the scene

   _scene << new Axes(std::string("axes-0"), 0.0f, 0.0f, 0.0f, 5.0f);
          //<< new Cube(0.0f, 0.0f, 0.0f, 5.0f);
   
   _zdepth = -5.0f;
}

bool lab1App::processInput( unsigned int nMsg, int wParam, long lParam )
{
   switch (nMsg)
   {
      case WM_MOUSEWHEEL:
      {
         if (LOWORD(wParam) == MK_LBUTTON)
         {
            int zDelta = (int)((signed short)(HIWORD(wParam)));
            _camera.increaseR(zDelta * s_rMouseWheel2Zoom);

            break;
         }
      }
      case WM_MOUSEMOVE:
      {
         if (LOWORD(wParam) == MK_LBUTTON)
         {
            _camera.increasePhi(0.1);

         }
      }
   }

   _camera.buildMatrix();

   return cglApp::processInput(nMsg, wParam, lParam);
}

void lab1App::renderInternal()
{
   D3DXMATRIX matWorld;
   D3DXMatrixIdentity(&matWorld);

   getDevice()->SetTransform(D3DTS_WORLD, &matWorld);
   getDevice()->SetTransform(D3DTS_VIEW, _camera.getMatrix());

   Renderer::renderScene(&_scene);
}

void lab1App::update()
{
   cglApp::update();
}

char const * lab1App::getWindowText()
{
   return "CG Lab 1. Fedor Zentsev, 4057/2";
}

lab1App::~lab1App()
{
}