#ifndef _comdef_h
#define _comdef_h

#include "FVF_Gen.h"

namespace cg_labs
{
   const unsigned long VertexFormat = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_NORMAL;      

   //TODO: Check if boost can be used for labs & use static assert
   typedef D3D_Util::FVF_Gen<VertexFormat>::Res Vertex;
}


#endif /* _comdef_h */