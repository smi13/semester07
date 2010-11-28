#include <d3dx9.h>
#include <cmath>

#include "spheric_camera.h"

using namespace cg_labs;

#define SPH2CART(x, y, z, phi, thetha, r)  do { \
   ((x) = (r) * cos((thetha)) * sin((phi))); \
   ((y) = (r) * sin((thetha)) * sin((phi))); \
   ((z) = (r) * cos((phi))); } while(0);


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

SphericCamera::~SphericCamera()
{

}

void SphericCamera::increasePhi( float step )
{
   _phi += step;
}

void SphericCamera::decreasePhi( float step )
{
   _phi -= step;
}

void SphericCamera::increaseTheta( float step)
{
   _theta += step;
}

void SphericCamera::decreaseTheta( float step )
{
   _theta -= step;
}

void SphericCamera::increaseR( float step )
{
   _r += step;
}

void SphericCamera::decreaseR( float step )
{
   _r -= step;
}
