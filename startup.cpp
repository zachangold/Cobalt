#include <iostream>
#include "Window.h"
#include "CobaltGame.h"

#pragma comment( lib, "OpenGL32.Lib" )

using namespace std;


int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow )
{
	Window::hInstance = hInstance;
	Window::hPrevInstance = hPrevInstance;
	Window::lpCmdLine = lpCmdLine;
	Window::nCmdShow = nCmdShow;

	CobaltGame game;
	game.main();


	/*
    MSG msg;

    while ( GetMessage( &msg, NULL, 0, 0 ) )
    {
        TranslateMessage( &msg );
        DispatchMessage( &msg );
    }

    return msg.wParam;
	*/
	return 1;
};

