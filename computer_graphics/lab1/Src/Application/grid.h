#ifndef _grid_h
#define _grid_h

#include <d3dx9.h>

#include "object.h"

namespace cg_labs
{
   class Grid : public Object
   {
   public:

      Grid( const char *name, D3DXVECTOR3 (*func)( float u, float v ), int M, int N, bool to_render = true );

      void setFunction( D3DXVECTOR3 (*_func)( float u, float v ) );
      virtual D3DPRIMITIVETYPE getPrimitiveType();

      virtual ~Grid();

   private:

      Grid();
      void _buildObject();
      
      int _m, _n;
      D3DXVECTOR3 (*_func)( float u, float v );
   };

   namespace grid_functions
   {
      D3DXVECTOR3 torus( float u, float v );
      D3DXVECTOR3 sphere( float u, float v );
      D3DXVECTOR3 cylinder( float u, float v );
      D3DXVECTOR3 cone( float u, float v );
      D3DXVECTOR3 moebius_strip( float u, float v );
   }
}


#endif /* _grid_h */