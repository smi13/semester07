#include <windows.h>
#include <d3dx9.h>

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