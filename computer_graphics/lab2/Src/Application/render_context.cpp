#include <windows.h>
#include <d3dx9.h>

#include "render_context.h"

using namespace cg_labs;

static HWND hWnd;
static IDirect3DDevice9 *device;
static int height, width;
static int fill_mode = D3DFILL_SOLID;
static float fov, wh_ratio;
static bool lbutton_pressed = false;
static int light_counter = 0;

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