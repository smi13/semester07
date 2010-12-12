#ifndef _renderer_h
#define _renderer_h

namespace cg_labs
{
   class Scene;

   class Renderer
   {
   public:
      static void render( Scene &scene );

      static void lightUp( Scene &scene );
   };
}


#endif /* _renderer_h */