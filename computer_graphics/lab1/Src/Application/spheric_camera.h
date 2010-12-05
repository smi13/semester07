#ifndef _spheric_camera_h
#define _spheric_camera_h

#include <d3dx9.h>

#include "comdef.h"

namespace cg_labs
{
   class SphericCamera
   {
   public:

      SphericCamera( float phi, float theta, float r );

      D3DXMATRIXA16 *getMatrix();

      void increasePhi( float step );
      void decreasePhi( float step );
      void increaseTheta( float step );
      void decreaseTheta( float step );

      void zoom( int step );

      void buildMatrix();

      ~SphericCamera();

   private:

      float _phi, _theta, _r;
      D3DXMATRIXA16 _matrix;

      SphericCamera();

   };
}


#endif /* _spheric_camera_h */