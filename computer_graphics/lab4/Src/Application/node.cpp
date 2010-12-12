#include <string>

#include "node.h"
#include "render_context.h"

using namespace cg_labs;

Node::Node( Object *obj, D3DXMATRIX (*update)( float time, std::string &name ) ) : 
   _object(obj), _update(update)
{
   D3DXMatrixIdentity(&_matrix);
}

void Node::render()
{
   LPD3DXMATRIXSTACK stack = getStack();

   stack->Push();
   stack->MultMatrixLocal(&_matrix);

   getDevice()->SetTransform(D3DTS_WORLDMATRIX(0), stack->GetTop());

   _object->render();

   for (int i = 0; i != _children.size(); i++)
      _children[i]->render();

   stack->Pop();
}

void Node::addChild( Node *child )
{
   _children.push_back(child);
}

void Node::update( float time )
{
   if (_update != 0)
      _matrix = _update(time, _object->getName());
   
   for (int i = 0; i != _children.size(); i++)
      _children[i]->update(time);
}

void Node::clear()
{
   if (_object != 0)
   {
      delete _object;
      _object = 0;
   }

   for (int i = 0; i != _children.size(); i++)
      _children[i]->clear();

   _children.resize(0);
}

Node::~Node()
{
   clear();
}