#include <windows.h>
#include <d3dx9.h>

#define _USE_MATH_DEFINES
#include <cmath>

#include "Library/cglD3D.h"

#include "lab2_app.h"
#include "comdef.h"
#include "axes.h"
#include "grid.h"
#include "mesh_object.h"
#include "render_context.h"
#include "utils.h"
#include "light.h"

using namespace cg_labs;

lab2App::lab2App( int nW, int nH, void *hInst, int nCmdShow ) : 
   cglApp(nW, nH, hInst, nCmdShow)
{
   _sphericCamera.set(D3DXToRadian(90.0f), D3DXToRadian(45.0f), 40.0f);
   _camera = &_sphericCamera;   

   for (int i = 0; i < MAX_KEYS; i++)
      _keysPressed[i] = false;

   updateWindowSize(nW, nH);
   setDevice(m_pD3D->getDevice());
   setWindowHandle((HWND)m_hWnd);
   setFieldOfView(D3DX_PI / 4);
   
   getDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

   SetWindowText((HWND)m_hWnd, getWindowText());

   m_nClearColor = D3DCOLOR_XRGB(120, 120, 120);

   //utils::toggleFullScreen();

   //Constructing the scene: objects
   _scene
      << new Grid("ground", grid_functions::plane, grid_functions::planeNormal, 40, 40, constants::white)
      << new MeshObject("car", "media", "car.x", true);

   //Constructing the scene: lights
   _scene 
      << new PointLight("pointlight1", D3DXVECTOR3(17.0f, 5.0f, 0.0f), constants::red)
      << new PointLight("pointlight2", D3DXVECTOR3(12.0f, 5.0f, 4.0f), constants::green)
      << new PointLight("pointlight3", D3DXVECTOR3(12.0f, 5.0f, -4.0f), constants::blue)
      << new DirectionalLight("dirlight", D3DXVECTOR3(4.0f, -1.0f, 0.0f), constants::white)
      << new SpotLight("spotlight", D3DXVECTOR3(0.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f),
      D3DXToRadian(30), D3DXToRadian(60), constants::cyan);

   _scene.getObject("ground")->scale(45.0f, 20.0f, 15.0f);
   _scene.getObject("ground")->translate(-22.5f, 0.0f, -7.5f);
   _scene.getLight("dirlight")->getObject()->rotateZ((float)M_PI / 4);
   _scene.getLight("dirlight")->getObject()->translate(-17.0f, 5.0f, 0.0f);
   _scene.getLight("spotlight")->translate(0.0f, 5.0f, 0.03f);

   tr.init();
}

void lab2App::renderInternal()
{ 
   D3DXMATRIX matProj;
   D3DXMatrixPerspectiveFovLH(&matProj, getFieldOfView(), getWHRatio(), 0.1f, 1000.0f);

   getDevice()->SetTransform(D3DTS_PROJECTION, &matProj);
   getDevice()->SetTransform(D3DTS_VIEW, _camera->getMatrix());

   tr.begin();
   tr.setInsertionPos(5, 5);
   tr.setForegroundColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f ));
   tr.drawTextLine("Controls");
   tr.drawTextLine("1, 2, 3: point lights");
   tr.drawTextLine("4: directional light");
   tr.drawTextLine("5: spot light");
   tr.drawTextLine("Home: wireframe");
   tr.drawTextLine("Space: switch cameras (WASD)");
   tr.drawTextLine("Enter: toggle fullscreen");
   tr.end();

   Renderer::lightUp(_scene);
   Renderer::render(_scene);
}

void lab2App::update()
{
   if (_keysPressed['W'])
      _camera->move(0, 60);
   if (_keysPressed['S'])
      _camera->move(0, -60);

   if (_keysPressed['A'])
      _camera->move(-60, 0);
   if (_keysPressed['D'])
      _camera->move(60, 0);

   if (!_keysPressed['L'])
     _scene.getObject("car")->translate(0.28f * cosf(m_timer.getTime() - 0.1f), 0.0f, 0.0f);
 
  _scene.getLight("spotlight")->translate(0.0f, -5.0f, 0.0f);
  _scene.getLight("spotlight")->rotateZ(0.009f * cosf(m_timer.getTime()));
  _scene.getLight("spotlight")->translate(0.0f, 5.0f, 0.0f);

  _scene.getLight("spotlight")->translate(0.0f, 0.0f, 0.1f * cosf(m_timer.getTime()));

   cglApp::update();
}

bool lab2App::processInput( unsigned int nMsg, int wParam, long lParam )
{
   _inputProc.handleMessage(this, nMsg, wParam, lParam);

   return cglApp::processInput(nMsg, wParam, lParam);
}

char const * lab2App::getWindowText()
{
   return "CG Lab 2. Fedor Zentsev, 4057/2";
}

lab2App::~lab2App()
{
}