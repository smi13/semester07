#ifndef _material_h
#define _material_h

#include <d3dx9.h>

namespace cg_labs
{
   struct Material
   {
      Material();

      Material( D3DXCOLOR amb, D3DXCOLOR spec, D3DXCOLOR dif );

      operator D3DMATERIAL9();

      D3DXCOLOR Ambient, Specular, Diffuse;
   };
}

#endif /* _material_h */