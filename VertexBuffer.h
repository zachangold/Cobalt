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

/**
 * An abstraction of the OpenGL Vertex Buffer Object (structure for
 * allocating graphics card memory for vertices).
 * 
 * TODO: add support for machines where VBOs are not supported by
 * using a vertex array in general memory.
 */
class VertexBuffer
{
public:
	/**
	 * Initializes an invalid vertex buffer object
	 */
	VertexBuffer( void );

	/**
	 * Deallocates the vertex buffer object if it is valid
	 */
	~VertexBuffer( void );

	/**
	 * Creates and initializes the vertex buffer object with the vertex
	 * information pointed to by the data parameter
	 *
	 * @param data a pointer to the vertex information
	 * @param nVertices the number of vertices in the vertex array
	 * @param vertexSize the size of each vertex, in bytes
	 */
	void load( float *data, int nVertices, int vertexSize );

	/**
	 * Deallocates the OpenGL vertex buffer object, invalidating the
	 * vertex buffer.
	 */
	void unload( void );

	/**
	 * Sets the vertex format to one of OpenGL's predefined formats,
	 * which is sent to the glInterleavedArrays() function.
	 *
	 * @param format the vertex format constant describing the vertex
	 *               information
	 */
	void setFormat( GLuint format ) { this->format = format; };

	/**
	 * Draws the VertexBuffer as a list of triangles. Note: most drawing
	 * should be done with index buffers (not yet implemented, 13/7/13)
	 */
	void draw( void );

private:
	/**
	 * The handle to the vertex buffer in graphics memory
	 */
	GLuint vbId;

	/**
	 * The number of vertices stored in the vertex buffer
	 */
	int nVertices;

	/**
	 * The format of the vertex information (OpenGL constant, see 
	 * documentation for glInterleavedArrays)
	 */
	GLuint format;
};

#endif /* VertexBufferH */