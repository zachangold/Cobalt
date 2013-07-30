#ifndef CobaltGameH
#define CobaltGameH

#include "CobaltEngine.h"

class CobaltGame
{
public:
	CobaltGame( void );
	virtual ~CobaltGame( void );

	void main( void );

private:
	CobaltEngine engine;
};

#endif /* CobaltGameH */