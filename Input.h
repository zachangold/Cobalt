#ifndef InputH
#define InputH

#include <dinput.h>

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


private:
	void initInput( void );
	void initKeyboard( Window& window );
	void initMouse( void );

	void deleteInput( void );
	void deleteKeyboard( void );
	void deleteMouse( void );

	void updateKeyboard( void );
	void updateMouse( void );

	LPDIRECTINPUT8 dInput;

	LPDIRECTINPUTDEVICE8 keyboard;
    char keys[ 256 ];


};


#endif /* InputH */