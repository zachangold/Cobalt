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

class Shader
{
public:
	Shader( void );
	~Shader( void );
	
	void create( GLenum shaderType, string shaderFile )
	{
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



	GLuint getHandle( void )
	{
		return handle;
	};

private:
	GLuint handle;
};

#endif /* ShaderH */

