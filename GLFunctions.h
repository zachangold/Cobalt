#ifndef GLFunctionsH
#define GLFunctionsH

#include "glut/Include/GL/glut.h"
#include "glext.h"
#include "wglext.h"


void loadGLFunctions( void );
void initGL( void );


extern PFNGLGENBUFFERSPROC				glGenBuffers;
extern PFNGLBINDBUFFERPROC				glBindBuffer;
extern PFNGLBUFFERDATAPROC				glBufferData;
extern PFNGLBUFFERSUBDATAPROC			glBufferSubData;
extern PFNGLDELETEBUFFERSPROC			glDeleteBuffers;
extern PFNGLGETBUFFERPARAMETERIVPROC	glGetBufferParameteriv;
extern PFNGLMAPBUFFERPROC				glMapBuffer;
extern PFNGLUNMAPBUFFERPROC				glUnmapBuffer;

extern PFNGLCREATESHADERPROC			glCreateShader;
extern PFNGLSHADERSOURCEPROC			glShaderSource;
extern PFNGLCOMPILESHADERPROC			glCompileShader;

extern PFNGLCREATEPROGRAMPROC			glCreateProgram;
extern PFNGLATTACHSHADERPROC			glAttachShader;
extern PFNGLDETACHSHADERPROC			glDetachShader;
extern PFNGLLINKPROGRAMPROC				glLinkProgram;
extern PFNGLUSEPROGRAMPROC				glUseProgram;
extern PFNGLDELETEPROGRAMPROC			glDeleteProgram;
extern PFNGLDELETESHADERPROC			glDeleteShader;

extern PFNGLACTIVETEXTUREPROC			glActiveTexture;
extern PFNGLCLIENTACTIVETEXTUREPROC		glClientActiveTexture;

extern PFNGLGETUNIFORMLOCATIONPROC		glGetUniformLocation;
extern PFNGLUNIFORM1IPROC				glUniform1i;

extern PFNWGLSWAPINTERVALEXTPROC		wglSwapIntervalEXT;

#endif /* GLFunctionsH */