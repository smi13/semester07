#ifndef _scene_h
#define _scene_h

#include <algorithm>
#include <map>
#include <string>

#include "object.h"

struct IDirect3DDevice9;

namespace cg_labs
{
   typedef std::map<std::string, Object *> ObjectToNameMap;

   namespace Renderer
   {
      template<typename T>
      static void renderScene( T *scene )
      {
         for (ObjectToNameMap::iterator it = scene->_objects.begin(); it != scene->_objects.end(); ++it)
            renderObject(it->second);
      }
   }

   class Scene
   {
   public:

      Scene();

      Scene &operator<<( Object *new_object );

      Object *getObject( std::string &name );
      Object *getObject( const char *name );

      ~Scene();

      friend void Renderer::renderScene( Scene *scene );

   private:
      
      ObjectToNameMap _objects;
   };
}


#endif /* _scene_h */