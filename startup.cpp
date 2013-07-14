#include <iostream>
#include "Window.h"
#include "CobaltGame.h"
#include "Video.h"

#pragma comment( lib, "OpenGL32.Lib" )
#pragma comment( lib, "glu32.lib" )

using namespace std;

#define CRASH_RUN 0
#define SUCCESSFUL_RUN 1

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	Window::hInstance = hInstance;
	Window::hPrevInstance = hPrevInstance;
	Window::lpCmdLine = lpCmdLine;
	Window::nCmdShow = nCmdShow;

	int runResult = SUCCESSFUL_RUN;

	try
	{
		CobaltGame game;
		game.main();
	} 
	catch ( ... )
	{
		runResult = CRASH_RUN;
	}

	Model::deleteAll();
	TextureHandle::deleteAll();
	return runResult;
};

