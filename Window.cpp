#include "Window.h"

// The four arguments to WinMain (necessary for some functions)
HINSTANCE Window::hInstance;
HINSTANCE Window::hPrevInstance;
LPSTR Window::lpCmdLine;
int Window::nCmdShow;

// The Window class, its name, and if it's already been made and doesn't need to be made again
WNDCLASSEX Window::wc;
const string Window::className = "CobaltWindowClass";
bool windowClassMade = false;


Window::Window( void )
{
	setupWindowClass();
};

Window::~Window( void )
{
    wglMakeCurrent( hdc, NULL );
    wglDeleteContext( hglrc );
    ReleaseDC( hwnd, hdc );
};

void Window::open( string title )
{
    hwnd = CreateWindowEx(
        0,
        className.c_str(),
        title.c_str(),
        0,
        CW_USEDEFAULT, CW_USEDEFAULT, 1680, 1050,
        NULL, NULL, hInstance, NULL );

    if ( hwnd == NULL )
    {
        MessageBox( NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK );
		throw "Error: window cannot be opened.";
    }

	SetWindowPos( hwnd, HWND_TOP, 0, 0, GetSystemMetrics( SM_CXSCREEN ), GetSystemMetrics( SM_CYSCREEN ), SWP_FRAMECHANGED );
	SetWindowLong( hwnd, GWL_STYLE, 0 );
	//SetCursor( NULL );
    ShowWindow( hwnd, nCmdShow );
};

void Window::setupOpenGL( void )
{
	hdc = GetDC( hwnd );

	setupPixelFormat();

	hglrc = wglCreateContext( hdc );

	makeCurrent();
	glViewport( 0, 0, 1680, 1050 );
    UpdateWindow( hwnd );
};

void Window::makeCurrent( void )
{
    wglMakeCurrent( hdc, hglrc );
};

void Window::swapGLBuffers( void )
{
	SwapBuffers( hdc );
};

int Window::processMessages( void )
{
	static MSG msg;

	while ( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
	{
		if ( !GetMessage( &msg, NULL, 0, 0 ) )
		{
			return 0;
		}

        TranslateMessage( &msg );
        DispatchMessage( &msg );
	}

	return 1;
};

HWND Window::getWindowHandle( void )
{
	return hwnd;		
};

void Window::setupWindowClass( void )
{
	if ( windowClassMade ) return;

    // Set the properties of the window class
	memset( &wc, 0, sizeof( wc ) );
    wc.cbSize        = sizeof( WNDCLASSEX );
    wc.style         = CS_OWNDC;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon( NULL, IDI_APPLICATION );
    wc.hCursor       = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = className.c_str();
    wc.hIconSm       = LoadIcon( NULL, IDI_APPLICATION );

    if ( !RegisterClassEx( &wc ) )
    {
        MessageBox( NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK );
		throw "Fatal error: window registration unsuccessful. Windows cannot be created.";
    }

	windowClassMade = true;
};

// This may be moved to an Input class
LRESULT CALLBACK Window::WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch ( msg )
    {
        case WM_CLOSE:
            DestroyWindow( hwnd );
        break;
        case WM_DESTROY:
            PostQuitMessage( 0 );
        break;
		case WM_SETCURSOR:
			SetCursor( NULL );
			return TRUE;
        default:
            return DefWindowProc( hwnd, msg, wParam, lParam );
    }
    return 0;
};


void Window::setupPixelFormat( void )
{
    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof( PIXELFORMATDESCRIPTOR ),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
        PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
        32,                        //Colordepth of the framebuffer.
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        24,                        //Number of bits for the depthbuffer
        8,                        //Number of bits for the stencilbuffer
        0,                        //Number of Aux buffers in the framebuffer.
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };

    int pixelFormat = ChoosePixelFormat( hdc, &pfd );

    SetPixelFormat( hdc, pixelFormat, &pfd );
};

