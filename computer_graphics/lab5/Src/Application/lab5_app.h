#ifndef _lab2_app_h
#define _lab2_app_h

#include <d3dx9.h>

#include "Library/cglApp.h"

#include "shader.h"
#include "mesh_object.h"
#include "scene.h"
#include "camera.h"
#include "spheric_camera.h"
#include "free_camera.h"
#include "input_processor.h"
#include "utils.h"

namespace cg_labs
{
   class lab5app : public cglApp
   {
   public:

      lab5app( int nW, int nH, void *hInst, int nCmdShow ); 

      bool processInput( unsigned int nMsg, int wParam, long lParam );

      ~lab5app();

      friend class InputProcessor<lab5app>;

   protected:

      void renderInternal();
      void update();

      char const *getWindowText();

   private:      

      void _renderText();
      void _renderEnvMesh( D3DXMATRIX &proj );

      bool _keysPressed[MAX_KEYS];

      Scene _scene;
      SphericCamera _sphericCamera;
      FreeCamera _freeCamera;
      Camera *_camera;
      Shader _shader;

      ID3DXMesh *_mesh;
      DWORD _numMaterials;      

      IDirect3DTexture9 *_meshTex;
      IDirect3DCubeTexture9 *_envTex;

      utils::TextRenderer tr1, tr2;
      InputProcessor<lab5app> _inputProc;
   };
}


#endif /* _lab2_app_h */