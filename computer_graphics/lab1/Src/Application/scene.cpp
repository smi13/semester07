#include <d3dx9.h>

#include "scene.h"

using namespace cg_labs;

Scene::Scene() 
{
}

Scene &Scene::operator<<( Object *new_object )
{
   _objects.insert(std::make_pair(new_object->getName(), new_object));

   return *this;
}

Object * cg_labs::Scene::getObject( std::string &name )
{
   ObjectToNameMap::iterator it = _objects.find(name);

   if (it == _objects.end())
      return 0;

   return it->second;
}

Scene::~Scene()
{
   for (ObjectToNameMap::iterator it = _objects.begin(); it != _objects.end(); ++it)
   {
      delete it->second;
   }
}