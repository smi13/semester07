#include "camera.h"

namespace cg_labs
{
   class FreeCamera : public Camera
   {
   public:

      FreeCamera();

      virtual void rotate( float dx, float dy );
      virtual void move( int dx, int dz );
      virtual void updateMatrix();

      void convert( Camera *cam );

      ~FreeCamera();

   private:

      float _yaw, _pitch;
   };
}