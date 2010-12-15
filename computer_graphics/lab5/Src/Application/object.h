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

      Object( std::string &name );

      virtual D3DPRIMITIVETYPE getPrimitiveType() = 0;
      std::string &getName();

      virtual void translate( float x, float y, float z );
      virtual void rotateX( float angle );
      virtual void rotateY( float angle );
      virtual void rotateZ( float angle );
      virtual void scale( float scl );
      virtual void scale( float scl_x, float scl_y, float scl_z );

      void setLighting( bool value );
      void setVisible( bool value );
      bool isVisible();

      D3DXMATRIX world() { return _matrix; }

      void setIdentity();

      virtual void render();

      virtual void clear();
      virtual ~Object() ;

   protected:

      int _verticesCount, _indicesCount, _primitivesCount; 
      bool _toRender, _isLightenUp;
      std::string _name;
      IDirect3DVertexBuffer9 *_vbuf;
      IDirect3DIndexBuffer9 *_ibuf;
      D3DXMATRIX _matrix;
   };
}


#endif /* _object_h */