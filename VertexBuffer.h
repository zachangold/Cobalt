#ifndef VertexBufferH
#define VertexBufferH

#include <iostream>
using namespace std;

#include "glut/Include/GL/glut.h"
#include "glext.h"

extern PFNGLGENBUFFERSARBPROC            pglGenBuffersARB;             // VBO Name Generation Procedure
extern PFNGLBINDBUFFERARBPROC            pglBindBufferARB;             // VBO Bind Procedure
extern PFNGLBUFFERDATAARBPROC            pglBufferDataARB;             // VBO Data Loading Procedure
extern PFNGLBUFFERSUBDATAARBPROC         pglBufferSubDataARB;          // VBO Sub Data Loading Procedure
extern PFNGLDELETEBUFFERSARBPROC         pglDeleteBuffersARB;          // VBO Deletion Procedure
extern PFNGLGETBUFFERPARAMETERIVARBPROC  pglGetBufferParameterivARB;   // return various parameters of VBO
extern PFNGLMAPBUFFERARBPROC             pglMapBufferARB;              // map VBO procedure
extern PFNGLUNMAPBUFFERARBPROC           pglUnmapBufferARB;            // unmap VBO procedure

#define glGenBuffersARB           pglGenBuffersARB
#define glBindBufferARB           pglBindBufferARB
#define glBufferDataARB           pglBufferDataARB
#define glBufferSubDataARB        pglBufferSubDataARB
#define glDeleteBuffersARB        pglDeleteBuffersARB
#define glGetBufferParameterivARB pglGetBufferParameterivARB
#define glMapBufferARB            pglMapBufferARB
#define glUnmapBufferARB          pglUnmapBufferARB


class VertexBuffer
{
public:
	VertexBuffer( void );
	~VertexBuffer( void );

	void load( float *data, int nVertices, int vertexSize );
	void setFormat( GLuint format ) { this->format = format; };
	void draw( void );

private:
	GLuint vbId;
	int nVertices;

	GLuint format;
};

#endif /* VertexBufferH */