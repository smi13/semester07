#ifndef _light_h
#define _light_h

#include "grid.h"

namespace cg_labs
{
   class Light
   {
   public:

      Light( const char *name, D3DLIGHTTYPE type, Grid *obj = 0 );

      virtual void set() = 0;

      std::string &getName();
      int getType();
      Object *getObject();
      void toggle();

      virtual void rotateX( float angle ) {}
      virtual void rotateY( float angle ) {}
      virtual void rotateZ( float angle ) {}
      virtual void translate( float x, float y, float z ) {}

      ~Light();

      bool _enabled;

   protected:
      int _id;
      D3DLIGHTTYPE _type;
      D3DXCOLOR _col;
      std::string _name;
      Grid *_obj;

   private:
      Light();
   };

   class PointLight : public Light
   {
   public:

      PointLight( const char *name, D3DXVECTOR3 &pos, D3DXCOLOR col, Grid *obj = 0 );

      virtual void set();

   private:

      D3DXVECTOR3 _pos;
      
   };

   class SpotLight : public Light
   {
   public:

      SpotLight( const char *name,  D3DXVECTOR3 &pos, D3DXVECTOR3 &dir, 
         float theta, float phi, D3DXCOLOR col, Grid *obj = 0 );

      virtual void rotateX( float angle );
      virtual void rotateY( float angle );
      virtual void rotateZ( float angle );
      virtual void translate( float x, float y, float z );

      virtual void set();

   private:

      float _theta, _phi;
      D3DXVECTOR3 _pos, _dir;
   };

   class DirectionalLight : public Light
   {
   public:

      DirectionalLight( const char *name,  D3DXVECTOR3 &dir, D3DXCOLOR col, Grid *obj = 0 );

      virtual void set();

   private:

      D3DXVECTOR3 _dir;
   };
}


#endif /* _light_h */