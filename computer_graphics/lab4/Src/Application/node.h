#ifndef _node_h
#define _node_h

#include <vector>
#include <string>

#include "object.h"

namespace cg_labs
{
   class Node
   {
   public:

      Node( Object *obj, D3DXMATRIX (*update)( float time, std::string &name ) = 0 );

      void render();
      void addChild( Node *child );
      void update( float time );
      void clear();

      ~Node();

   private:

      D3DXMATRIX (*_update)( float time, std::string &name );
      D3DXMATRIX _matrix;
      Object *_object;
      std::vector<Node *> _children;

   };
}


#endif /* _node_h */