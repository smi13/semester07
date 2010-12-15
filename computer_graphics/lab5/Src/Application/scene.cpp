#include <d3dx9.h>

#include "scene.h"

using namespace cg_labs;

void Renderer::render( Scene &scene )
{
   for (ObjectToNameMap::iterator it = scene._objects.begin(); it != scene._objects.end(); ++it)
      it->second->render();

   for (LightToNameMap::iterator it = scene._lights.begin(); it != scene._lights.end(); ++it)
   {
      Object *obj = it->second->getObject();

      if (obj != 0)
         obj->render();
   }
}

void Renderer::lightUp( Scene &scene )
{
   for (LightToNameMap::iterator it = scene._lights.begin(); it != scene._lights.end(); ++it)
      it->second->set();
}

Scene::Scene() 
{
}

Scene &Scene::operator<<( Object *new_object )
{
   _objects.insert(std::make_pair(new_object->getName(), new_object));

   return *this;
}

Scene &Scene::operator<<( Light *new_light )
{
   _lights.insert(std::make_pair(new_light->getName(), new_light));

   return *this;
}

Object * Scene::getObject( std::string &name )
{
   ObjectToNameMap::iterator it = _objects.find(name);

   if (it == _objects.end())
      return 0;

   return it->second;
}

Object * Scene::getObject( const char *name )
{
   return getObject(std::string(name));
}

Light * Scene::getLight( std::string &name )
{
   LightToNameMap::iterator it = _lights.find(name);

   if (it == _lights.end())
      return 0;

   return it->second;
}

Light * Scene::getLight( const char *name )
{
   return getLight(std::string(name));
}

Scene::~Scene()
{
   for (ObjectToNameMap::iterator it = _objects.begin(); it != _objects.end(); ++it)
   {
      delete it->second;
   }

   for (LightToNameMap::iterator it = _lights.begin(); it != _lights.end(); ++it)
   {
      delete it->second;
   }
}