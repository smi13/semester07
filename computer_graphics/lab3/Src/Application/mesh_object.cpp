#include <d3dx9.h>
#include <string>

#include "comdef.h"
#include "mesh_object.h"
#include "render_context.h"

using namespace cg_labs;

MeshObject::MeshObject( const char *name, const char *path, 
                       const char *file_name, std::vector<std::string> *buf, bool lighten ) : 
   Object(std::string(name))
{
   ID3DXBuffer *pMat = NULL;

   _isLightenUp = lighten;

   _mesh = 0;
   _materials = 0;
   _textures = 0;

   std::string full_name = std::string(path) + std::string("\\") + std::string(file_name);

   HRESULT hr = D3DXLoadMeshFromX(full_name.c_str(), D3DXMESH_SYSTEMMEM, getDevice(),
      NULL, &pMat, NULL, &_numMaterials, &_mesh);

   if (SUCCEEDED(hr))
   {
      D3DXMATERIAL* pD3DXMaterials=(D3DXMATERIAL*)pMat->GetBufferPointer();

      _materials = new D3DMATERIAL9[_numMaterials];
      _textures = new LPDIRECT3DTEXTURE9[_numMaterials];

      for (DWORD i = 0; i < _numMaterials; ++i)
      {
         _materials[i] = pD3DXMaterials[i].MatD3D;
         _materials[i].Ambient = _materials[i].Diffuse;

         if (buf == 0)
         {
            if (pD3DXMaterials[i].pTextureFilename != 0)
            {
               std::string full_tex_name = std::string(path) + 
                  "\\" + std::string(pD3DXMaterials[i].pTextureFilename);
               hr = D3DXCreateTextureFromFile(getDevice(), 
                     full_tex_name.c_str(), &(_textures[i]));

               if (FAILED(hr))
                  _textures[i] = 0;
               else
               {
                  if (buf != 0)
                  {

                  }
               }
            }
            else
               _textures[i] = 0;
         }
         else
         {
            int j = 0;
            getDevice()->CreateTexture(256, 256, buf->size(), 0, D3DFMT_X8R8G8B8, 
               D3DPOOL_DEFAULT, &_textures[i], NULL);

            for (std::vector<std::string>::iterator it = buf->begin(); 
               it != buf->end(); ++it)
            {
               (*it) = std::string(path) + 
                  "\\" + std::string(it->c_str());

               IDirect3DSurface9 *surface;
               _textures[i]->GetSurfaceLevel(j++, &surface);

               if (FAILED(D3DXLoadSurfaceFromFile(surface, NULL, NULL, it->c_str(), 
                  NULL, D3DX_DEFAULT, 0, NULL)))
                  _textures[i]->Release();

               surface->Release();
            }
         }
      }

      if (pMat)
         pMat->Release();

      _mesh->OptimizeInplace(D3DXMESHOPT_COMPACT |
         D3DXMESHOPT_ATTRSORT, NULL, NULL, NULL, NULL);
   }
}

D3DPRIMITIVETYPE MeshObject::getPrimitiveType()
{
   return D3DPRIMITIVETYPE(-1);
}

void MeshObject::render()
{
   if (isVisible())
   {
      D3DMATERIAL9 tmp;
      IDirect3DBaseTexture9 *tmp_tex;
      getDevice()->GetMaterial(&tmp);
      getDevice()->GetTexture(0, &tmp_tex);

      if (_isLightenUp)
         getDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
      else
         getDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);

      Object::render();

      for (UINT i = 0; i < _numMaterials; i++)
      {
         if (_textures[i] != 0)
         {
            if (isTexturesEnabled())
               getDevice()->SetTexture(0, _textures[i]);
         }
         
         getDevice()->SetMaterial(&(_materials[i]));
         _mesh->DrawSubset(i);
      }

      getDevice()->SetTexture(0, tmp_tex);
      getDevice()->SetMaterial(&tmp);
   }
}

void MeshObject::clear()
{
   for (int i = 0; i != _numMaterials; i++)
   {
      if (_textures[i] != 0)
      {
         _textures[i]->Release();
         _textures[i] = 0;
      }
   }

   if (_textures != 0)
   {
      delete[] _textures;
      _textures = 0;
   }

   if (_materials != 0)
   {
      delete[] _materials;
      _materials = 0;
   }
   
   if (_mesh != 0)
      _mesh->Release();
}

MeshObject::~MeshObject()
{
   clear();
}

