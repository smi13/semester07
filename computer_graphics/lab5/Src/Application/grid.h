#ifndef _grid_h
#define _grid_h

#include <d3dx9.h>

#include "object.h"

namespace cg_labs
{
   class Grid : public Object
   {
   public:

      Grid( const char *name, D3DXVECTOR3 (*func)( float u, float v ),
         D3DXVECTOR3 (*funcNormal)( D3DXVECTOR3 vec ), int M, int N, DWORD color, 
         DWORD cubeface, bool lightenup = true, bool to_render = true );

      void setFunction( D3DXVECTOR3 (*_func)( float u, float v ) );
      void setColor( DWORD color );
      
      virtual D3DPRIMITIVETYPE getPrimitiveType();

      virtual void render();

      virtual ~Grid();

   private:

      IDirect3DTexture9 *_texture;

      Grid();
      void _buildObject();

      DWORD _color, _cubeface;
      int _m, _n;
      D3DXVECTOR3 (*_func)( float u, float v );
      D3DXVECTOR3 (*_funcNormal)( D3DXVECTOR3 vec );
   };

   namespace grid_functions
   {
      D3DXVECTOR3 plane( float u, float v );
      D3DXVECTOR3 torus( float u, float v );
      D3DXVECTOR3 sphere( float u, float v );
      D3DXVECTOR3 cylinder( float u, float v );
      D3DXVECTOR3 cone( float u, float v );
      D3DXVECTOR3 moebius_strip( float u, float v );

      D3DXVECTOR3 planeNormal( D3DXVECTOR3 vec );
      D3DXVECTOR3 sphereNormal( D3DXVECTOR3 vec );
   }
}


#endif /* _grid_h */