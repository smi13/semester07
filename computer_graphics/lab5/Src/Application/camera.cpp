#include "camera.h"

using namespace cg_labs;

D3DXMATRIX *Camera::getMatrix()
{
   return &_matrix;
}

D3DXVECTOR3 Camera::getEyePos()
{
   return _eyePos;
}

D3DXVECTOR3 Camera::getLookAt()
{
   return _lookAt;
}

D3DXVECTOR3 Camera::getUpVec()
{
   return D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

void Camera::_buildMatrix()
{
   D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

   D3DXMatrixLookAtLH(&_matrix, &_eyePos, &_lookAt, &up);
}