#include <d3dx9.h>

#include <algorithm>

#include "lab1_app.h"
#include "utils.h"
#include "render_context.h"

using namespace cg_labs;

const float sensitivity = 0.005f;

bool lab1App::processInput( unsigned int nMsg, int wParam, long lParam )
{
   static int mouseX, mouseY; 

   switch (nMsg)
   {
   case WM_MOUSEWHEEL:
      {
         if (isMouseLButton())
         {
            int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
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
            _camera.increasePhi((x - mouseX) * sensitivity);

            int delta_y = y - mouseY;

            delta_y < 0 ? _camera.increaseTheta(-delta_y * sensitivity) :
                          _camera.decreaseTheta(delta_y * sensitivity);
            
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
         // Save flags for continuous controls
         if (wParam < MAX_KEYS)
            _keysPressed[wParam] = false;
         // Process switch controls
         switch (wParam)
         {
         case '1': /* do something */ break;
         case '2': /* do something */ break;
         case '3': /* do something */ break;
         }
         break;
      }
   }   

   return cglApp::processInput(nMsg, wParam, lParam);
}