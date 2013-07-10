#ifndef TextureH
#define TextureH

#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "glext.h"
#include <iostream>

#include "Picture.h"

using namespace std;

class Texture
{
public:
	Texture( void );
	~Texture( void );

	void load( string fileName );
	void unload( void );

	// sets this texture as the current one in openGL
	void setCurrent( void );

	static const Texture NONE;
	static const Texture DEFAULT;

private:
	GLuint texId;

};

#endif /* TextureH */