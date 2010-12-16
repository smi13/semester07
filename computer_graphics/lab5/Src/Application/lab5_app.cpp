#include <windows.h>
#include <d3dx9.h>

#define _USE_MATH_DEFINES
#include <cmath>

#include "Library/cglD3D.h"

#include "lab5_app.h"
#include "comdef.h"
#include "axes.h"
#include "mesh_object.h"
#include "render_context.h"
#include "utils.h"
#include "light.h"
#include "cube_texture_creator.h"

using namespace cg_labs;

lab5app::lab5app( int nW, int nH, void *hInst, int nCmdShow ) : 
   cglApp(nW, nH, hInst, nCmdShow)
{
   ShowCursor(false);
   _sphericCamera.set(D3DXToRadian(234.0f), D3DXToRadian(30.0f), 90.0f);
   _camera = &_sphericCamera;   

   //setWorldMatrix(*_camera->getMatrix());

   for (int i = 0; i < MAX_KEYS; i++)
      _keysPressed[i] = false;

   updateWindowSize(nW, nH);
   setDevice(m_pD3D->getDevice());
   setWindowHandle((HWND)m_hWnd);
   setFieldOfView(D3DX_PI / 4);   

   //getDevice()->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(100, 100, 100));
   getDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
   getDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
   getDevice()->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
   getDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
   getDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
   getDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

  // float vertex_fogstart = 50.0f, vertex_fogend = 200.0f, vertex_fogdensity = 0.7f;
  // getDevice()->SetRenderState(D3DRS_FOGENABLE, TRUE);
  // getDevice()->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR); 
  // getDevice()->SetRenderState(D3DRS_FOGSTART, *(DWORD *)&vertex_fogstart); 
  // getDevice()->SetRenderState(D3DRS_FOGEND, *(DWORD *)&vertex_fogend); 
  // getDevice()->SetRenderState(D3DRS_FOGCOLOR, constants::white);
  // getDevice()->SetRenderState(D3DRS_FOGDENSITY, *(DWORD *)&vertex_fogdensity );
   
   SetWindowText((HWND)m_hWnd, getWindowText());

   m_nClearColor = D3DCOLOR_XRGB(0, 0, 0);
   //m_nClearColor = D3DCOLOR_XRGB(255, 255, 255);

   std::vector<std::string> buf;

   //Constructing the scene: objects
   _scene
      << new MeshObject("dwarf", "media", "dwarf.x")
      << new MeshObject("airplane", "media", "airplane 2.x")
      << new MeshObject("castle", "media", "castlesiege.x")
      << new MeshObject("room", "media", "room.x")
      << new MeshObject("chair", "media", "chair.x");      

   float step = 70.0f;

   _scene.getObject("room")->scale(5.0f);
   
   _scene.getObject("chair")->rotateY(D3DXToRadian(180));
   _scene.getObject("chair")->scale(5.0f);
   _scene.getObject("chair")->translate(0.0f, 0.0f, -step);

   _scene.getObject("airplane")->rotateY(D3DXToRadian(-90));
   _scene.getObject("airplane")->scale(2.0f);
   _scene.getObject("airplane")->translate(-step, 6.0f, 0.0f);

   _scene.getObject("dwarf")->rotateY(D3DXToRadian(90));
   _scene.getObject("dwarf")->scale(10.0f);
   _scene.getObject("dwarf")->translate(step, 0.0f, 0.0f);

   _scene.getObject("castle")->rotateY(D3DXToRadian(180));
   _scene.getObject("castle")->scale(0.01f);
   _scene.getObject("castle")->translate(0.0f, 5.0f, step);

   //Constructing the scene: lights
   _scene << new PointLight("pointlight1", D3DXVECTOR3(10.0f, 20.0f, 0.0f), constants::white)
      << new PointLight("pointlight2", D3DXVECTOR3(-10.0f, 20.0f, 0.0f), constants::white)
      << new PointLight("pointlight3", D3DXVECTOR3(0.0f, 20.0f, 10.0f), constants::white)
      << new PointLight("pointlight4", D3DXVECTOR3(0.0f, 20.0f, -10.0f), constants::white);

   //Obtain cube texture
   getDevice()->CreateCubeTexture(512, 1, D3DUSAGE_RENDERTARGET, D3DFMT_X8R8G8B8, 
      D3DPOOL_DEFAULT, &_envTex, NULL);
   CubeTextureCreator::create(&_envTex, _scene);

   //Debug output
   D3DXSaveTextureToFileA("media/mycube.dds", D3DXIFF_DDS, _envTex, 0);

   //Initializing texture renderer
   tr1.init();
   tr2.init();

   //Loading shaders code
   _shader.load("Src/Application/env_vs.hlsl", "Src/Application/env_ps.hlsl");   

   //Loading special mesh, which will be environmental reflection
   DWORD _numMaterials;
   ID3DXBuffer *pMat = NULL;

   //D3DXCreateBox(getDevice(), 5.0f, 5.0f, 5.0f, &_mesh, 0);

   D3DXLoadMeshFromX("media/sphere.x", D3DXMESH_SYSTEMMEM, getDevice(),
      NULL, &pMat, NULL, &_numMaterials, &_mesh);

   if (pMat != NULL)
      pMat->Release();

   D3DXCreateTextureFromFile(getDevice(), 
      "media/wood01.jpg", &_meshTex);
}

