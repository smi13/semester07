#ifndef _scene_h
#define _scene_h

#include <algorithm>
#include <map>
#include <string>

#include "object.h"
#include "light.h"
#include "renderer.h"

namespace cg_labs
{
   typedef std::map<std::string, Object *> ObjectToNameMap;
   typedef std::map<std::string, Light *> LightToNameMap;
        
   class Scene
   {
   public:

      Scene();

      Scene &operator<<( Object *new_object );
      Scene &operator<<( Light *new_light );

      Object *getObject( std::string &name );
      Object *getObject( const char *name );

      Light *getLight( std::string &name );
      Light *getLight( const char *name );

      ~Scene();

      friend void Renderer::render( Scene &scene );
      friend void Renderer::lightUp( Scene &scene );

   private:
      
      ObjectToNameMap _objects;
      LightToNameMap _lights;
   };
}


#endif /* _scene_h */