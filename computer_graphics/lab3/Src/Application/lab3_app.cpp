#include <windows.h>
#include <d3dx9.h>

#define _USE_MATH_DEFINES
#include <cmath>

#include "Library/cglD3D.h"

#include "lab3_app.h"
#include "comdef.h"
#include "axes.h"
#include "grid.h"
#include "mesh_object.h"
#include "render_context.h"
#include "utils.h"
#include "light.h"

using namespace cg_labs;

lab3App::lab3App( int nW, int nH, void *hInst, int nCmdShow ) : 
   cglApp(nW, nH, hInst, nCmdShow)
{
   ShowCursor(false);
   _sphericCamera.set(D3DXToRadian(90.0f), D3DXToRadian(45.0f), 60.0f);
   _camera = &_sphericCamera;   

   for (int i = 0; i < MAX_KEYS; i++)
      _keysPressed[i] = false;

   updateWindowSize(nW, nH);
   setDevice(m_pD3D->getDevice());
   setWindowHandle((HWND)m_hWnd);
   setFieldOfView(D3DX_PI / 4);   
   
   SetWindowText((HWND)m_hWnd, getWindowText());

   m_nClearColor = D3DCOLOR_XRGB(0, 0, 0);

   std::vector<std::string> buf;

   buf.push_back("1.png");
   buf.push_back("2.png");
   buf.push_back("3.png");
   buf.push_back("4.png");

   //Constructing the scene: objects
   _scene
      << new MeshObject("ground", "media", "ground_paletted.x", &buf)
      << new MeshObject("castle", "media", "castlesiege.x")
      << new MeshObject("dwarf", "media", "dwarf.x")
      << new MeshObject("airplane", "media", "airplane 2.x");

   //Constructing the scene: lights
   _scene 
      << new PointLight("pointlight", D3DXVECTOR3(0.0f, 15.0f, 10.0f), constants::white)
      << new DirectionalLight("dirlight", D3DXVECTOR3(1.0f, 1.0f, 0.0f), constants::white)
      << new SpotLight("spotlight", D3DXVECTOR3(20.0f, 15.0f, 0.0f),
        D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXToRadian(90), D3DXToRadian(110), constants::white);

   _scene.getLight("pointlight")->toggle();
   _scene.getObject("castle")->scale(0.02f);

   _scene.getObject("dwarf")->scale(6.0f);
   _scene.getObject("dwarf")->translate(0.0f, 0.0f, 20.0f);

   _scene.getObject("airplane")->scale(1.7f);
   _scene.getObject("airplane")->translate(20.0f, 15.0f, 0.0f);

   tr1.init();
   tr2.init();
}

void lab3App::_renderText()
{
   if (getF1())
   {
      tr1.begin();
      tr1.setInsertionPos(5, 5);
      tr1.setForegroundColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f ));
      tr1.drawTextLine("Controls:");
      tr1.drawTextLine("1, 2, 3: lights");
      tr1.drawTextLine("Home: wireframe");
      tr1.drawTextLine("Space: switch cameras (WASD)");
      tr1.drawTextLine("Enter: toggle fullscreen");
      tr1.drawTextLine("U: toggle textures");
      tr1.drawTextLine("F/G/M: toggle Min/Mag/Mip filters");
      tr1.drawTextLine("+/-: change MipMap LOD Bias value");
      tr1.drawTextLine("F1: Hide help");
      tr1.end();

      tr2.begin();
      tr2.setInsertionPos(650, 5);
      tr2.setForegroundColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f ));
      tr2.drawTextLine("Current values:");

      switch (getMipFilter())
      {
      case D3DTEXF_LINEAR:
         tr2.drawFormattedTextLine("Mip filter: LINEAR");
         break;
      case D3DTEXF_POINT:
         tr2.drawFormattedTextLine("Mip filter: NEAREST");
         break;
      case D3DTEXF_NONE:
         tr2.drawFormattedTextLine("Mip filter: NONE");
         break;
      }

      switch (getMinFilter())
      {
      case D3DTEXF_LINEAR:
         tr2.drawFormattedTextLine("Min filter: LINEAR");
         break;
      case D3DTEXF_POINT:
         tr2.drawFormattedTextLine("Min filter: NEAREST");
         break;
      }

      switch (getMagFilter())
      {
      case D3DTEXF_LINEAR:
         tr2.drawFormattedTextLine("Mag filter: LINEAR");
         break;
      case D3DTEXF_POINT:
         tr2.drawFormattedTextLine("Mag filter: NEAREST");
         break;
      }

      tr2.drawFormattedTextLine("LOD Bias: %.1f", getMipmapBias());

      if (_camera == &_sphericCamera)
         tr2.drawFormattedTextLine("Camera: spheric");
      else
         tr2.drawFormattedTextLine("Camera: free");

      tr2.end();
   }
   else
   {
      tr1.begin();
      tr1.setInsertionPos(5, 5);
      tr1.setForegroundColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f ));
      tr1.drawTextLine("F1: Show help");
      tr1.end();
   }
}

void lab3App::renderInternal()
{ 
   D3DXMATRIX matProj;
   D3DXMatrixPerspectiveFovLH(&matProj, getFieldOfView(), getWHRatio(), 0.1f, 1000.0f);

   getDevice()->SetTransform(D3DTS_PROJECTION, &matProj);
   getDevice()->SetTransform(D3DTS_VIEW, _camera->getMatrix());

   _renderText();

   getDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
   getDevice()->SetRenderState(D3DRS_COLORVERTEX, TRUE);
   getDevice()->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);
   getDevice()->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
   getDevice()->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_COLOR2);
   getDevice()->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);

   float bias = getMipmapBias();

   getDevice()->SetSamplerState(0, D3DSAMP_MIPMAPLODBIAS, 
      *((DWORD *)(&bias)));

   getDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, getMipFilter());
   getDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, getMagFilter());
   getDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, getMinFilter());

   Renderer::lightUp(_scene);
   Renderer::render(_scene);
}

void lab3App::update()
{
   if (_keysPressed['W'])
      _camera->move(0, 60);
   if (_keysPressed['S'])
      _camera->move(0, -60);

   if (_keysPressed['A'])
      _camera->move(-60, 0);
   if (_keysPressed['D'])
      _camera->move(60, 0);

   _scene.getObject("airplane")->rotateY(0.01f);
   _scene.getLight("spotlight")->rotateY(0.01f);

   cglApp::update();
}

bool lab3App::processInput( unsigned int nMsg, int wParam, long lParam )
{
   _inputProc.handleMessage(this, nMsg, wParam, lParam);

   return cglApp::processInput(nMsg, wParam, lParam);
}

char const * lab3App::getWindowText()
{
   return "CG Lab 3. Fedor Zentsev, 4057/2";
}

lab3App::~lab3App()
{
}