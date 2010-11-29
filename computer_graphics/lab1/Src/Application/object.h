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
         if (obj->isVisible())
         {
            getDevice()->SetTransform(D3DTS_WORLD, &obj->_matrix);

            getDevice()->SetFVF(VertexFormat);
            getDevice()->SetStreamSource(0, obj->_vbuf, 0, sizeof(Vertex));
            
            if (obj->_ibuf != 0)
            {
               getDevice()->SetIndices(obj->_ibuf);
               getDevice()->DrawIndexedPrimitive(obj->getPrimitiveType(), 0, 0, obj->_verticesCount,
                  0, obj->_primitivesCount);
            }
            else
               getDevice()->DrawPrimitive(obj->getPrimitiveType(), 0, obj->_primitivesCount);
         }
      }
   }

   class Object
   {
   public:

      Object( std::string &name );

      virtual D3DPRIMITIVETYPE getPrimitiveType() = 0;
      std::string &getName();

      void translate( float x, float y, float z );
      void rotateX( float angle );
      void rotateY( float angle );
      void rotateZ( float angle );
      void scale( float scl );

      void setVisible( bool value );
      bool isVisible();

      void setIdentity();

      void clear();
      virtual ~Object() ;

      friend void Renderer::renderObject( Object *obj );

   protected:

      int _verticesCount, _indicesCount, _primitivesCount; 
      bool _toRender;
      std::string _name;
      IDirect3DVertexBuffer9 *_vbuf;
      IDirect3DIndexBuffer9 *_ibuf;
      D3DXMATRIX _matrix;

   private:
      Object();
   };
}


#endif /* _object_h */