#ifndef _mesh_object_h
#define _mesh_object_h

#include <d3dx9.h>
#include <string>
#include <vector>

#include "object.h"
#include "renderer.h"

namespace cg_labs
{
   class MeshObject : public Object
   {
   public:

      MeshObject( const char *name, const char *path, const char *file_name, 
         std::vector<std::string> *buf = 0, bool lighten = true );

      virtual D3DPRIMITIVETYPE getPrimitiveType();
      virtual void render();

      virtual void clear();

      virtual ~MeshObject();

   private:

      ID3DXMesh *_mesh;
      D3DMATERIAL9 *_materials;
      IDirect3DTexture9 **_textures;
      DWORD _numMaterials;
   };
}

#endif /* _mesh_object_h */