#include "GLFunctions.h"


#define LOAD_FUNCTION( FUNC ) load( ( void ** ) &FUNC, #FUNC )

PFNGLGENBUFFERSPROC				glGenBuffers			= nullptr;
PFNGLBINDBUFFERPROC				glBindBuffer			= nullptr;
PFNGLBUFFERDATAPROC				glBufferData			= nullptr;
PFNGLBUFFERSUBDATAPROC			glBufferSubData			= nullptr;
PFNGLDELETEBUFFERSPROC			glDeleteBuffers			= nullptr;
PFNGLGETBUFFERPARAMETERIVPROC	glGetBufferParameteriv	= nullptr;
PFNGLMAPBUFFERPROC				glMapBuffer				= nullptr;
PFNGLUNMAPBUFFERPROC			glUnmapBuffer			= nullptr;

PFNGLCREATESHADERPROC			glCreateShader			= nullptr;
PFNGLSHADERSOURCEPROC			glShaderSource			= nullptr;
PFNGLCOMPILESHADERPROC			glCompileShader			= nullptr;

PFNGLCREATEPROGRAMPROC			glCreateProgram			= nullptr;
PFNGLATTACHSHADERPROC			glAttachShader			= nullptr;
PFNGLDETACHSHADERPROC			glDetachShader			= nullptr;
PFNGLLINKPROGRAMPROC			glLinkProgram			= nullptr;
PFNGLUSEPROGRAMPROC				glUseProgram			= nullptr;
PFNGLDELETEPROGRAMPROC			glDeleteProgram			= nullptr;
PFNGLDELETESHADERPROC			glDeleteShader			= nullptr;

PFNGLACTIVETEXTUREPROC			glActiveTexture			= nullptr;
PFNGLCLIENTACTIVETEXTUREPROC	glClientActiveTexture	= nullptr;

PFNGLGETUNIFORMLOCATIONPROC		glGetUniformLocation	= nullptr;
PFNGLUNIFORM1IPROC				glUniform1i				= nullptr;

PFNWGLSWAPINTERVALEXTPROC 		wglSwapIntervalEXT		= nullptr;

bool load( void **function, const char *functionString )
{
	return ( ( *function ) = ( void * ) wglGetProcAddress( functionString ) ) != nullptr;
};

void loadGLFunctions( void )
{
	// Buffer objects
	LOAD_FUNCTION( glGenBuffers );
    LOAD_FUNCTION( glBindBuffer );
    LOAD_FUNCTION( glBufferData );
    LOAD_FUNCTION( glBufferSubData );
    LOAD_FUNCTION( glDeleteBuffers );
    LOAD_FUNCTION( glGetBufferParameteriv );
    LOAD_FUNCTION( glMapBuffer );
    LOAD_FUNCTION( glUnmapBuffer );

	// Shaders
	LOAD_FUNCTION( glCreateShader );
	LOAD_FUNCTION( glShaderSource );
	LOAD_FUNCTION( glCompileShader );
	LOAD_FUNCTION( glDeleteShader );

	// Program objects
	LOAD_FUNCTION( glCreateProgram );
	LOAD_FUNCTION( glAttachShader );
	LOAD_FUNCTION( glDetachShader );
	LOAD_FUNCTION( glLinkProgram );
	LOAD_FUNCTION( glUseProgram );
	LOAD_FUNCTION( glDeleteProgram );
	LOAD_FUNCTION( glGetUniformLocation );
	LOAD_FUNCTION( glUniform1i );

	LOAD_FUNCTION( glActiveTexture );
	LOAD_FUNCTION( glClientActiveTexture );


	LOAD_FUNCTION( wglSwapIntervalEXT );
};

void initGL( void )
{
	loadGLFunctions();

	glEnable( GL_CULL_FACE );
	glFrontFace( GL_CW );

	glEnable( GL_TEXTURE_2D );
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_LIGHTING );

};