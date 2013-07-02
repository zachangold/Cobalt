#ifndef CobaltGameH
#define CobaltGameH

#include "Window.h"

class CobaltGame
{
public:
	CobaltGame( void );
	virtual ~CobaltGame( void );

	void main( void );

private:
	Window window;

};

#endif /* CobaltGameH */