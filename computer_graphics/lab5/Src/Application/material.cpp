#include "material.h"

using namespace cg_labs;

Material::Material()
{
   Diffuse = D3DCOLOR_XRGB(255, 255, 0);
   Ambient = D3DCOLOR_XRGB(255, 255, 255);
   Specular = D3DCOLOR_XRGB(255, 255, 255);
}

Material::Material( D3DXCOLOR amb, D3DXCOLOR spec, D3DXCOLOR dif )
{
   Ambient = amb;
   Specular = spec;
   Diffuse = dif;
}

Material::operator D3DMATERIAL9()
{
   D3DMATERIAL9 mat;

   ZeroMemory(&mat, sizeof(D3DMATERIAL9));
   mat.Ambient = Ambient;
   mat.Diffuse = Diffuse;
   mat.Specular = Specular;

   return mat;
}
