#ifndef _lab1_app_h
#define _lab1_app_h

#include "Library/cglApp.h"

struct IDirect3DDevice9;

namespace cg_labs
{
   class lab1App : public cglApp
   {
   public:

      lab1App( int nW, int nH, void* hInst, int nCmdShow ); 

      bool processInput( unsigned int nMsg, int wParam, long lParam );
      
      ~lab1App();

   protected:

      void renderInternal();
      void update();

      char const *getWindowText();

   private:

      IDirect3DDevice9 *_device;

   };
}


#endif /* _lab1_app_h */