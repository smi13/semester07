#include <d3dx9.h>

#include "light.h"
#include "render_context.h"

using namespace cg_labs;

Light::Light( const char *name, D3DLIGHTTYPE type, Grid *obj ) : 
   _type(type), _name(std::string(name)), _id(getLightCounter()), _obj(obj)
{
}

std::string &Light::getName()
{
   return _name;
}

int Light::getType()
{
   return _type;
}

Object *Light::getObject()
{
   return _obj;
}

void Light::toggle()
{
   if (_enabled)
   {
      _enabled = false;
         
      if (_obj != 0)
         _obj->setColor(D3DCOLOR_XRGB(0, 0, 0));
   }
   else
   {
      _enabled = true;

      if (_obj != 0)
         _obj->setColor((DWORD)_col);
   }
}

Light::~Light()
{
   if (_obj != 0)
      delete _obj;
}

PointLight::PointLight( const char *name, D3DXVECTOR3 &pos, D3DXCOLOR col, Grid *obj ) : 
   Light(name, D3DLIGHT_POINT, obj), _pos(pos)
{
   _col = col;
   if (_obj == 0)
   {
      char Buf[50];

      sprintf_s(Buf, "%i", _id);
      _obj = 
         new Grid((std::string("pointlight") + std::string(Buf)).c_str(), 
         grid_functions::sphere, 0, 30, 30, (DWORD)col);
      _obj->setLighting(false);
      _obj->translate(_pos.x, _pos.y, _pos.z);
   }
}

void PointLight::set()
{
   D3DLIGHT9 light;
   ZeroMemory(&light, sizeof(D3DLIGHT9));
   light.Type = _type;

   light.Attenuation0 = 0.1f;
   light.Attenuation1 = 0.001f;//0.001f;
   light.Attenuation2 = 0.001f;//0.001f;
   light.Range = 50.0f;

   light.Position = _pos;
   light.Diffuse = _col;

   getDevice()->SetLight(_id, &light);
   getDevice()->LightEnable(_id, _enabled);
}

DirectionalLight::DirectionalLight( const char *name,  
                                   D3DXVECTOR3 &dir, D3DXCOLOR col, Grid *obj ) :
   Light(name, D3DLIGHT_DIRECTIONAL, obj), _dir(dir)
{
   D3DXVec3Normalize(&_dir, &_dir);
   _col = col;
   if (_obj == 0)
   {
      char Buf[50];

      sprintf_s(Buf, "%i", _id);
      _obj = 
         new Grid((std::string("dirlight") + std::string(Buf)).c_str(), 
         grid_functions::cylinder, 0, 30, 30, (DWORD)col);
      _obj->setLighting(false);
   }
}

void DirectionalLight::set()
{
   D3DLIGHT9 light;
   ZeroMemory(&light, sizeof(D3DLIGHT9));
   light.Type = _type;

   light.Attenuation0 = 0.1f;
   light.Attenuation1 = 0.001f;//0.001f;
   light.Attenuation2 = 0.001f;//0.001f;
   light.Range = 50.0f;

   light.Direction = _dir;
   light.Diffuse = _col;

   getDevice()->SetLight(_id, &light);
   getDevice()->LightEnable(_id, _enabled);
}

SpotLight::SpotLight( const char *name,  D3DXVECTOR3 &pos, D3DXVECTOR3 &dir, 
                     float theta, float phi, D3DXCOLOR col, Grid *obj ) :
   Light(name, D3DLIGHT_SPOT, obj), _dir(dir), _pos(pos), _theta(theta), _phi(phi)
{
   D3DXVec3Normalize(&_dir, &_dir);
   _col = col;
   if (_obj == 0)
   {
      char Buf[50];

      sprintf_s(Buf, "%i", _id);
      _obj = 
         new Grid((std::string("spotlight") + std::string(Buf)).c_str(), 
         grid_functions::cone, 0, 30, 30, (DWORD)col);
      _obj->setLighting(false);
   }
}

void SpotLight::rotateX( float angle )
{
   _obj->rotateX(angle);
}

void SpotLight::rotateY( float angle )
{
   _obj->rotateY(angle);
}

void SpotLight::rotateZ( float angle )
{
   D3DXMATRIX rot;
   _obj->rotateZ(angle);
   
   D3DXMatrixRotationZ(&rot, angle);

   D3DXVECTOR4 tmp;
   D3DXVec3Transform(&tmp, &_dir, &rot);

   _dir.x = tmp.x;
   _dir.y = tmp.y;
   _dir.z = tmp.z;

}

void SpotLight::translate( float x, float y, float z )
{
   _pos += D3DXVECTOR3(x, y, z);
   _obj->translate(x, y, z);
}

void SpotLight::set()
{
   D3DLIGHT9 light;
   ZeroMemory(&light, sizeof(D3DLIGHT9));
   light.Type = _type;

   light.Attenuation0 = 0.1f;
   //light.Attenuation1 = 0.001f;//0.001f;
   //light.Attenuation2 = 0.001f;//0.001f;
   light.Range = 50.0f;

   light.Direction = _dir;
   light.Position = _pos;
   light.Diffuse = _col;

   light.Theta = _theta;
   light.Phi = _phi;
   light.Falloff = 2.5f;

   getDevice()->SetLight(_id, &light);
   getDevice()->LightEnable(_id, _enabled);
}