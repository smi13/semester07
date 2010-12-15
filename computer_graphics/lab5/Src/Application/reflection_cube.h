#ifndef _reflection_cube_h
#define _reflection_cube_h

#include <vector>

#include "object.h"
#include "mesh_object.h"
#include "grid.h"
#include "shader.h"

namespace cg_labs
{
   class ReflectionCube : public Object
   {
   public:
      ReflectionCube( const char *name, float a, const char *path, 
         const char *tex_name, const char *cube_tex_name, int n = 30 );

      virtual D3DPRIMITIVETYPE getPrimitiveType();

      virtual void translate( float x, float y, float z );
      virtual void rotateX( float angle );
      virtual void rotateY( float angle );
      virtual void rotateZ( float angle );
      virtual void scale( float scl );
      virtual void scale( float scl_x, float scl_y, float scl_z );

      virtual void render();

      virtual ~ReflectionCube();

      std::vector<Object *> _grids;
      IDirect3DTexture9 *_tex;
      IDirect3DCubeTexture9 *_cubeTex;

   private:

      int _n;
      
   };
}

#endif /* _reflection_cube_h */