#ifndef _render_context_h
#define _render_context_h

struct IDirect3DDevice9;

namespace cg_labs
{
   IDirect3DDevice9 *getDevice();

   void setDevice( IDirect3DDevice9 *dev );

   void updateWindowSize( int width, int height );

   int getWindowWidth();
   int getWindowHeight();
   
   HWND getWindowHandle();
   void setWindowHandle( HWND hWnd );

   int getFillMode();
   void setFillMode( int new_fill_mode );
}


#endif /* _render_context_h */