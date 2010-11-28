#ifndef _cube_h
#define _cube_h

#include <string>

#include "object.h"

namespace cg_labs 
{
   class Axes : public Object 
   {
   public:
      
      Axes( std::string &name, float x, float y, float z, float a, DWORD Color = D3DCOLOR_XRGB(255, 0, 0) );

      virtual D3DPRIMITIVETYPE getPrimitiveType();

      virtual ~Axes();

   private:

   };
}


#endif /* _cube_h */