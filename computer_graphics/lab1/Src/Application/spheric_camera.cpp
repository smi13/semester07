#include <d3dx9.h>

#define _USE_MATH_DEFINES
#include <cmath>

#include "spheric_camera.h"

using namespace cg_labs;

#define SPH2CART(x, y, z, phi, theta, r)  do { \
   ((x) = (r) * cos((theta)) * cos((phi))); \
   ((y) = (r) * sin((theta))); \
   ((z) = (r) * cos((theta)) * sin((phi))); } while(0);


SphericCamera::SphericCamera( float phi, float theta, float r ) : 
   _phi(phi), _theta(theta), _r(r)
{
   buildMatrix();
}

void SphericCamera::buildMatrix()
{
   float x, y, z;

   SPH2CART(x, y, z, _phi, _theta, _r);

   D3DXVECTOR3 vEyePt(x, y, z);
   D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
   D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);

   D3DXMatrixLookAtLH(&_matrix, &vEyePt, &vLookatPt, &vUpVec);
}

D3DXMATRIXA16 *SphericCamera::getMatrix()
{
   return &_matrix;
}

void SphericCamera::increasePhi( float step )
{
   _phi += step;
}

void SphericCamera::decreasePhi( float step )
{
   _phi -= step;
}

void SphericCamera::increaseTheta( float step )
{
   if (_theta < M_PI_2 - 0.3)
      _theta += step;
}

void SphericCamera::decreaseTheta( float step )
{
   if (_theta > -M_PI_2 + 0.3)
      _theta -= step;
}

void SphericCamera::increaseR( float step )
{
   if (_r < 15.0f)
      _r += step;
}

void SphericCamera::decreaseR( float step )
{
   if (_r > 1.5f)
      _r -= step;
}

SphericCamera::~SphericCamera()
{
}