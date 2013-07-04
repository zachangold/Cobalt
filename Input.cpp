#include "Input.h"
#include "Window.h"

#pragma comment( lib, "dinput8.lib" )
#pragma comment( lib, "dxguid.lib" )

Input::Input( void )
{
	dInput = NULL;
	keyboard = NULL;

	initInput();
};

Input::Input( Window& window )
{
	dInput = NULL;
	keyboard = NULL;

	initInput();
	initKeyboard( window );
	initMouse();
};


Input::~Input( void )
{
	deleteMouse();
	deleteKeyboard();
	deleteInput();
};

void Input::init( Window& window )
{
	deleteKeyboard();
	deleteMouse();
	deleteInput();

	initInput();
	initKeyboard( window );
	initMouse();
};

void Input::update( void )
{
	updateMouse();
	updateKeyboard();
};

bool Input::keyDown( int key )
{
	return keys[ key ] & 0x80;
};

void Input::initInput( void )
{
	if ( FAILED( DirectInput8Create( GetModuleHandle( NULL ),
								    DIRECTINPUT_VERSION,
								    IID_IDirectInput8,
								    ( void** ) &dInput,
								    NULL ) ) )
	{
		throw "Fatal Error: DirectInput initialization failed.";
	}
};

void Input::initKeyboard( Window& window )
{
	if ( FAILED( dInput->CreateDevice( GUID_SysKeyboard, &keyboard, NULL ) ) )
	{
		throw "Fatal Error: DirectInput Keyboard initialization failed.";
	}

	if ( FAILED( keyboard->SetDataFormat( &c_dfDIKeyboard ) ) )
	{
		throw "Fatal Error: DirectInput Keyboard SetDataFormat() failed.";
	}

	if ( FAILED( keyboard->SetCooperativeLevel( window.getWindowHandle(), DISCL_BACKGROUND | DISCL_NONEXCLUSIVE ) ) )
	{
		throw "Fatal Error: DirectInput Keyboard SetCooperativeLevel() failed.";
	}

	if ( FAILED( keyboard->Acquire() ) )
	{
		throw "Fatal Error: DirectInput Keyboard could not be acquired.";
	}
};

void Input::initMouse( void )
{
	
};


void Input::deleteInput( void )
{
	if ( dInput != NULL )
	{
		dInput->Release();
		dInput = NULL;
	}
};

void Input::deleteKeyboard( void )
{
	if ( keyboard != NULL )
	{
		keyboard->Unacquire();
		keyboard->Release();
		keyboard = NULL;
	}
};

void Input::deleteMouse( void )
{

};

void Input::updateKeyboard( void )
{
	keyboard->GetDeviceState( 256, ( void * ) &keys );
};

void Input::updateMouse( void )
{

};
