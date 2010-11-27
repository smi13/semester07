#include <d3dx9.h>

#include "scene.h"

using namespace cg_labs;

Scene::Scene() 
{
}

Scene &Scene::operator<<( Object *new_object )
{
   _objects.push_back(new_object);

   return *this;
}

Scene::~Scene()
{
   for (std::vector<Object *>::iterator it = _objects.begin(); it != _objects.end(); ++it)
   {
      delete *it;
   }
}