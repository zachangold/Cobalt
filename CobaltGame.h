#ifndef CobaltGameH
#define CobaltGameH

#include "Window.h"
#include "Input.h"
#include "Camera.h"
#include "Model.h"
#include "Video.h"
#include "BSPMap.h"


class CobaltGame
{
public:
	CobaltGame( void );
	virtual ~CobaltGame( void );

	void main( void );

private:
	Window window;
	Video video;
	Model *model;
	Input input;
};

#endif /* CobaltGameH */