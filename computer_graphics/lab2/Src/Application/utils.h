#ifndef _utils_h
#define _utils_h

#include <d3dx9.h>

#include "render_context.h"

namespace cg_labs
{
   namespace utils
   {
      void toggleWireFrame();
      void toggleFullScreen();

      D3DXVECTOR3 spherticToCartesian( float phi, float theta, float r );

      void cartesianToSpheric( const D3DXVECTOR3 &cart, float &r, 
         float &theta, float &phi );

      class TextRenderer
      {
      public:

         void init();

         void begin();
         void drawTextLine( const char *str );
         void setInsertionPos( int x, int y );
         void setForegroundColor( D3DXCOLOR clr );
         void end();

         ~TextRenderer();

      private:

         ID3DXFont* m_pFont9;
         ID3DXSprite* m_pSprite9;
         D3DXCOLOR m_clr;
         POINT m_pt;
         int m_nLineHeight;
      };
   }
}


#endif /* _utils_h */