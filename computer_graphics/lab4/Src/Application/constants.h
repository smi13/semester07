#include <d3dx9.h>

#include "material.h"

namespace cg_labs
{
   namespace constants
   {
      const float sensitivity = 0.005f;

      const D3DXCOLOR black = D3DCOLOR_ARGB(0, 0, 0, 0);
      const D3DXCOLOR white = D3DCOLOR_ARGB(0, 255, 255, 255);
      const D3DXCOLOR red = D3DCOLOR_ARGB(0, 255, 0, 0);
      const D3DXCOLOR green = D3DCOLOR_ARGB(0, 0, 255, 0);
      const D3DXCOLOR blue = D3DCOLOR_ARGB(0, 0, 0, 255);
      const D3DXCOLOR yellow = D3DCOLOR_ARGB(0, 255, 255, 0);
      const D3DXCOLOR magenta = D3DCOLOR_ARGB(0, 255, 0, 255);
      const D3DXCOLOR cyan = D3DCOLOR_ARGB(0, 0, 255, 255);
      const Material mat1 = Material(white, white, white);
      const Material mat2 = Material(green, green, green);
      const Material mat3 = Material(red, blue, green);
      const Material mat4 = Material(cyan, yellow, blue);

      const Material stem_mat = 
         Material(black, 
                  black, 
                  D3DXCOLOR(0.0f, 0.5f, 0.0f, 1.0f));
      const Material receptacle_mat = Material(red, blue, green);
      const Material petal_mat1 = 
         Material(D3DXCOLOR(0.1f, 0.2f, 0.2f, 0.2f), magenta, 
         D3DXCOLOR(0.0f, 0.2f, 0.7f, 0.9f));
      const Material petal_mat2 = 
         Material(D3DXCOLOR(0.1f, 0.2f, 0.2f, 0.2f), magenta, 
         D3DXCOLOR(0.0f, 0.2f, 0.7f, 0.9f));
   }
}