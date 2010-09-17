#include <windows.h>
#include <d3d9.h>

#include "Library/cglD3D.h"
#include "lab1_app.h"
#include "comdef.h"

using namespace cg_labs;

lab1App::lab1App( int nW, int nH, void* hInst, int nCmdShow ) : cglApp(nW, nH, hInst, nCmdShow)
{
   SetWindowText((HWND)m_hWnd, getWindowText());

   m_nClearColor = 0xFF000000;

   _device = m_pD3D->getDevice();
}

bool lab1App::processInput( unsigned int nMsg, int wParam, long lParam )
{
   if (cglApp::processInput(nMsg, wParam, lParam))
      return true;

   return false;
}

void lab1App::renderInternal()
{
   IDirect3DVertexBuffer9 *pVB;

   _device->CreateVertexBuffer(
      4*sizeof(Vertex),   
      D3DUSAGE_WRITEONLY, 
      0,               
      D3DPOOL_DEFAULT,  
      &pVB,             
      NULL);            

   Vertex *pVtx;

   HRESULT hRes = pVB->Lock(0, 0, (void **)&pVtx, 0);       

   if (hRes == D3D_OK)
   {
      for (int i = 0; i < 4; i++)
         ;

      pVB->Unlock();
   }

   pVB->Release();
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

