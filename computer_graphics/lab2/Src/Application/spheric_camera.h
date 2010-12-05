#ifndef _spheric_camera_h
#define _spheric_camera_h

#include <d3dx9.h>

#include "camera.h"
#include "comdef.h"

namespace cg_labs
{
   class SphericCamera : public Camera
   {
   public:

      SphericCamera();

      void rotate( float dx, float dy );
      virtual void move( int dx, int dz );
      virtual void updateMatrix();

      void convert( Camera *cam );
      void set( float phi, float theta, float r );

      ~SphericCamera();

   private:

      float _phi, _theta, _r;
   };
}


#endif /* _spheric_camera_h */