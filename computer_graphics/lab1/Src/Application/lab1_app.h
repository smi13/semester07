#ifndef _lab1_app_h
#define _lab1_app_h

#include "Library/cglApp.h"

#include "scene.h"
#include "spheric_camera.h"

struct IDirect3DDevice9;
struct IDirect3DVertexBuffer9; 
struct IDirect3DIndexBuffer9; 

namespace cg_labs
{
   class lab1App : public cglApp
   {
   public:

      lab1App( int nW, int nH, void *hInst, int nCmdShow ); 

      bool processInput( unsigned int nMsg, int wParam, long lParam );
      
      ~lab1App();

   protected:

      void renderInternal();
      void update();

      char const *getWindowText();

   private:

      float _zdepth;

      Scene _scene;
      SphericCamera _camera;
   };
}


#endif /* _lab1_app_h */