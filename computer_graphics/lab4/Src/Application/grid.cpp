
#define _USE_MATH_DEFINES
#include <cmath>

#include "comdef.h"
#include "grid.h"
#include "render_context.h"

using namespace cg_labs;

Grid::Grid( const char *name, D3DXVECTOR3 (*func)( float u, float v ), 
           D3DXVECTOR3 (*funcNormal)( D3DXVECTOR3 vec ), int M, int N, DWORD color, 
           bool lightenup, bool to_render ) : 
   Object(std::string(name)), _func(func), _m(M), _n(N), _funcNormal(funcNormal), _color(color)
{
   Object::_isLightenUp = lightenup;
   _toRender = to_render;
   _verticesCount = (_m + 1) * (_n + 1);
   _primitivesCount = _m * _n * 2;
   _indicesCount = _primitivesCount * 3;

   getDevice()->CreateVertexBuffer(_verticesCount * sizeof(Vertex),
      D3DUSAGE_WRITEONLY, VertexFormat, D3DPOOL_DEFAULT, &_vbuf, NULL);      
   getDevice()->CreateIndexBuffer(_indicesCount * sizeof(int), D3DUSAGE_WRITEONLY,
      D3DFMT_INDEX16, D3DPOOL_DEFAULT, &_ibuf, NULL);

   _buildObject();
}

void Grid::setFunction( D3DXVECTOR3 (*func)( float u, float v ) )
{
   _func = func;
   _buildObject();
}

void Grid::setColor( DWORD color )
{
   Vertex* pVertices;

   _color = color;

   _vbuf->Lock(0, sizeof(Vertex) * _verticesCount, (void **)&pVertices, 0);

   int w = _m + 1, h = _n + 1;

   for (int j = 0; j < h; j++)
      for (int i = 0; i < w; i++)
      {
         int offset = j * w + i;

         pVertices[offset].m_diffuse = _color;

         if (j == _n || i == _m)
            pVertices[offset].m_diffuse = D3DCOLOR_XRGB(0, 0, 0);
      }

   _vbuf->Unlock();
}

D3DPRIMITIVETYPE cg_labs::Grid::getPrimitiveType()
{
   return D3DPT_TRIANGLELIST;
}

void Grid::_buildObject()
{
   Vertex* pVertices;
   WORD* pIndices; 

   _vbuf->Lock(0, sizeof(Vertex) * _verticesCount, (void **)&pVertices, 0);
   _ibuf->Lock(0, sizeof(WORD) * _indicesCount, (void **)&pIndices, 0);

   int w = _m + 1, h = _n + 1;

   for (int j = 0; j < h; j++)
      for (int i = 0; i < w; i++)
      {
         int offset = j * w + i;
         D3DXVECTOR3 vec = _func((float)i / _m, (float)j / _n);

         pVertices[offset].m_pos[0] = vec.x;
         pVertices[offset].m_pos[1] = vec.y;
         pVertices[offset].m_pos[2] = vec.z;

         if (_funcNormal != 0)
         {
            D3DXVECTOR3 vec_norm = _funcNormal(vec);

            pVertices[offset].m_normal[0] = vec_norm.x;
            pVertices[offset].m_normal[1] = vec_norm.y;
            pVertices[offset].m_normal[2] = vec_norm.z;
         }
         else
         {
            pVertices[offset].m_normal[0] = 0.0f;
            pVertices[offset].m_normal[1] = 1.0f;
            pVertices[offset].m_normal[2] = 0.0f;
         }
         
         pVertices[offset].m_diffuse = _color;

         if (j == _n || i == _m)
            pVertices[offset].m_diffuse = D3DCOLOR_XRGB(0, 0, 0);
            //D3DCOLOR_XRGB(255 - (int)(255 - (0.1f * cos((float)i * j / _m) + 1.0f) * 0.5f * 255), 
              //            255 - (int)(255 - (0.5f * cos((float)i * j / _m * _n) + 1.0f) * 0.5f * 255), 
                //          255 - (int)(255 - (0.9f * sin((float)j / _n) + 0.9f) * 0.5f * 255));
      }

   for (int j = 0; j < _n; j++)
      for (int i = 0; i < _m; i++)
      {
         int offset_ind = j * _m + i, offset_ver = j * w + i;

         pIndices[6 * offset_ind] = offset_ver; 
         pIndices[6 * offset_ind + 1] = offset_ver + 1;
         pIndices[6 * offset_ind + 2] = (j + 1) * w + i;

         pIndices[6 * offset_ind + 3] = offset_ver + 1;
         pIndices[6 * offset_ind + 4] = (j + 1) * w + i + 1;
         pIndices[6 * offset_ind + 5] = (j + 1) * w + i;
      }         

   _vbuf->Unlock();
   _ibuf->Unlock();
}

