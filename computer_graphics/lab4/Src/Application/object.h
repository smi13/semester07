#ifndef _object_h
#define _object_h

#include <d3dx9.h>

#include <string>

#include "comdef.h"
#include "renderer.h"

namespace cg_labs
{  
   class Object
   {
   public:

      Object();
      Object( std::string &name, bool world_dependent = false );

      virtual D3DPRIMITIVETYPE getPrimitiveType() = 0;
      std::string &getName();

      void translate( float x, float y, float z );
      void rotateX( float angle );
      void rotateY( float angle );
      void rotateZ( float angle );
      void scale( float scl );
      void scale( float scl_x, float scl_y, float scl_z );

      void setWorldDependent( bool value );
      void setLighting( bool value );
      void setVisible( bool value );
      void setName( const char *name );
      bool isVisible();

      void setIdentity();

      virtual void render();

      virtual void clear();
      virtual ~Object() ;

   protected:

      int _verticesCount, _indicesCount, _primitivesCount; 
      bool _toRender, _isLightenUp, _worldDependent;
      std::string _name;
      IDirect3DVertexBuffer9 *_vbuf;
      IDirect3DIndexBuffer9 *_ibuf;
      D3DXMATRIX _matrix;

   private:

   };
}


#endif /* _object_h */