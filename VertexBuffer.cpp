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

	glGenBuffers( 1, &vbId );
	glBindBuffer( GL_ARRAY_BUFFER, vbId );
	glBufferData( GL_ARRAY_BUFFER, nVertices * vertexSize, vertexData, GL_STATIC_DRAW );
};

void VertexBuffer::unload( void )
{
	if ( vbId != 0xFFFFFFFF )
	{
		glDeleteBuffers( 1, &vbId );
		vbId = 0xFFFFFFFF;
	}
};

void VertexBuffer::draw( void )
{
	if ( vbId == 0xFFFFFFFF ) return;

	glBindBuffer( GL_ARRAY_BUFFER, vbId );
	//glEnableClientState( GL_VERTEX_ARRAY );
	glInterleavedArrays( format, 0, NULL );
	glDrawArrays( GL_POINTS, 0, nVertices );
	//glDisableClientState( GL_VERTEX_ARRAY );
};


void VertexBuffer::bind( void )
{
	glBindBuffer( GL_ARRAY_BUFFER, vbId );

};

void VertexBuffer::unbind( void )
{

};
