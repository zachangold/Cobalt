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

	float x = 0.0;
	float y = 0.0;
	float z = -3.0;
	float rot = 0.0;



	while ( true )
	{
		if ( !window.processMessages() ) break;
		input.update();

		camera.update( input );

		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluPerspective( 60.0, 4.0/3.0, 0.1, 100.0 );
		camera.transform();
		glMatrixMode( GL_MODELVIEW );

		
		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT );

		glColor3f( 1.0f, 1.0f, 1.0f );
		glPointSize( 2.0f );

		glLoadIdentity();
		glTranslatef( x, y, z );
		glRotatef( rot, 0, 0, 1.0 );

		glScalef( 0.1f, 0.1f, 0.1f );

		// Draw a wireframe cube
		glBegin( GL_LINES );
			// Front face
			glVertex3f( -5.0f, -5.0f, -5.0f );
			glVertex3f( -5.0f, +5.0f, -5.0f );

			glVertex3f( -5.0f, +5.0f, -5.0f );
			glVertex3f( +5.0f, +5.0f, -5.0f );

			glVertex3f( +5.0f, +5.0f, -5.0f );
			glVertex3f( +5.0f, -5.0f, -5.0f );

			glVertex3f( +5.0f, -5.0f, -5.0f );
			glVertex3f( -5.0f, -5.0f, -5.0f );

			// Back Face
			glVertex3f( -5.0f, -5.0f, +5.0f );
			glVertex3f( -5.0f, +5.0f, +5.0f );

			glVertex3f( -5.0f, +5.0f, +5.0f );
			glVertex3f( +5.0f, +5.0f, +5.0f );

			glVertex3f( +5.0f, +5.0f, +5.0f );
			glVertex3f( +5.0f, -5.0f, +5.0f );

			glVertex3f( +5.0f, -5.0f, +5.0f );
			glVertex3f( -5.0f, -5.0f, +5.0f );

			// Connection between front & back
			glVertex3f( -5.0f, -5.0f, -5.0f );
			glVertex3f( -5.0f, -5.0f, +5.0f );

			glVertex3f( -5.0f, +5.0f, -5.0f );
			glVertex3f( -5.0f, +5.0f, +5.0f );

			glVertex3f( +5.0f, -5.0f, -5.0f );
			glVertex3f( +5.0f, -5.0f, +5.0f );

			glVertex3f( +5.0f, +5.0f, -5.0f );
			glVertex3f( +5.0f, +5.0f, +5.0f );

		glEnd();

		window.swapGLBuffers();
	}
};

