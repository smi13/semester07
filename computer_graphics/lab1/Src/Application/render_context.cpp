
#include <d3dx9.h>

#include "render_context.h"

using namespace cg_labs;

static IDirect3DDevice9 *device;

IDirect3DDevice9 * cg_labs::getDevice()
{
   return device;
}

void cg_labs::setDevice( IDirect3DDevice9 *dev )
{
   device = dev;
}