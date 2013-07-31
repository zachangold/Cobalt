#ifndef ProgramH
#define ProgramH

#include <iostream>
#include <windows.h>

#include "GLFunctions.h"
#include "Shader.h"

using namespace std;

/**
 * Stores a handle to an OpenGL shader program, which is several
 * individual shaders compiled and linked together.
 *
 * In general, usage of the program class is as follows:
 * create();
 * attach( shader1 );
 * attach( shader2 );
 * ...
 * link();
 * setUniform( ... );
 * ...
 * use();
 * destroy(); (optional; this is handled by the destructor)
 */
class Program
{
public:
	/**
	 * Sets the program handle to INVALID_HANDLE. To make the program,
	 * call create()
	 */
	Program( void );

	/**
	 * Deletes the program if it has been instantiated.
	 */
	~Program( void );

	/**
	 * Creates the opengl program object so that it can be initialized and 
	 * used. Note that this is not done in the constructor to prevent
	 * empty programs from being made.
	 */
	void create( void );

	/**
	 * Attaches a shader object to the program for execution. Note that
	 * attach() must be called after create(), but before link() and 
	 * use(). The shader passed in must be detached after linking and
	 * usage so that the shader can be deleted.
	 */
	void attach( Shader &shader );

	/**
	 * Removes the shader object from the program. Detach() should be
	 * called on every attached shader object after link() has been
	 * called so that the shaders can be deleted by OpenGL.
	 */
	void detach( Shader &shader );

	/**
	 * Links the attached shader binaries together and prepares the 
	 * program for use. This should be done after attaching all 
	 * shaders. Once link() is called, shaders should be detached.
	 */
	void link( void );

	/**
	 * Sets the current rendering program to this Program. Note that
	 * this will likely become unused later, when Programs become 
	 * part of the Pipeline objects, which will be much more useful
	 * for advanced rendering purposes
	 */
	void use( void );

	/**
	 * Deletes the program if it has already been instantiated, which
	 * also prevents further use.
	 */
	void destroy( void );

	/**
	 * Sets a uniform variable in the program with the specified name
	 * to the specified integer value.
	 */
	void setUniform( string uniformName, int value );

	
private:
	// The handle to the opengl program
	GLuint handle;
};


#endif /* ProgramH */