#include <d3dx9.h>

#define _USE_MATH_DEFINES
#include <cmath>

#include "free_camera.h"

using namespace cg_labs;

FreeCamera::FreeCamera()
{
}

void FreeCamera::rotate( float dx, float dy )
{   
   _yaw += dx;
   _pitch += dy;  

   updateMatrix();
}

void FreeCamera::move( int dx, int dz )
{
   D3DXMATRIXA16 matRotation;
   D3DXMatrixRotationYawPitchRoll(&matRotation, _yaw, _pitch, 0.0f);
   
   D3DXVECTOR3 move, dir(fabs((float)dx) / 120.0f, 0.0f, fabs((float)dz) / 120.0f);
   D3DXVec3TransformNormal(&move, &dir, &matRotation);

   if (dz < 0 || dx < 0)
      _eyePos -= move;
   else
      _eyePos += move;

   updateMatrix();
}

void FreeCamera::updateMatrix()
{
   D3DXMATRIX rot;
   D3DXMatrixRotationYawPitchRoll(&rot, _yaw, _pitch, 0.0f);

   D3DXVECTOR3 dir(0, 0, 1);
   D3DXVECTOR3 target;
   D3DXVec3TransformNormal(&target, &dir, &rot);
   target += _eyePos;

   _lookAt = target;

   _buildMatrix();
}

void FreeCamera::convert( Camera *cam )
{
   _lookAt = cam->getLookAt();
   _eyePos = cam->getEyePos();

   D3DXVECTOR3 target = _lookAt - _eyePos;
   float len = D3DXVec3Length(&target);

   _pitch = -asinf(target.y / len);

   float dist_to_camera = len * cosf(_pitch);

   _yaw = acosf(target.x / dist_to_camera) - 3 * (float)M_PI / 2;

   if (target.z > 0) 
      _yaw = -(_yaw + (float)M_PI);

   updateMatrix();
}

FreeCamera::~FreeCamera()
{
}