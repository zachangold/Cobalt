#include "CobaltGame.h"


CobaltGame::CobaltGame( void )
{

};


CobaltGame::~CobaltGame( void )
{

};


void CobaltGame::main( void )
{
	while ( !engine.hasQuit() )
	{
		engine.prepare();

		engine.update();

		engine.present();
	}
};

