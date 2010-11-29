#ifndef _cube_h
#define _cube_h

#include "object.h"

namespace cg_labs 
{
   class Axes : public Object 
   {
   public:
      
      Axes( const char *name, float a, DWORD Color = D3DCOLOR_XRGB(255, 0, 0), bool to_render = true );

      virtual D3DPRIMITIVETYPE getPrimitiveType();

      virtual ~Axes();

   private:

   };
}


#endif /* _cube_h */