#include <d3dx9.h>

#include "cube_texture_creator.h"
#include "render_context.h"
#include "scene.h"

using namespace cg_labs;

void CubeTextureCreator::create( IDirect3DCubeTexture9 **tex, Scene &scene )
{
   D3DXMATRIX matProjSave, matViewSave;
   getDevice()->GetTransform(D3DTS_VIEW,       &matViewSave);
   getDevice()->GetTransform(D3DTS_PROJECTION, &matProjSave);

   // Store the current back buffer and z-buffer
   LPDIRECT3DSURFACE9 pBackBuffer, pZBuffer;

   getDevice()->GetRenderTarget(0, &pBackBuffer);
   getDevice()->GetDepthStencilSurface(&pZBuffer);

   // Use 90-degree field of view in the projection
   D3DXMATRIX matProj;
   D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 2, 1.0f, 0.5f, 1000.0f);
   getDevice()->SetTransform(D3DTS_PROJECTION, &matProj);

   // Loop through the six faces of the cube map
   for(DWORD i = 0; i < 6; i++)
   {
      float eye_y = 6.1f;
      // Standard view that will be overridden below
      D3DXVECTOR3 vEnvEyePt = D3DXVECTOR3(0.0f, eye_y, 0.0f);
      D3DXVECTOR3 vLookatPt, vUpVec;

      switch(i)
      {
      case D3DCUBEMAP_FACE_POSITIVE_X:
         vLookatPt = D3DXVECTOR3(eye_y, eye_y, 0.0f);
         vUpVec    = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
         break;
      case D3DCUBEMAP_FACE_NEGATIVE_X:
         vLookatPt = D3DXVECTOR3(-eye_y, eye_y, 0.0f);
         vUpVec    = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
         break;
      case D3DCUBEMAP_FACE_POSITIVE_Y:
         vLookatPt = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
         vUpVec    = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
         break;
      case D3DCUBEMAP_FACE_NEGATIVE_Y:
         vLookatPt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
         vUpVec    = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
         break;
      case D3DCUBEMAP_FACE_POSITIVE_Z:
         vLookatPt = D3DXVECTOR3(0.0f, eye_y, eye_y);
         vUpVec    = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
         break;
      case D3DCUBEMAP_FACE_NEGATIVE_Z:
         vLookatPt = D3DXVECTOR3(0.0f, eye_y, -eye_y);
         vUpVec    = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
         break;
      }

      D3DXMATRIX matView;
      D3DXMatrixLookAtLH(&matView, &vEnvEyePt, &vLookatPt, &vUpVec);
      getDevice()->SetTransform(D3DTS_VIEW, &matView);

      // Get pointer to surface in order to render to it
      LPDIRECT3DSURFACE9 pFace;
      (*tex)->GetCubeMapSurface((D3DCUBEMAP_FACES)i, 0, &pFace);

      getDevice()->SetRenderTarget(0, pFace);

      getDevice()->BeginScene();
      getDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
        D3DCOLOR_COLORVALUE(0.0f,0.0f,0.0f,1.0f), 1.0f, 0);
      Renderer::lightUp(scene);
      Renderer::render(scene);
      getDevice()->EndScene();

      pFace->Release();

      /*LPD3DXRENDERTOSURFACE asd;
      D3DSURFACE_DESC desc;

      pFace->GetDesc(&desc);

      HRESULT hr = D3DXCreateRenderToSurface(getDevice(), 
         desc.Width, 
         desc.Height, 
         desc.Format, 
         TRUE, 
         D3DFMT_D16, 
         &asd);

      asd->BeginScene(pFace, NULL);

      getDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
         D3DCOLOR_COLORVALUE(0.0f,0.0f,0.0f,1.0f), 1.0f, 0);
      
      Renderer::lightUp(scene);
      Renderer::render(scene);
      asd->EndScene(0);

      asd->Release();
      pFace->Release();*/
   }

   // Change the render target back to the main back buffer.
   getDevice()->SetRenderTarget(0, pBackBuffer);
   getDevice()->SetDepthStencilSurface(pZBuffer);
   pBackBuffer->Release();
   pZBuffer->Release();

   // Restore the original transformation matrices
   getDevice()->SetTransform(D3DTS_VIEW,       &matViewSave);
   getDevice()->SetTransform(D3DTS_PROJECTION, &matProjSave);
}