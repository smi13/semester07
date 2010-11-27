/**
  @file     cglMain.cpp
  @brief    WinMain container
  @date     Created on 10/09/2005
  @project  D3DBase
  @author   Bvs
*/

// *******************************************************************
// includes

#include <crtdbg.h>
#include <Windows.h>

#include "lab1_app.h"
#include "myApp.h"

#include "object.h"

/**
  @brief    This function is WinMain for D3DBase project

  @return   Windows error code
  @param    hInstance        standard WinMain input
  @param    hPrevInsatnce    standard WinMain input
  @param    lpszCommandLine  standard WinMain input
  @param    nCmdShow         standard WinMain input
  @author   Bvs
  @see      MSDN =)
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInsatnce,
                   LPTSTR lpszCommandLine, int nCmdShow)
{
   cg_labs::lab1App app(800, 600, (void*)hInstance, nCmdShow);

   if (!app.isFailed())
      app.theLoop();


   //TODO: Not sure how to dump leaks properly for C++.
#ifdef _DEBUG
   //_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
#endif  /* _DEBUG */
   
} // end of WinMain

