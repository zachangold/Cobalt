#include "CobaltGame.h"


CobaltGame::CobaltGame( void )
{

};


CobaltGame::~CobaltGame( void )
{

};


void CobaltGame::main( void )
{
	window.open( "Cobalt" );
	window.setupOpenGL();
	
	input.init( window );

	float x = 100.0;
	float y = 100.0;

	glViewport( 0, 0, 800, 600 );
	glOrtho( 0, 800, 600, 0, 0.0, 1.0 );

	while ( true )
	{
		if ( !window.processMessages() ) break;
		input.update();
		
		if ( input.keyDown( DIK_LEFT ) )	x -= 0.1;
		if ( input.keyDown( DIK_RIGHT ) )	x += 0.1;
		if ( input.keyDown( DIK_UP ) )		y -= 0.1;
		if ( input.keyDown( DIK_DOWN ) )	y += 0.1;
		
		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT );

		glColor3f( 1.0f, 1.0f, 1.0f );
		glPointSize( 2.0f );
		glBegin( GL_POINTS );
			glVertex3f( x - 5, y - 5, 0 );
			glVertex3f( x - 5, y + 5, 0 );
			glVertex3f( x + 5, y + 5, 0 );
			glVertex3f( x + 5, y - 5, 0 );
		glEnd();

		window.swapGLBuffers();
	}
};

