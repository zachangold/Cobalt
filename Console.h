#ifndef ConsoleH
#define ConsoleH

#include <iostream>
using namespace std;

class Console
{
public:
	Console( void );
	~Console( void );

	void print( string text );

	void setColour( float r, float g, float b, float a );
	//void setColour( Colour c );

	// For console printing on the UI
	void setFadeTime( int millisSincePrint );

private:

};


#endif /* ConsoleH */