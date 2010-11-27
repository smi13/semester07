#ifndef _renderer_h
#define _renderer_h

#include <algorithm>

#include "comdef.h"
#include "render_context.h"
#include "scene.h"

namespace cg_labs
{
   /*namespace Renderer
   {
      template<typename T>
      static void renderObject( T *obj )
      {
         getDevice()->SetStreamSource(0, obj->_vbuf, 0, sizeof(Vertex));
         getDevice()->SetFVF(VertexFormat);
         getDevice()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
      }

      template<typename T>
      static void renderScene( T *scene )
      {
         std::for_each(scene->_objects.begin(), scene->_objects.end(), renderObject);
      }
   }*/
}


#endif /* _renderer_h */