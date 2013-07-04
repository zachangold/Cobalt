#ifndef CobaltGameH
#define CobaltGameH

#include "Window.h"
#include "Input.h"

class CobaltGame
{
public:
	CobaltGame( void );
	virtual ~CobaltGame( void );

	void main( void );

private:
	Window window;
	Input input;
};

#endif /* CobaltGameH */