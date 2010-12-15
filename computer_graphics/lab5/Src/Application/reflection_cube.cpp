#include <d3dx9.h>
#include <vector>

#include "comdef.h"
#include "reflection_cube.h"
#include "grid.h"
#include "render_context.h"
#include "shader.h"

using namespace cg_labs;

ReflectionCube::ReflectionCube( const char *name, float a, const char *path, 
               const char *tex_name, const char *cube_tex_name, int n ) : 
               Object(std::string(name))
{
   _grids.resize(6);
   _grids[0] = new Grid("grid1", grid_functions::plane, grid_functions::planeNormal, 
      n, n, 0, 0);
   _grids[1] = new Grid("grid2", grid_functions::plane, grid_functions::planeNormal, 
      n, n, 0, 1);
   _grids[2] = new Grid("grid3", grid_functions::plane, grid_functions::planeNormal, 
      n, n, 0, 2);
   _grids[3] = new Grid("grid4", grid_functions::plane, grid_functions::planeNormal, 
      n, n, 0, 3);
   _grids[4] = new Grid("grid5", grid_functions::plane, grid_functions::planeNormal, 
      n, n, 0, 4);
   _grids[5] = new Grid("grid6", grid_functions::plane, grid_functions::planeNormal, 
      n, n, 0, 5);

   for (int i = 0; i != _grids.size(); i++)
   {
      _grids[i]->scale(a);
      _grids[i]->translate(-a / 2, 0.0f, -a / 2);
   }

   _grids[1]->translate(-a / 2, 0.0f, 0.0f);
   _grids[1]->rotateZ(D3DXToRadian(-90));
   _grids[1]->translate(a / 2, 0.0f, 0.0f);

   _grids[2]->translate(a / 2, 0.0f, 0.0f);
   _grids[2]->rotateZ(D3DXToRadian(90));
   _grids[2]->translate(-a / 2, 0.0f, 0.0f);

   _grids[3]->translate(0.0f, 0.0f, a / 2);
   _grids[3]->rotateX(D3DXToRadian(-90));
   _grids[3]->translate(0.0f, 0.0f, -a / 2);

   _grids[4]->translate(0.0f, 0.0f, -a / 2);
   _grids[4]->rotateX(D3DXToRadian(90));
   _grids[4]->translate(0.0f, 0.0f, a / 2);

   _grids[5]->translate(0.0f, a, 0.0f);

   HRESULT hr = D3DXCreateTextureFromFile(getDevice(),
      (std::string(path) + "//" + std::string(tex_name)).c_str(),
      &_tex);

   hr = D3DXCreateCubeTextureFromFileA(getDevice(),
      (std::string(path) + "//" + std::string(cube_tex_name)).c_str(),
      &_cubeTex);
}

D3DPRIMITIVETYPE ReflectionCube::getPrimitiveType()
{
   return D3DPT_TRIANGLELIST;
}

void ReflectionCube::render()
{
   if (isVisible())
   {
      D3DMATERIAL9 tmp;
      IDirect3DBaseTexture9 *tmp_tex0, *tmp_tex1;
      getDevice()->GetMaterial(&tmp);
      getDevice()->GetTexture(0, &tmp_tex0);
      getDevice()->GetTexture(1, &tmp_tex1);
      //
      if (_isLightenUp)
         getDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
      else
         getDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);

      getDevice()->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
      //getDevice()->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE ); // Modulate...
      //getDevice()->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );   // the texture for this stage with...
      //getDevice()->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );   // the diffuse color of the geometry.

      getDevice()->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 1);
      //getDevice()->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE ); // Modulate...
      //getDevice()->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE); // the texture for this stage with...
      //getDevice()->SetTextureStageState( 1, D3DTSS_COLORARG2, D3DTA_CURRENT ); // the current argument passed down from stage 0

      getDevice()->SetTexture(0, _cubeTex);
      getDevice()->SetTexture(1, _tex);    

      for (int i = 0; i != _grids.size(); i++)
         _grids[i]->render();

      getDevice()->SetMaterial(&tmp);
      getDevice()->SetTexture(0, tmp_tex0);
      getDevice()->SetTexture(1, tmp_tex1);
   }
}

void ReflectionCube::translate( float x, float y, float z )
{
   for (int i = 0; i != _grids.size(); i++)
      _grids[i]->translate(x, y, z);
}

void ReflectionCube::rotateX( float angle )
{
   for (int i = 0; i != _grids.size(); i++)
      _grids[i]->rotateX(angle);
}

void ReflectionCube::rotateY( float angle )
{
   for (int i = 0; i != _grids.size(); i++)
      _grids[i]->rotateY(angle);
}

void ReflectionCube::rotateZ( float angle )
{
   for (int i = 0; i != _grids.size(); i++)
      _grids[i]->rotateZ(angle);
}

void ReflectionCube::scale( float scl )
{
   for (int i = 0; i != _grids.size(); i++)
      _grids[i]->scale(scl);
}

void ReflectionCube::scale( float scl_x, float scl_y, float scl_z )
{
   for (int i = 0; i != _grids.size(); i++)
      _grids[i]->scale(scl_x, scl_y, scl_z);   
}

ReflectionCube::~ReflectionCube()
{
   for (int i = 0; i != _grids.size(); i++)
      delete _grids[i];
   _grids.clear();

   _cubeTex->Release();
   _tex->Release();
}
