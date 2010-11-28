#ifndef _object_h
#define _object_h

#include <d3dx9.h>

#include <string>

namespace cg_labs
{  
   namespace Renderer
   {
      template<typename T>
      static void renderObject( T *obj )
      {
         getDevice()->SetStreamSource(0, obj->_vbuf, 0, sizeof(Vertex));
         getDevice()->SetFVF(VertexFormat);
         getDevice()->DrawPrimitive(obj->getPrimitiveType(), 0, obj->_primitivesCount);
      }
   }

   class Object
   {
   public:

      Object( std::string &name ) : _vbuf(0), _name(name) {}

      virtual D3DPRIMITIVETYPE getPrimitiveType() = 0;
      std::string &getName() { return _name; }

      virtual ~Object() { _vbuf->Release(); }

      friend void Renderer::renderObject( Object *obj );

   protected:

      int _verticesCount, _primitivesCount; 
      std::string _name;
      IDirect3DVertexBuffer9 *_vbuf;
   private:
      Object();
   };
}


#endif /* _object_h */