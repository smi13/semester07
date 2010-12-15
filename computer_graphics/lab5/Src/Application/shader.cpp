#include "Shader.h"

#include "render_context.h"
using namespace cg_labs;

Shader::Shader()
:  vertexShader(0),
   constantTableVS(0),
   pixelShader(0),
   constantTablePS(0)
{
}

Shader::~Shader()
{
   if (vertexShader)
   {
      vertexShader->Release();
   }
   if (constantTableVS)
   {
      constantTableVS->Release();
   }
   if (pixelShader)
   {
      pixelShader->Release();
   }
   if (constantTablePS)
   {
      constantTablePS->Release();
   }
}

void Shader::load( const char* vs, const char* ps )
{
   HRESULT hr;
   LPD3DXBUFFER code;
   DWORD dwShaderFlags = 0;
   LPD3DXBUFFER bufferErrors = NULL;

   if (vs)
   {
      hr = D3DXCompileShaderFromFile( vs, NULL, NULL, "main",
         "vs_2_0", dwShaderFlags, &code,
         &bufferErrors, &constantTableVS );

      if (FAILED(hr))
      {
         LPVOID compileErrors = bufferErrors->GetBufferPointer();
         MessageBox(NULL, (const char*)compileErrors, "Vertex Shader Compile Error", MB_OK|MB_ICONEXCLAMATION);
      }

      getDevice()->CreateVertexShader( (DWORD*)code->GetBufferPointer(), &vertexShader );
      code->Release();
   }

   if (ps)
   {
      hr = D3DXCompileShaderFromFile( ps, NULL, NULL, "main",
         "ps_2_0", dwShaderFlags, &code,
         &bufferErrors, &constantTablePS );

      if (FAILED(hr))
      {
         LPVOID compileErrors = bufferErrors->GetBufferPointer();
         MessageBox(NULL, (const char*)compileErrors, "Pixel Shader Compile Error",
            MB_OK|MB_ICONEXCLAMATION);
      }

      getDevice()->CreatePixelShader((DWORD*)code->GetBufferPointer(), &pixelShader);
      code->Release();
   }
}

void Shader::bind()
{
   getDevice()->SetVertexShader(vertexShader);
   getDevice()->SetPixelShader(pixelShader);
}

void Shader::unbind()
{
   getDevice()->SetVertexShader(NULL);
   getDevice()->SetPixelShader(NULL);
}