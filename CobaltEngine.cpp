#include "CobaltEngine.h"


CobaltEngine::CobaltEngine( void ) : window(), video( window )
{
	quit = false;

	window.open( "Cobalt" );
	window.setupOpenGL();
	video.init();
	
	input.init( window );
};


CobaltEngine::~CobaltEngine( void )
{

};
