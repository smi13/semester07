#include <windows.h>
#include <d3dx9.h>

#include "render_context.h"

using namespace cg_labs;

static HWND hWnd;
static IDirect3DDevice9 *device;
static int height, width;
static int fill_mode = D3DFILL_SOLID;

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
}

int cg_labs::getWindowHeight()
{
   return height;
}

int cg_labs::getWindowWidth()
{
   return width;
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