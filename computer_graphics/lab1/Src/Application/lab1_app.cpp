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
   cglApp(nW, nH, hInst, nCmdShow)
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

   _scene << new Axes(0.0f, 0.0f, 0.0f, 5.0f);
          //<< new Cube(0.0f, 0.0f, 0.0f, 5.0f);
   
   _zdepth = -5.0f;
}

bool lab1App::processInput( unsigned int nMsg, int wParam, long lParam )
{
   switch (nMsg)
   {
      case WM_MOUSEWHEEL:
      {
         int zDelta = (int)((signed short)(HIWORD(wParam)));
         _zdepth += zDelta * s_rMouseWheel2Zoom;
         break;
      }
   }

   return cglApp::processInput(nMsg, wParam, lParam);
}

void lab1App::renderInternal()
{
   D3DXMATRIX matWorld;

   UINT iTime = timeGetTime() % 1000;
   FLOAT fAngle = iTime * (2.0f * D3DX_PI) / 1000.0f;
   D3DXMatrixRotationY( &matWorld, 1.0 );

   D3DXMatrixIdentity(&matWorld);
   getDevice()->SetTransform(D3DTS_WORLD, &matWorld);

   D3DXVECTOR3 vEyePt( 1.0f, 1.0f, -5.0f );
   D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
   D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
   D3DXMATRIXA16 matView;
   D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
   
   getDevice()->SetTransform(D3DTS_VIEW, &matView);

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