#ifndef _complex_objects_h
#define _complex_objects_h

#include <vector>
#include <d3dx9.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include "material.h"
#include "node.h"
#include "object.h"
#include "mesh_object.h"

namespace cg_labs
{
   namespace complex_objects
   {
      const int petals_num = 15;
      const float receptacle_radius = 5.0f;
      const float stem_length = 10;
      const float petal_height = 3.5f;
      const float petal_depth = 0.2f;
      const float petal_ext = 0.1f;
      const float petal_width = 2 * (float)M_PI * receptacle_radius / (float)petals_num;      

      class Petal : public MeshObject
      {
      public:
         Petal();
         Petal( const char *name, Material mat );
         virtual ~Petal();
      };

      struct Flower
      {
         Flower();
         Flower( int petals_num );
         void construct( int petals_num );
         ~Flower();

         static D3DXMATRIX _stemUpdate( float time, std::string &name );
         static D3DXMATRIX _petalUpdate( float time, std::string &name );
         static D3DXMATRIX _receptacleUpdate( float time, std::string &name );

         Node *stem, *receptacle;
         std::vector<Node *> petals1, petals2;
      };
   }
}

#endif /* _complex_objects_h */