void lab5app::_renderText()
{
   if (getF1())
   {
      tr1.begin();
      tr1.setInsertionPos(5, 5);
      tr1.setForegroundColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f ));
      tr1.drawTextLine("Controls:");
      tr1.drawTextLine("Home: wireframe");
      tr1.drawTextLine("Space: switch cameras (WASD)");
      tr1.drawTextLine("Enter: toggle fullscreen");
      tr1.drawTextLine("U: toggle textures");
      tr1.drawTextLine("+/-: change Fresnel power");
      tr1.drawTextLine("F1: Hide help");
      tr1.end();

      tr2.begin();
      tr2.setInsertionPos(650, 5);
      tr2.setForegroundColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f ));
      tr2.drawTextLine("Current values:");

      if (_camera == &_sphericCamera)
         tr2.drawFormattedTextLine("Camera: spheric");
      else
         tr2.drawFormattedTextLine("Camera: free");

      tr2.drawFormattedTextLine("Fresnel power: %.1lf", getFresnelPow());

      tr2.end();
   }
   else
   {
      tr1.begin();
      tr1.setInsertionPos(5, 5);
      tr1.setForegroundColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f ));
      tr1.drawTextLine("F1: Show help");
      tr1.end();
   }
}

void lab5app::_renderEnvMesh( D3DXMATRIX &proj )
{
   D3DMATERIAL9 tmp;
   IDirect3DBaseTexture9 *tmp_tex0, *tmp_tex1;
   getDevice()->GetMaterial(&tmp);
   getDevice()->GetTexture(0, &tmp_tex0);
   getDevice()->GetTexture(1, &tmp_tex1);

   getDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);

   getDevice()->SetTexture(0, _meshTex);    
   getDevice()->SetTexture(1, _envTex);

   D3DXMATRIX world, tmp_mat;
   D3DXMatrixIdentity(&world);

   D3DXMatrixTranslation(&tmp_mat, 0.0f, 1.0f, 0.0f);
   world *= tmp_mat;

   D3DXMatrixScaling(&tmp_mat, 18.0f, 18.0f, 18.0f);
   world *= tmp_mat;

   float det;
   D3DXMatrixInverse(&tmp_mat, &det, &world);
   D3DXMatrixTranspose(&tmp_mat, &tmp_mat);

   D3DXMATRIX mv = world * *(_camera->getMatrix());
   D3DXMATRIX mvp = mv * proj;
   D3DXVECTOR4 eyepos = D3DXVECTOR4(_camera->getEyePos());
   //D3DXVECTOR4 eyepos = D3DXVECTOR4(0.0f, 0.0f, 5.0f, 1.0f);

   _shader.constantTableVS->SetMatrix(getDevice(), "mvp", &mvp);
   _shader.constantTableVS->SetMatrix(getDevice(), "m", &world);
   _shader.constantTableVS->SetMatrix(getDevice(), "inv_trans_m", &tmp_mat);
   _shader.constantTableVS->SetVector(getDevice(), "eyepos", &eyepos);
   _shader.constantTableVS->SetFloat(getDevice(), "fresnel_pow", getFresnelPow());

   _shader.bind();
   _mesh->DrawSubset(0);
   _shader.unbind();

   getDevice()->SetMaterial(&tmp);
   getDevice()->SetTexture(0, tmp_tex0);
   getDevice()->SetTexture(1, tmp_tex1);
}

void lab5app::renderInternal()
{ 
   D3DXMATRIX matProj;
   D3DXMatrixPerspectiveFovLH(&matProj, getFieldOfView(), getWHRatio(), 0.1f, 1000.0f);

   getDevice()->SetTransform(D3DTS_PROJECTION, &matProj);
   getDevice()->SetTransform(D3DTS_VIEW, _camera->getMatrix());      

   _renderEnvMesh(matProj);
   _renderText();

   Renderer::lightUp(_scene);
   Renderer::render(_scene);
}

void lab5app::update()
{
   if (_keysPressed['W'])
      _camera->move(0, 120);
   if (_keysPressed['S'])
      _camera->move(0, -120);

   if (_keysPressed['A'])
      _camera->move(-120, 0);
   if (_keysPressed['D'])
      _camera->move(120, 0);

   cglApp::update();
}

bool lab5app::processInput( unsigned int nMsg, int wParam, long lParam )
{
   _inputProc.handleMessage(this, nMsg, wParam, lParam);

   return cglApp::processInput(nMsg, wParam, lParam);
}

char const * lab5app::getWindowText()
{
   return "CG Lab 2. Fedor Zentsev, 4057/2";
}

lab5app::~lab5app()
{
   _mesh->Release();
   _envTex->Release();
   _meshTex->Release();
}