#ifndef ProgramH
#define ProgramH

#include <iostream>
#include <windows.h>

#include "glut/Include/GL/glut.h"
#include "glext.h"
#include "Shader.h"

using namespace std;

extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLDETACHSHADERPROC glDetachShader;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLUSEPROGRAMPROC glUseProgram;



class Program
{
public:
	Program( void );
	~Program( void );

	void create( void )
	{
		handle = glCreateProgram();
	};

	void attachShader( Shader &shader )
	{
		glAttachShader( handle, shader.getHandle() );
	};

	void detachShader( Shader &shader )
	{
		glDetachShader( handle, shader.getHandle() );
	};

	void link( void )
	{
		glLinkProgram( handle );
	};

	void use( void )
	{
		glUseProgram( handle );
	};

private:
	GLuint handle;

};


#endif /* ProgramH */