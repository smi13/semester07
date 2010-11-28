#ifndef _comdef_h
#define _comdef_h

#include "FVF_Gen.h"

#define DEG2RAD(x) (x / 180.0 * pi)
#define RAD2DEG(x) (x / pi * 180.0) 

namespace cg_labs
{
   const unsigned long VertexFormat = D3DFVF_XYZ | D3DFVF_DIFFUSE;      

   const float pi = 3.141592f;

   //TODO: Check if boost can be used for labs & use static assert
   typedef D3D_Util::FVF_Gen<VertexFormat>::Res Vertex;
   
}


#endif /* _comdef_h */