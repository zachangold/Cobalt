#include "CobaltGame.h"


CobaltGame::CobaltGame( void )
{

};


CobaltGame::~CobaltGame( void )
{

};


void CobaltGame::main( void )
{
	Window window;
	window.open( "Cobalt" );
	window.setupOpenGL();
	
	while ( true )
	{
		if ( !window.processMessages() ) break;
		glClearColor( 1.0, 0.0, 1.0, 1.0 );
		glClear( GL_COLOR_BUFFER_BIT );

		window.swapGLBuffers();
	}
};