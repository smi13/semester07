#include <vector>
#include <d3dx9.h>

#include "constants.h"
#include "complex_objects.h"
#include "node.h"
#include "mesh_object.h"

using namespace cg_labs;

/************************************************************************/
/* Flower class methods implementation                                  */
/************************************************************************/

complex_objects::Flower::Flower() 
{
}

complex_objects::Flower::Flower( int petals_num ) 
{
   construct(petals_num);   
}

void complex_objects::Flower::construct( int petals_num )
{
   MeshObject *stem_obj = new MeshObject("stem");
   ShapeCreator::createCylinder(stem_obj, constants::stem_mat, receptacle_radius / 10.0f,
      stem_length, 20, petals_num);
   MeshObject *receptacle_obj = new MeshObject("receptacle");
   ShapeCreator::createCylinder(receptacle_obj, constants::receptacle_mat, receptacle_radius,
      stem_length / 10.0f, petals_num, 20);

   stem = new Node(stem_obj, _stemUpdate);
   receptacle = new Node(receptacle_obj, _receptacleUpdate);

   stem->addChild(receptacle);

   petals1.resize(petals_num);
   petals2.resize(petals_num);

   for (int i = 0; i != petals_num; i++)
   {
      char Buf[50];
      MeshObject *petal1_obj,
         *petal2_obj;

      sprintf_s(Buf, "1 %i", i);
      petal1_obj = new Petal(Buf, constants::petal_mat1);
      
      sprintf_s(Buf, "2 %i", i);
      petal2_obj = new Petal(Buf, constants::petal_mat2);      

      petals1[i] = new Node(petal1_obj, _petalUpdate);
      petals2[i] = new Node(petal2_obj, _petalUpdate);

      petals1[i]->addChild(petals2[i]);
      receptacle->addChild(petals1[i]);
   }
}

complex_objects::Flower::~Flower()
{
   delete stem;
   delete receptacle;

   for (int i = 0; i != petals1.size(); i++)
   {
      delete petals1[i];
      delete petals2[i];
   }
}

/************************************************************************/
/* Petal class methods implementation                                   */
/************************************************************************/

complex_objects::Petal::Petal()
{
}

complex_objects::Petal::Petal( const char *name, Material mat ) :
   MeshObject(name)
{
   ShapeCreator::createBox(this, mat, petal_depth, petal_width, petal_height);

   typedef D3D_Util::FVF_Gen<D3DFVF_XYZ | D3DFVF_NORMAL>::Res MeshVertex;

   Object::_verticesCount = _mesh->GetNumVertices();
   IDirect3DVertexBuffer9 *vbuf = 0;

   _mesh->GetVertexBuffer(&vbuf);

   MeshVertex* pVertices;
   vbuf->Lock(0, sizeof(MeshVertex) * _verticesCount, (void **)&pVertices, 0);

   for (int i = 0; i != _verticesCount; i++)
   {
      if (pVertices[i].m_pos[2] < 0)
      {
         if (pVertices[i].m_pos[1] > 0)
            pVertices[i].m_pos[1] += petal_ext;
         else if (pVertices[i].m_pos[1] < 0)
            pVertices[i].m_pos[1] -= petal_ext;
      }
   }

   vbuf->Unlock();
   vbuf->Release();
}

complex_objects::Petal::~Petal()
{

}

/************************************************************************/
/* Flower hierarchy objects callbacks                                   */
/************************************************************************/

D3DXMATRIX complex_objects::Flower::_stemUpdate( float time, std::string &name )
{
   D3DXMATRIX res, tmp;

   D3DXMatrixIdentity(&res);
   D3DXMatrixTranslation(&tmp, 0.0f, 0.0f, -stem_length * 0.5f);
   res *= tmp;
   D3DXMatrixRotationX(&tmp, D3DXToRadian(90));
   res *= tmp;
   D3DXMatrixTranslation(&tmp, 0.0f, 0.0f, stem_length * 0.5f);
   res *= tmp;
   
   return res;
}

D3DXMATRIX complex_objects::Flower::_receptacleUpdate( float time, std::string &name )
{
   D3DXMATRIX res, tmp;

   D3DXMatrixIdentity(&res);

   D3DXMatrixRotationZ(&tmp, time / 10.0f);
   res *= tmp;
   D3DXMatrixTranslation(&tmp, 0, 0, -stem_length * 0.5f);
   res *= tmp;

   return res;
}

D3DXMATRIX complex_objects::Flower::_petalUpdate( float time, std::string &name )
{
   int ind, i;

   static float old_time;
   D3DXMATRIX res;
   D3DXMatrixIdentity(&res);

   sscanf_s(name.c_str(), "%i %i", &ind, &i);

   if (ind == 1)
   {
      float angle = (float)M_PI / (float)petals_num,
         angle2 = (petals_num - 2) * (float)M_PI / (float)petals_num,
         r = receptacle_radius * cosf(angle);
      
      D3DXMATRIX tmp;

      D3DXMatrixRotationZ(&tmp, i * angle2 + (float)M_PI_2);
      res *= tmp;

      D3DXMatrixTranslation(&tmp, 0.0f, 0.0f, -petal_height * 0.5f);
      res *= tmp;

      D3DXVECTOR3 vec(r * cosf(2 * i * angle), -r * sinf(2 * i * angle), 0.0f);
      D3DXMatrixRotationAxis(&tmp, &vec, cosf(time - 0.4f * i) - 0.8f);
      res *= tmp;

      D3DXMatrixTranslation(&tmp, 0.0f, 0.0f, 
         petal_height * 0.5f);
      res *= tmp;
      
      D3DXMatrixTranslation(&tmp, -r * sinf(2 * i * angle), 
         -r * cosf(2 * i * angle), 
         -petal_height * 0.5f - stem_length / 20.0f);
      res *= tmp;      
   }
   else if (ind == 2)
   {
      float angle = 0.5f * cosf(time - 0.4f * i) + D3DXToRadian(30);
      D3DXMATRIX tmp;

      D3DXMatrixRotationY(&tmp, D3DXToRadian(180));
      res *= tmp;

      D3DXMatrixTranslation(&tmp, 0.0f, 0.0f, -petal_height * 0.5f);
      res *= tmp;

      D3DXMatrixRotationY(&tmp, 
         i % 2 ? angle  : -angle);
      res *= tmp;

      D3DXMatrixTranslation(&tmp, 0.0f, 0.0f, petal_height * 0.5f);
      res *= tmp;

      D3DXMatrixTranslation(&tmp, 0.0f, 0.0f, -petal_height);
      res *= tmp;
   }

   return res;
}