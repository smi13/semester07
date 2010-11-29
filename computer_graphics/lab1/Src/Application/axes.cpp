#include <d3dx9.h>
#include <string>

#include "comdef.h"
#include "axes.h"
#include "render_context.h"

using namespace cg_labs;

Axes::Axes( const char *name, float a, DWORD color, bool to_render ) : 
   Object(std::string(name))
{
   _toRender = to_render;
   _verticesCount = 6;
   _primitivesCount = 3;

   getDevice()->CreateVertexBuffer(_verticesCount * sizeof(Vertex), 
      D3DUSAGE_WRITEONLY, VertexFormat, D3DPOOL_DEFAULT, &_vbuf, NULL);

   Vertex* pVertices;

   _vbuf->Lock(0, sizeof(Vertex) * _verticesCount, (void **)&pVertices, 0);

   pVertices[0].m_pos[0] = 0.0f;
   pVertices[0].m_pos[1] = 0.0f;
   pVertices[0].m_pos[2] = 0.0f;
   pVertices[0].m_diffuse = color; 

   pVertices[1].m_pos[0] = a;
   pVertices[1].m_pos[1] = 0.0f;
   pVertices[1].m_pos[2] = 0.0f;
   pVertices[1].m_diffuse = color; 

   pVertices[2].m_pos[0] = 0.0f;
   pVertices[2].m_pos[1] = 0.0f;
   pVertices[2].m_pos[2] = 0.0f;
   pVertices[2].m_diffuse = color; 

   pVertices[3].m_pos[0] = 0.0f;
   pVertices[3].m_pos[1] = a;
   pVertices[3].m_pos[2] = 0.0f;
   pVertices[3].m_diffuse = color; 

   pVertices[4].m_pos[0] = 0.0f;
   pVertices[4].m_pos[1] = 0.0f;
   pVertices[4].m_pos[2] = 0.0f;
   pVertices[4].m_diffuse = color; 

   pVertices[5].m_pos[0] = 0.0f;
   pVertices[5].m_pos[1] = 0.0f;
   pVertices[5].m_pos[2] = a;
   pVertices[5].m_diffuse = color; 

   _vbuf->Unlock();   
}

D3DPRIMITIVETYPE Axes::getPrimitiveType()
{
   return D3DPT_LINELIST;
}

Axes::~Axes()
{
}

