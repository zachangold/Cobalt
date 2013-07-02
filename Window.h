#ifndef WindowH
#define WindowH

#include <iostream>
#include <windows.h>
#include <GL/GL.h>
using namespace std;


/**
 * 
 * 
 */
class Window
{
public:
	Window( void );
	~Window( void );

	void open( string title );
	void setupOpenGL( void );
	void makeCurrent( void );

	// Updates the openGL buffer to the screen
	void swapGLBuffers( void );

	// Goes through the message queue until it's empty
	// returns 0 if WM_QUIT is received, 1 otherwise
	int processMessages( void );

	static HINSTANCE hInstance;
	static HINSTANCE Window::hPrevInstance;
	static LPSTR Window::lpCmdLine;
	static int Window::nCmdShow;

private:
	// initialize the WNDCLASSX structure so that we can make windows with it
	static void setupWindowClass( void );
	static LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );

	void setupPixelFormat( void );
	
	static WNDCLASSEX wc;
	static const string className;


	HWND hwnd;
    HDC hdc;
	HGLRC hglrc;


};

#endif /* WindowH */