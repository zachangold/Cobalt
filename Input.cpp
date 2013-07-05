#include "Input.h"
#include "Window.h"

#pragma comment( lib, "dinput8.lib" )
#pragma comment( lib, "dxguid.lib" )

Input::Input( void )
{
	dInput = nullptr;
	keyboard = nullptr;
	mouse = nullptr;

	sensitivity = 0.003;

	initInput();
};

Input::Input( Window& window )
{
	dInput = nullptr;
	keyboard = nullptr;
	mouse = nullptr;

	init( window );
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
	initMouse( window );
};

void Input::update( void )
{
	updateMouse();
	updateKeyboard();
};

bool Input::keyDown( int key )
{
	return keyboardState[ key ] & 0x80;
};

bool Input::buttonDown( int button )
{
	return mouseState.rgbButtons[ button ] & 0x80;
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

void Input::initMouse( Window& window )
{
	DIDEVCAPS mouseCapabilities;

	if ( FAILED( dInput->CreateDevice( GUID_SysMouse, &mouse, NULL ) ) )
	{
		throw "Fatal Error: DirectInput Mouse init failed.";
	}

	if ( FAILED( mouse->SetDataFormat( &c_dfDIMouse2 ) ) )
	{
		throw "Fatal Error: could not set mouse data format";
	}

	if ( FAILED( mouse->SetCooperativeLevel( window.getWindowHandle(), DISCL_BACKGROUND | DISCL_NONEXCLUSIVE ) ) )
	{
		throw "Fatal Error: mouse cooperative level could not be set.";
	}

	if ( FAILED( mouse->Acquire() ) )
	{
		throw "Fatal Error: mouse could not be acquired.";
	}

	mouseCapabilities.dwSize = sizeof( mouseCapabilities );
	mouse->GetCapabilities( &mouseCapabilities );

	if ( !( mouseCapabilities.dwFlags & DIDC_ATTACHED ) )
	{
		throw "Fatal Error: Mouse not attached?";
	}
};


void Input::deleteInput( void )
{
	if ( dInput != nullptr )
	{
		dInput->Release();
		dInput = nullptr;
	}
};

void Input::deleteKeyboard( void )
{
	if ( keyboard != nullptr )
	{
		keyboard->Unacquire();
		keyboard->Release();
		keyboard = nullptr;
	}
};

void Input::deleteMouse( void )
{
	if ( mouse != nullptr )
	{
		mouse->Unacquire();
		mouse->Release();
		mouse = nullptr;
	}
};

void Input::updateKeyboard( void )
{
	keyboard->GetDeviceState( 256, ( void * ) &keyboardState );
};

void Input::updateMouse( void )
{
	memcpy( &prevMouseState, &mouseState, sizeof( DIMOUSESTATE2 ) );

	if ( DIERR_INPUTLOST == mouse->GetDeviceState( sizeof( mouseState ), ( void * ) &mouseState ) )
	{
		mouse->Acquire();
	}

	SetCursorPos( 840, 525 );
};
