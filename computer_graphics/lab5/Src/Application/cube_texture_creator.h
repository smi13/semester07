#ifndef _cube_texture_creator_h
#define _cube_texture_creator_h

#include "scene.h"

namespace cg_labs
{
   class CubeTextureCreator
   {
   public:
      static void create( IDirect3DCubeTexture9 **tex, Scene &scene );
   };
}


#endif /* _cube_texture_creator_h */