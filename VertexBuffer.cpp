#include "VertexBuffer.h"


VertexBuffer::VertexBuffer( void )
{
	vbId = 0xFFFFFFFF;
};


VertexBuffer::~VertexBuffer( void )
{
	unload();
};


void VertexBuffer::load( float *vertexData, int nVertices, int vertexSize )
{
	unload();
	this->nVertices = nVertices;

	glGenBuffersARB( 1, &vbId );
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, vbId );
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, nVertices * vertexSize, vertexData, GL_STATIC_DRAW_ARB );
};

void VertexBuffer::unload( void )
{
	if ( vbId != 0xFFFFFFFF )
	{
		glDeleteBuffersARB( 1, &vbId );
		vbId = 0xFFFFFFFF;
	}
};

void VertexBuffer::draw( void )
{
	if ( vbId == 0xFFFFFFFF ) return;

	glBindBufferARB( GL_ARRAY_BUFFER_ARB, vbId );
	glEnableClientState( GL_VERTEX_ARRAY );
	glInterleavedArrays( format, 0, NULL );
	glDrawArrays( GL_TRIANGLES, 0, nVertices );
	glDisableClientState( GL_VERTEX_ARRAY );
};
