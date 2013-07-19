#ifndef ShaderH
#define ShaderH

#include <windows.h>
#include <iostream>
#include <fstream>

#include "glut/Include/GL/glut.h"
#include "glext.h"

using namespace std;

extern PFNGLCREATESHADERPROC            glCreateShader;
extern PFNGLSHADERSOURCEPROC            glShaderSource;
extern PFNGLCOMPILESHADERPROC           glCompileShader;
extern PFNGLDELETESHADERPROC            glDeleteShader;

class Shader
{
public:
	Shader( void );
	~Shader( void );
	
	void create( GLenum shaderType, string shaderFile )
	{
		destroy();

		ifstream inFile( shaderFile, fstream::ate | fstream::in );
		int fileLen = inFile.tellg();
		inFile.seekg( fstream::beg );
		char *shaderCode = new char[ fileLen ];
		inFile.read( shaderCode, fileLen );
		inFile.close();

		handle = glCreateShader( shaderType );
		glShaderSource( handle, 1, ( const GLchar ** ) &shaderCode, &fileLen );
		glCompileShader( handle );
		delete[] shaderCode;
	};

	void destroy( void )
	{
		if ( handle != 0xFFFFFFFF )
		{
			glDeleteShader( handle );
			handle = 0xFFFFFFFF;
		}
	};

	GLuint getHandle( void )
	{
		return handle;
	};

private:
	GLuint handle;
};

#endif /* ShaderH */

