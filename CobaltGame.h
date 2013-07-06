#ifndef CobaltGameH
#define CobaltGameH

#include "Window.h"
#include "Input.h"
#include "Camera.h"
#include "Video.h"

class CobaltGame
{
public:
	CobaltGame( void );
	virtual ~CobaltGame( void );

	void main( void );

private:
	Window window;
	//Camera camera;
	Video video;
	Model model;
	Input input;
};

#endif /* CobaltGameH */