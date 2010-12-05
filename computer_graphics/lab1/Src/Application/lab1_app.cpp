#include <windows.h>
#include <d3dx9.h>

#define _USE_MATH_DEFINES
#include <cmath>

#include "Library/cglD3D.h"

#include "lab1_app.h"
#include "comdef.h"
#include "axes.h"
#include "grid.h"
#include "render_context.h"
#include "utils.h"

using namespace cg_labs;

lab1App::lab1App( int nW, int nH, void *hInst, int nCmdShow ) : 
   cglApp(nW, nH, hInst, nCmdShow), _camera(D3DXToRadian(35.0f), D3DXToRadian(37.5f), 11.0f)
{
   for (int i = 0; i < MAX_KEYS; i++)
      _keysPressed[i] = false;

   updateWindowSize(nW, nH);
   setDevice(m_pD3D->getDevice());
   setWindowHandle((HWND)m_hWnd);
   setFieldOfView(D3DX_PI / 4);
   
   // Some rendering settings. Specific for Lab1, though.
   getDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);   
   getDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

   SetWindowText((HWND)m_hWnd, getWindowText());

   m_nClearColor = D3DCOLOR_XRGB(0, 0, 0);

   // Constructing the scene
   _scene << new Axes("axes", 4.0f) 
          << new Grid("torus", grid_functions::torus, 30, 30)
          << new Grid("sphere", grid_functions::sphere, 30, 30, false)
          << new Grid("cone", grid_functions::cone, 30, 30, false)
          << new Grid("cylinder", grid_functions::cylinder, 30, 30, false)
          << new Grid("moebius_strip", grid_functions::moebius_strip, 30, 30, false);

   _scene.getObject("torus")->scale(0.4f);
   _enabledObject = _scene.getObject("torus");
   _enabledObject->translate(2.0f, 2.0f, 2.0f);
}

void lab1App::renderInternal()
{ 
   D3DXMATRIX matProj;
   D3DXMatrixPerspectiveFovLH(&matProj, getFieldOfView(), getWHRatio(), 0.1f, 1000.0f);

   getDevice()->SetTransform(D3DTS_PROJECTION, &matProj);
   getDevice()->SetTransform(D3DTS_VIEW, _camera.getMatrix());

   Renderer::renderScene(&_scene);
}

void lab1App::update()
{
   _enabledObject->translate(-2.0f, -2.0f, -2.0f);

   if (_keysPressed[VK_RIGHT])
      _enabledObject->rotateX(D3DXToRadian(2));
   if (_keysPressed[VK_LEFT])
      _enabledObject->rotateX(-D3DXToRadian(2));
   if (_keysPressed[VK_UP])
      _enabledObject->rotateZ(D3DXToRadian(2));
   if (_keysPressed[VK_DOWN])
      _enabledObject->rotateZ(-D3DXToRadian(2));

   if (_keysPressed['1'])
   {
      _enabledObject->setVisible(false);
      _enabledObject = _scene.getObject("torus");
      _enabledObject->setVisible(true);
   }

   if (_keysPressed['2'])
   {
      _enabledObject->setVisible(false);
      _enabledObject = _scene.getObject("sphere");
      _enabledObject->setVisible(true);
   }

   if (_keysPressed['3'])
   {
      _enabledObject->setVisible(false);
      _enabledObject = _scene.getObject("cone");
      _enabledObject->setVisible(true);
   }

   if (_keysPressed['4'])
   {
      _enabledObject->setVisible(false);
      _enabledObject = _scene.getObject("cylinder");
      _enabledObject->setVisible(true);
   }

   if (_keysPressed['5'])
   {
      _enabledObject->setVisible(false);
      _enabledObject = _scene.getObject("moebius_strip");
      _enabledObject->setVisible(true);
   }

   _enabledObject->translate(2.0f, 2.0f, 2.0f);

   cglApp::update();
}

char const * lab1App::getWindowText()
{
   return "CG Lab 1. Fedor Zentsev, 4057/2";
}

lab1App::~lab1App()
{
}