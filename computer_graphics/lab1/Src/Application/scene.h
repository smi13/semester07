#ifndef _scene_h
#define _scene_h

#include <algorithm>
#include <vector>

#include "object.h"

struct IDirect3DDevice9;

namespace cg_labs
{
   namespace Renderer
   {
      template<typename T>
      static void renderScene( T *scene )
      {
         std::for_each(scene->_objects.begin(), scene->_objects.end(), renderObject<Object>);
      }
   }

   class Scene
   {
   public:

      Scene();

      Scene &operator<<( Object *new_object );

      ~Scene();

      friend void Renderer::renderScene( Scene *scene );

   private:
      std::vector<Object *> _objects;
   };
}


#endif /* _scene_h */