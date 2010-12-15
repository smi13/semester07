#include <d3dx9.h>

#include <algorithm>

#include "lab2_app.h"
#include "utils.h"
#include "render_context.h"

using namespace cg_labs;



bool lab2App::processInput( unsigned int nMsg, int wParam, long lParam )
{
   static int mouseX, mouseY; 

   switch (nMsg)
   {
   case WM_MOUSEWHEEL:
      {
         if (isMouseLButton())
         {
            int zDelta = (int)((signed short)(HIWORD(wParam)));
            _camera.zoom(-zDelta);
         }
         break;
      }
   case WM_LBUTTONDOWN:
      {
         mouseX = LOWORD(lParam);
         mouseY = HIWORD(lParam);
         ShowCursor(false);
         setMouseLButton(true);
         break;
      }
   case WM_LBUTTONUP:
      {
         ShowCursor(true);
         setMouseLButton(false);
         break;
      }
   case WM_MOUSEMOVE:
      {
         int x = LOWORD(lParam), y = HIWORD(lParam);

         if (isMouseLButton())
         {
            _camera.rotateX((x - mouseX) * sensitivity);
            _camera.rotateY((y - mouseY) * sensitivity);

            _camera.buildMatrix();
         }
         mouseX = x;
         mouseY = y;

         break;
      }
   case WM_KEYDOWN:
      {
         // Save flags for continuous controls
         if (wParam < MAX_KEYS)
            _keysPressed[wParam] = true;

         if (wParam == VK_SPACE)
            utils::toggleWireFrame();

         if (wParam == VK_RETURN)
            utils::toggleFullScreen();

         break;
      }

   case WM_KEYUP:
      {
         if (wParam < MAX_KEYS)
            _keysPressed[wParam] = false;
         break;
      }
   }   

   return cglApp::processInput(nMsg, wParam, lParam);
}