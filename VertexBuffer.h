#ifndef VertexBufferH
#define VertexBufferH

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

	void load( float *vertexData, int nVertices, int vertexSize )
	{
		this->nVertices = nVertices;

		glGenBuffersARB( 1, &vbId );
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, vbId );
		glBufferDataARB( GL_ARRAY_BUFFER_ARB, nVertices * vertexSize, vertexData, GL_STATIC_DRAW_ARB );
	};

	void draw( void )
	{
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, vbId );
		glEnableClientState( GL_VERTEX_ARRAY );
		glVertexPointer( 3, GL_FLOAT, 0, 0 );
		glDrawArrays( GL_TRIANGLES, 0, nVertices );
		glDisableClientState( GL_VERTEX_ARRAY );
	};

private:
	GLuint vbId;
	int nVertices;

};

#endif /* VertexBufferH */