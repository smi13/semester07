#ifndef _comdef_h
#define _comdef_h

#include "FVF_Gen.h"

namespace cg_labs
{
   const unsigned long VertexFormat = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | 
      D3DFVF_TEX2 | D3DFVF_TEXCOORDSIZE3(0) | D3DFVF_TEXCOORDSIZE2(1);
      //D3DFVF_TEXCOORDSIZE3(0) |
      //D3DFVF_TEXCOORDSIZE2(1) ;
            
   //TODO: Check if boost can be used for labs & use static assert

   struct Vertex 
   {
      float m_pos[3];
      float m_normal[3];
      D3DCOLOR m_diffuse;
      float m_tex_1[3];
      float m_tex_2[2];
   };
   //typedef D3D_Util::FVF_Gen<VertexFormat>::Res Vertex;
}


#endif /* _comdef_h */