#ifndef _shader_h
#define _shader_h

#include <d3dx9.h>

namespace cg_labs
{
   struct Shader
   {
      Shader();

      void load( const char* vs, const char* ps );

      void bind();
      void unbind();

      ~Shader();

      LPD3DXCONSTANTTABLE    constantTableVS;
      LPD3DXCONSTANTTABLE    constantTablePS;
   private:
      LPDIRECT3DVERTEXSHADER9  vertexShader;
      LPDIRECT3DPIXELSHADER9 pixelShader;
   };
}


#endif /* _shader_h */