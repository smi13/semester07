#include <d3dx9.h>

#include "material.h"

namespace cg_labs
{
   namespace constants
   {
      const float sensitivity = 0.005f;

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
   }
}