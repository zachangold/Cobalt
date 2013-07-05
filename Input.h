#ifndef InputH
#define InputH

#include <dinput.h>

#define DIMOUSE_LEFTBUTTON   0
#define DIMOUSE_RIGHTBUTTON  1
#define DIMOUSE_MIDDLEBUTTON 2
#define DIMOUSE_4BUTTON      3
#define DIMOUSE_5BUTTON      4

class Window;

class Input
{
public:
	Input( void );
	Input( Window& window );
	~Input( void );

	void init( Window& window );

	void update( void );
	bool keyDown( int key );
	bool buttonDown( int button );

	float getRelX( void )
	{
		return float( mouseState.lX );// - prevMouseState.lX );
	}
	float getRelY( void )
	{
		return float( mouseState.lY );// - prevMouseState.lY );
	};

	float getSensitivity( void )
	{
		return sensitivity;
	}

private:
	void initInput( void );
	void initKeyboard( Window& window );
	void initMouse( Window& window );

	void deleteInput( void );
	void deleteKeyboard( void );
	void deleteMouse( void );

	void updateKeyboard( void );
	void updateMouse( void );


	LPDIRECTINPUT8 dInput;
	LPDIRECTINPUTDEVICE8 keyboard;
	LPDIRECTINPUTDEVICE8 mouse;

	char keyboardState[ 256 ];
	DIMOUSESTATE2 mouseState;
	DIMOUSESTATE2 prevMouseState; // Mouse state from previous update
	bool invertedY;
    float sensitivity;
	float cursorX;
    float cursorY;

};


#endif /* InputH */