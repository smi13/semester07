#ifndef _lab2_app_h
#define _lab2_app_h

#include <d3dx9.h>

#include "Library/cglApp.h"

#include "scene.h"
#include "camera.h"
#include "spheric_camera.h"
#include "free_camera.h"
#include "input_processor.h"
#include "utils.h"

namespace cg_labs
{
   class lab2App : public cglApp
   {
   public:

      lab2App( int nW, int nH, void *hInst, int nCmdShow ); 

      bool processInput( unsigned int nMsg, int wParam, long lParam );

      ~lab2App();

      friend class InputProcessor<lab2App>;

   protected:

      void renderInternal();
      void update();

      char const *getWindowText();

   private:      

      bool _keysPressed[MAX_KEYS];

      Scene _scene;
      SphericCamera _sphericCamera;
      FreeCamera _freeCamera;
      Camera *_camera;

      utils::TextRenderer tr;
      InputProcessor<lab2App> _inputProc;
   };
}


#endif /* _lab2_app_h */