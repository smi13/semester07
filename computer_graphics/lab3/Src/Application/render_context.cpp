#include <windows.h>
#include <d3dx9.h>

#include "render_context.h"

using namespace cg_labs;

static HWND hWnd;
static IDirect3DDevice9 *device;
static int height, width;
static int fill_mode = D3DFILL_SOLID;
static float fov, wh_ratio, mipmap_bias;
static bool lbutton_pressed = false, textures_enabled = true, _f1 = false;
static int light_counter = 0;
static DWORD mip_filter = D3DTEXF_LINEAR, mag_filter = D3DTEXF_LINEAR, 
   min_filter = D3DTEXF_LINEAR;

IDirect3DDevice9 * cg_labs::getDevice()
{
   return device;
}

void cg_labs::setDevice( IDirect3DDevice9 *dev )
{
   device = dev;
}

void cg_labs::updateWindowSize( int _width, int _height )
{
   width = _width;
   height = _height;
   wh_ratio = (float)_width / _height;
}

int cg_labs::getWindowHeight()
{
   return height;
}

int cg_labs::getWindowWidth()
{
   return width;
}

float cg_labs::getWHRatio()
{
   return wh_ratio;
}

float cg_labs::getFieldOfView()
{
   return fov;
}

void cg_labs::setFieldOfView( float new_fov )
{
   fov = new_fov;
}

HWND cg_labs::getWindowHandle()
{
   return hWnd;
}

void cg_labs::setWindowHandle( HWND nhWnd )
{
   hWnd = nhWnd;
}

int cg_labs::getFillMode()
{
   return fill_mode;
}

void cg_labs::setFillMode( int new_fill_mode )
{
   fill_mode = new_fill_mode;
}

bool cg_labs::isMouseLButton()
{
   return lbutton_pressed;
}

void cg_labs::setMouseLButton( bool value )
{
   lbutton_pressed = value;
}

int cg_labs::getLightCounter()
{
   return light_counter++;
}

bool cg_labs::isTexturesEnabled()
{
   return textures_enabled;
}

void cg_labs::setTexturesEnabled( bool value )
{
   textures_enabled = value;
}

float cg_labs::getMipmapBias()
{
   return mipmap_bias;
}

void cg_labs::setMipmapBias( float value )
{
   mipmap_bias = value;

   if (mipmap_bias < 0)
      mipmap_bias = 0;
}

DWORD cg_labs::getMipFilter()
{
   return mip_filter;   
}

DWORD cg_labs::getMagFilter()
{
   return mag_filter;   
}

DWORD cg_labs::getMinFilter()
{
   return min_filter;
}

void cg_labs::setMipFilter( DWORD filt )
{
   mip_filter = filt;
}

void cg_labs::setMagFilter( DWORD filt )
{
   mag_filter = filt;
}

void cg_labs::setMinFilter( DWORD filt )
{
   min_filter = filt;
}

bool cg_labs::getF1()
{
   return _f1;
}

void cg_labs::toggleF1()
{
   if (_f1)
      _f1 = false;
   else
      _f1 = true;
}