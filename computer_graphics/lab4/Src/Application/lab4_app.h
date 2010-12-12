#ifndef _lab2_app_h
#define _lab2_app_h

#include <d3dx9.h>

#include "Library/cglApp.h"

#include "complex_objects.h"
#include "scene.h"
#include "camera.h"
#include "spheric_camera.h"
#include "free_camera.h"
#include "input_processor.h"
#include "utils.h"

namespace cg_labs
{
   class lab3App : public cglApp
   {
   public:

      lab3App( int nW, int nH, void *hInst, int nCmdShow ); 

      bool processInput( unsigned int nMsg, int wParam, long lParam );

      ~lab3App();

      friend class InputProcessor<lab3App>;

   protected:

      void renderInternal();
      void update();

      char const *getWindowText();

   private:      

      void _renderText();

      bool _keysPressed[MAX_KEYS];

      Scene _scene;
      
      SphericCamera _sphericCamera;
      FreeCamera _freeCamera;
      Camera *_camera;

      complex_objects::Flower _flower;

      utils::TextRenderer tr1, tr2;
      InputProcessor<lab3App> _inputProc;
   };
}


#endif /* _lab2_app_h */