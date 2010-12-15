#include "object.h"
#include "render_context.h"

using namespace cg_labs;

Object::Object() : _vbuf(0), _ibuf(0), _toRender(true)
{
}

Object::Object( std::string &name ) : _vbuf(0), _ibuf(0), _name(name), _toRender(true)
{
   D3DXMatrixIdentity(&_matrix);
}

std::string &Object::getName()
{
   return _name;
}

void Object::translate( float x, float y, float z )
{
   D3DXMATRIX tmp;

   D3DXMatrixTranslation(&tmp, x, y, z);

   _matrix *= tmp;
}

void Object::rotateX( float angle )
{
   D3DXMATRIX tmp;

   D3DXMatrixRotationX(&tmp, angle);

   _matrix *= tmp;
}

void Object::rotateY( float angle )
{
   D3DXMATRIX tmp;

   D3DXMatrixRotationY(&tmp, angle);

   _matrix *= tmp;
}

void Object::rotateZ( float angle )
{
   D3DXMATRIX tmp;

   D3DXMatrixRotationZ(&tmp, angle);

   _matrix *= tmp;
}

void Object::scale( float scl )
{
   D3DXMATRIX tmp;

   D3DXMatrixScaling(&tmp, scl, scl, scl);

   _matrix *= tmp;
}

void Object::scale( float scl_x, float scl_y, float scl_z )
{
   D3DXMATRIX tmp;

   D3DXMatrixScaling(&tmp, scl_x, scl_y, scl_z);

   _matrix *= tmp;
}

void Object::setIdentity()
{
   D3DXMatrixIdentity(&_matrix);
}

void Object::setVisible( bool value )
{
   _toRender = value;
}

void Object::setLighting( bool value )
{
   _isLightenUp = value;
}

bool Object::isVisible()
{
   return _toRender;
}

void Object::clear()
{
   if (_vbuf != 0)
   {
      _vbuf->Release(); 
      _vbuf = 0;
   }

   if (_ibuf != 0)
   {
      _ibuf->Release();
      _ibuf = 0;
   }
}

void Object::render()
{
   getDevice()->SetTransform(D3DTS_WORLD, &_matrix);
}

Object::~Object() 
{
   clear();
}

