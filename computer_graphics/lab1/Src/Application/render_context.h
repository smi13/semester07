#ifndef _render_context_h
#define _render_context_h

struct IDirect3DDevice9;

namespace cg_labs
{
   IDirect3DDevice9 *getDevice();

   void setDevice( IDirect3DDevice9 *dev );
}


#endif /* _render_context_h */