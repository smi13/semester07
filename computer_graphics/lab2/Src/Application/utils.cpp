#include <windows.h>
#include <d3dx9.h>

#define _USE_MATH_DEFINES
#include <cmath>

#include "render_context.h"
#include "utils.h"

using namespace cg_labs;

void utils::toggleWireFrame()
{
   if (getFillMode() == D3DFILL_WIREFRAME)
   {
      getDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
      setFillMode(D3DFILL_SOLID);
   }
   else
   {
      getDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
      setFillMode(D3DFILL_WIREFRAME);
   }
}

void utils::toggleFullScreen()
{
   static int old_width = getWindowWidth(), 
      old_height = getWindowHeight();
   static bool full_screen = false;
   static WINDOWPLACEMENT wpc;
   HWND hWnd = getWindowHandle();

   if (!full_screen)
   {

      GetWindowPlacement(hWnd, &wpc);
      SetWindowLong(hWnd, GWL_STYLE,WS_POPUP);
      SetWindowLong(hWnd, GWL_EXSTYLE,WS_EX_TOPMOST);
      ShowWindow(hWnd, SW_SHOWMAXIMIZED);
      updateWindowSize(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
      full_screen = true;
   }
   else
   {
      SetWindowLong(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
      SetWindowLong(hWnd, GWL_EXSTYLE, 0L);
      SetWindowPlacement(hWnd, &wpc);
      ShowWindow(hWnd, SW_SHOWDEFAULT);
      updateWindowSize(old_width, old_height);
      full_screen = false;
   }
}

D3DXVECTOR3 utils::spherticToCartesian( float phi, float theta, float r )
{
   D3DXVECTOR3 res(r * cosf(theta) * cosf(phi),
                   r * sinf(theta),
                   r * cosf(theta) * sinf(phi));
   return res;
}

void utils::cartesianToSpheric( const D3DXVECTOR3 &cart, float &r, 
                                      float &theta, float &phi )
{
   float x = cart.x, y = cart.y, z = cart.z;

   r = sqrtf(x * x + y * y + z * z);
   theta = atanf(y / sqrtf(x * x + z * z));
   phi = atanf(z / x);

   if (z > 0 && x < 0)
      phi += (float)M_PI;

   if (z < 0 && x < 0)
      phi += (float)M_PI;

   if (z < 0 && x > 0)
      phi += 2.0f * (float)M_PI;
}

void utils::TextRenderer::init()
{
   D3DXCreateFont(getDevice(), 15, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
      OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
      "Arial", &m_pFont9);

   D3DXCreateSprite(getDevice(), &m_pSprite9);

   m_nLineHeight = 15;
}

void utils::TextRenderer::setInsertionPos( int x, int y )
{
   m_pt.x = x; m_pt.y = y;
}

void utils::TextRenderer::setForegroundColor( D3DXCOLOR clr )
{
   m_clr = clr;
}

void utils::TextRenderer::drawTextLine( const char *str )
{
   HRESULT hr;
   RECT rc;
   SetRect( &rc, m_pt.x, m_pt.y, 0, 0 );
   if( m_pFont9 )
      hr = m_pFont9->DrawText(m_pSprite9, str, -1, &rc, DT_NOCLIP, m_clr);

   m_pt.y += m_nLineHeight;
}

void utils::TextRenderer::begin()
{
   m_pSprite9->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
}

void utils::TextRenderer::end()
{
   m_pSprite9->End();
}

utils::TextRenderer::~TextRenderer()
{
   m_pSprite9->Release();
   m_pFont9->Release();
}