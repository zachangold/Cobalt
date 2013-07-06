#include "CobaltGame.h"


CobaltGame::CobaltGame( void ) : window(), video( window )
{

};


CobaltGame::~CobaltGame( void )
{

};


void CobaltGame::main( void )
{
	window.open( "Cobalt" );
	window.setupOpenGL();
	
	model.load( "mat/monkHiRes.raw" );
	video.model = &model;

	input.init( window );

	while ( true )
	{
		if ( !window.processMessages() ) break;
		input.update();
		video.update( input );

		video.render();

		window.swapGLBuffers();
	}
};

