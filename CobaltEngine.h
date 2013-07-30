#ifndef CobaltEngineH
#define CobaltEngineH

#include "Window.h"
#include "Input.h"
#include "Video.h"
#include "Console.h"

class CobaltEngine
{
public:
	CobaltEngine( void );
	~CobaltEngine( void );

	// Each frame should contain prepare->update->present
	void prepare( void )
	{
		if ( !window.processMessages() )
		{
			quit = true;
			return;
		}

		input.update();
		video.update( input );
	};

	void update( void )
	{
		
	};

	void present( void )
	{
		video.render();
		window.swapGLBuffers();
	};


	bool hasQuit( void )
	{
		return quit;
	};

private:
	bool quit;

	Window window;
	Input input;

	Video video;
	Console console;

};

#endif /* CobaltEngineH */