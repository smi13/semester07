#include <d3dx9.h>

#define _USE_MATH_DEFINES
#include <cmath>

#include "spheric_camera.h"
#include "utils.h"

using namespace cg_labs;

SphericCamera::SphericCamera()
{
}

void SphericCamera::set( float phi, float theta, float r ) 
{
   _phi = phi;
   _theta = theta;
   _r = r;
   updateMatrix();
}

void SphericCamera::convert( Camera *cam )
{
   D3DXVECTOR3 tmp = cam->getEyePos();
   utils::cartesianToSpheric(tmp, _r, _theta, _phi);

   _eyePos = tmp;
   _lookAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

   _buildMatrix();
}

void SphericCamera::updateMatrix()
{
   _eyePos = utils::spherticToCartesian(_phi, _theta, _r);
   _lookAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

   _buildMatrix();
}

void SphericCamera::rotate( float dx, float dy )
{
   if (dy < 0)
   {
      if (_theta > -M_PI_2 + 0.3)
         _theta += dy;
   }
   else if (dy > 0)
   {
      if (_theta < M_PI_2 - 0.3)
         _theta += dy;
   }

   _phi += dx;

   if (_phi < 0)
      _phi = 0;

   if (_phi > 2.0f * (float)M_PI)
      _phi = 2.0f * (float)M_PI;

   updateMatrix();
}

void SphericCamera::move( int dx, int dz )
{
   float dR = dz * 1.5f / 120.0f;

   if (_r + dR < 6.5)
      _r = 6.5;
   else if (_r + dR > 45)
      _r = 45;
   else 
      _r += dR;

   updateMatrix();
}

SphericCamera::~SphericCamera()
{
}