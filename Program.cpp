#include "Program.h"


/**
 * Sets the program handle to INVALID_HANDLE. To make the program,
 * call create()
 */
Program::Program( void )
{
	handle = INVALID_HANDLE;
};


/**
 * Deletes the program if it has been instantiated.
 */
Program::~Program( void )
{
	destroy();
};


/**
 * Creates the opengl program object so that it can be initialized and 
 * used. Note that this is not done in the constructor to prevent
 * empty programs from being made.
 */
void Program::create( void )
{
	handle = glCreateProgram();
};


/**
 * Attaches a shader object to the program for execution. Note that
 * attach() must be called after create(), but before link() and 
 * use(). The shader passed in must be detached after linking and
 * usage so that the shader can be deleted.
 */
void Program::attach( Shader &shader )
{
	glAttachShader( handle, shader.getHandle() );
};


/**
 * Removes the shader object from the program. Detach() should be
 * called on every attached shader object after link() has been
 * called so that the shaders can be deleted by OpenGL.
 */
void Program::detach( Shader &shader )
{
	glDetachShader( handle, shader.getHandle() );
};


/**
 * Links the attached shader binaries together and prepares the 
 * program for use. This should be done after attaching all 
 * shaders. Once link() is called, shaders should be detached.
 */
void Program::link( void )
{
	glLinkProgram( handle );
};


/**
 * Sets the current rendering program to this Program. Note that
 * this will likely become unused later, when Programs become 
 * part of the Pipeline objects, which will be much more useful
 * for advanced rendering purposes
 */
void Program::use( void )
{
	glUseProgram( handle );
};


/**
 * Deletes the program if it has already been instantiated, which
 * also prevents further use.
 */
void Program::destroy( void )
{
	if ( handle != INVALID_HANDLE )
	{
		glDeleteProgram( handle );
		handle = INVALID_HANDLE;
	}
};


/**
 * Sets a uniform variable in the program with the specified name
 * to the specified integer value.
 */
void Program::setUniform( string uniformName, int value )
{
	glUniform1i( glGetUniformLocation( handle, uniformName.c_str() ), value );
};
