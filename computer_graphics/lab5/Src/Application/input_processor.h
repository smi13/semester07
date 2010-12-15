#ifndef _input_processor_h
#define _input_processor_h

#include <windows.h>

#include "render_context.h"
#include "constants.h"

#define CHANDLE_MSG(msg, func) \
   case msg: \
      func(app, wParam, lParam); \
   break;

namespace cg_labs
{
   enum
   {
      MAX_KEYS = 128
   };

   template<typename T>
   class InputProcessor
   {
   public:

      InputProcessor() : _mouseX(-1), _mouseY(-1) {}

      void handleMessage( T *app, int nMsg, int wParam, long lParam )
      {
         switch (nMsg)
         {
            CHANDLE_MSG(WM_MOUSEMOVE, _onMouseMove);
            CHANDLE_MSG(WM_MOUSEWHEEL, _onMouseWheel);
            CHANDLE_MSG(WM_LBUTTONDOWN, _onLButtonDown);
            CHANDLE_MSG(WM_LBUTTONUP, _onLButtonUp);
            CHANDLE_MSG(WM_KEYDOWN, _onKeyDown);
            CHANDLE_MSG(WM_KEYUP, _onKeyUp)
         }
      }

   private:

      void _onMouseMove( T *app, int wParam, long lParam )
      {
         int x = LOWORD(lParam), y = HIWORD(lParam);

         //if (isMouseLButton())
         //{
            if (_mouseX != -1 && _mouseY != -1)
            {
               float dx = (x - _mouseX) * constants::sensitivity,
                  dy = -(y - _mouseY) * constants::sensitivity;
               app->_camera->rotate(dx, dy);
            }
         //}

         _mouseX = x;
         _mouseY = y;
      }

      void _onMouseWheel( T *app, int wParam, long lParam )
      {
         int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);

         //if (isMouseLButton())
            app->_camera->move(0, -zDelta);

      }

      void _onLButtonDown( T *app, int wParam, long lParam )
      {
         //_mouseX = LOWORD(lParam);
         //_mouseY = HIWORD(lParam);
         //ShowCursor(false);
         setMouseLButton(true);
      }

      void _onLButtonUp( T *app, int wParam, long lParam )
      {
         //ShowCursor(true);
         setMouseLButton(false);
      }

      void _onKeyDown( T *app, int wParam, long lParam )
      {
         if (wParam < MAX_KEYS)
            app->_keysPressed[wParam] = true;

         if (wParam == VK_SPACE)
         {
            if (app->_camera == &app->_freeCamera)
            {
               app->_sphericCamera.convert(&app->_freeCamera);
               app->_camera = &app->_sphericCamera;
            }
            else
            {
               app->_freeCamera.convert(&app->_sphericCamera);
               app->_camera = &app->_freeCamera;
            }
         }

         if (wParam == VK_HOME)
            utils::toggleWireFrame();

         if (wParam == VK_RETURN)
            utils::toggleFullScreen();
         
         if (app->_keysPressed['U'])
            utils::toggleTextures();

         if (wParam == VK_F1)
            toggleF1();

         if (app->_keysPressed[VK_ADD] || app->_keysPressed[VK_OEM_PLUS])
            setFresnelPow(getFresnelPow() + 0.1f);

         if (app->_keysPressed[VK_SUBTRACT])
            setFresnelPow(getFresnelPow() - 0.1f);
      }

      void _onKeyUp( T *app, int wParam, long lParam )
      {
         if (wParam < MAX_KEYS)
            app->_keysPressed[wParam] = false;
      }

      int _mouseX, _mouseY;
   };
}


#endif /* _input_processor_h */