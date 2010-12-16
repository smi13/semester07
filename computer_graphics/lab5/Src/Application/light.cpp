#include <d3dx9.h>

#include "light.h"
#include "render_context.h"

using namespace cg_labs;

Light::Light( const char *name, D3DLIGHTTYPE type ) : 
   _type(type), _name(std::string(name)), _id(getLightCounter())
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

void Light::toggle()
{
   if (_enabled)
   {
      _enabled = false;
         
      /*if (_obj != 0)
         ;_obj->setColor(D3DCOLOR_XRGB(0, 0, 0));*/
   }
   else
   {
      _enabled = true;

      /*if (_obj != 0)
         _obj->setColor((DWORD)_col);*/
   }
}

Light::~Light()
{
}

PointLight::PointLight( const char *name, D3DXVECTOR3 &pos, D3DXCOLOR col ) : 
   Light(name, D3DLIGHT_POINT), _pos(pos)
{
   _col = col;
}

void PointLight::set()
{
   D3DLIGHT9 light;
   ZeroMemory(&light, sizeof(D3DLIGHT9));
   light.Type = _type;

   light.Attenuation0 = 0.02f;
   light.Attenuation1 = 0.000f;//0.001f;
   light.Attenuation2 = 0.0001f;//0.001f;
   light.Range = 1000.0f;

   light.Position = _pos;
   light.Diffuse = D3DXCOLOR(16.7f, 16.7f, 16.7f, 0.0f);
   light.Ambient = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
   light.Specular = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);

   getDevice()->SetLight(_id, &light);
   getDevice()->LightEnable(_id, _enabled);
}

DirectionalLight::DirectionalLight( const char *name,  
                                   D3DXVECTOR3 &dir, D3DXCOLOR col ) :
   Light(name, D3DLIGHT_DIRECTIONAL), _dir(dir)
{
   D3DXVec3Normalize(&_dir, &_dir);
   _col = col;
}

void DirectionalLight::set()
{
   D3DLIGHT9 light;
   ZeroMemory(&light, sizeof(D3DLIGHT9));
   light.Type = _type;

   light.Attenuation0 = 0.05f;
   light.Attenuation1 = 0.001f;
   light.Attenuation2 = 0.001f;
   light.Range = 100.0f;

   light.Direction = _dir;
   light.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
   light.Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
   light.Specular = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

   getDevice()->SetLight(_id, &light);
   getDevice()->LightEnable(_id, _enabled);
}

SpotLight::SpotLight( const char *name,  D3DXVECTOR3 &pos, D3DXVECTOR3 &dir, 
                     float theta, float phi, D3DXCOLOR col  ) :
   Light(name, D3DLIGHT_SPOT), _dir(dir), _pos(pos), _theta(theta), _phi(phi)
{
   D3DXVec3Normalize(&_dir, &_dir);
   _col = col;
}

void SpotLight::rotateX( float angle )
{
}

void SpotLight::rotateY( float angle )
{
   D3DXMATRIX rot;

   D3DXMatrixRotationY(&rot, angle);

   D3DXVECTOR4 tmp;
   D3DXVec3Transform(&tmp, &_pos, &rot);

   _pos.x = tmp.x;
   _pos.y = tmp.y;
   _pos.z = tmp.z;
}

void SpotLight::rotateZ( float angle )
{
   D3DXMATRIX rot;

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
   
   /*light.Diffuse = D3DXCOLOR(1.7f, 1.7f, 1.7f, 1.0f);
   light.Ambient = D3DXCOLOR(1.7f, 1.7f, 1.7f, 1.0f);
   light.Specular = D3DXCOLOR(1.7f, 1.7f, 1.7f, 1.0f);*/
   light.Diffuse = _col;
   
   light.Theta = _theta;
   light.Phi = _phi;
   light.Falloff = 2.5f;

   getDevice()->SetLight(_id, &light);
   getDevice()->LightEnable(_id, _enabled);
}