#ifndef _camera_h
#define _camera_h

#include <d3dx9.h>

namespace cg_labs
{
   class Camera
   {
   public:

      virtual void rotate( float dx, float dy ) = 0;
      virtual void move( int dx, int dz ) = 0;
      virtual void updateMatrix() = 0;

      D3DXVECTOR3 getEyePos();
      D3DXVECTOR3 getLookAt();
      D3DXVECTOR3 getUpVec();

      D3DXMATRIX *getMatrix();

   protected:

      void _buildMatrix();

      D3DXVECTOR3 _eyePos, _lookAt;
      D3DXMATRIX _matrix;
   };
}


#endif /* _camera_h */