void Grid::render()
{
   if (isVisible())
   {
      if (Object::_isLightenUp)
         getDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
      else
         getDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);

      Object::render();

      getDevice()->SetFVF(VertexFormat);
      getDevice()->SetStreamSource(0, _vbuf, 0, sizeof(Vertex));
      getDevice()->SetIndices(_ibuf);
      getDevice()->DrawIndexedPrimitive(getPrimitiveType(), 0, 0, _verticesCount,
         0, _primitivesCount);
   }
}

Grid::~Grid()
{
}


D3DXVECTOR3 grid_functions::torus( float u, float v )
{
   D3DXVECTOR3 res;
  
   res.x = cos(2.0f * (float)M_PI * u) * (2.0f + cos(2 * (float)M_PI * v));
   res.y = sin(2.0f * (float)M_PI * v);
   res.z = sin(2.0f * (float)M_PI * u) * (2.0f + cos(2 * (float)M_PI * v));

   return res;
}

D3DXVECTOR3 grid_functions::sphere( float u, float v )
{
   D3DXVECTOR3 res;

   res.x = cos((float)M_PI * u) * cos(2.0f * (float)M_PI * v);
   res.y = sin(2.0f * (float)M_PI * v);
   res.z = sin((float)M_PI * u) * cos(2 * (float)M_PI * v);
 
   return res;
}

D3DXVECTOR3 grid_functions::cylinder( float u, float v )
{
   D3DXVECTOR3 res;

   res.x = cos(2.0f * (float)M_PI * u);
   res.y = v;
   res.z = sin(2.0f * (float)M_PI * u);

   return res;
}

D3DXVECTOR3 grid_functions::cone( float u, float v )
{
   D3DXVECTOR3 res;

   res.x = cos(2.0f * (float)M_PI * u) * (1.5f - v);
   res.y = v;
   res.z = sin(2.0f * (float)M_PI * u) * (1.5f - v);

   return res;
}

D3DXVECTOR3 grid_functions::moebius_strip( float u, float v )
{
   D3DXVECTOR3 res;

   res.x = (1.0f + 0.5f * (v * 2.0f - 1.0f) * cos(2.0f * (float)M_PI * 0.5f * u)) * cos(2.0f * (float)M_PI * u);
   res.y = (1.0f + 0.5f * (v * 2.0f - 1.0f) * cos(2.0f * (float)M_PI * 0.5f * u)) * sin(2.0f * (float)M_PI * u);
   res.z = 0.5f * (v * 2.0f - 1.0f) * sin(2.0f * (float)M_PI * 0.5f * u);

   return res;
}

D3DXVECTOR3 grid_functions::plane( float u, float v )
{
   return D3DXVECTOR3(u, 0.0, v);
}

D3DXVECTOR3 grid_functions::planeNormal( D3DXVECTOR3 vec )
{
   //D3DXVECTOR3 tmp = vec, res;

   //tmp.y = 1.0f;
   //D3DXVec3Normalize(&res, &tmp);
   return D3DXVECTOR3(0.0f, 1.0f, 0.0f);
   //return res;
}

D3DXVECTOR3 grid_functions::sphereNormal( D3DXVECTOR3 vec )
{
   D3DXVECTOR3 tmp;

   D3DXVec3Normalize(&tmp, &vec);
   return tmp;
}

