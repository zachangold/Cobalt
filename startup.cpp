#include <iostream>
#include "Window.h"
#include "CobaltGame.h"

#pragma comment( lib, "OpenGL32.Lib" )
#pragma comment( lib, "glu32.lib" )

using namespace std;


int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	Window::hInstance = hInstance;
	Window::hPrevInstance = hPrevInstance;
	Window::lpCmdLine = lpCmdLine;
	Window::nCmdShow = nCmdShow;

	CobaltGame game;
	game.main();

	return 1;
};

