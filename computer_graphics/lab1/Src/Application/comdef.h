#ifndef _comdef_h
#define _comdef_h

#include "FVF_Gen.h"

#define DEG2RAD(x) (x / 180.0f * (float)M_PI)
#define RAD2DEG(x) (x / (float)M_PI * 180.0f) 

namespace cg_labs
{
   const unsigned long VertexFormat = D3DFVF_XYZ | D3DFVF_DIFFUSE;      

   //TODO: Check if boost can be used for labs & use static assert
   typedef D3D_Util::FVF_Gen<VertexFormat>::Res Vertex;
}


#endif /* _comdef_h */