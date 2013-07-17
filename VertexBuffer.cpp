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

	glLineWidth( 2.0f );
	glDisable( GL_LIGHTING );
	glDisable( GL_TEXTURE_2D );
	glColor3f( 0.0, 1.0, 0.0 );

	glBindBuffer( GL_ARRAY_BUFFER, vbId );
	glEnableClientState( GL_VERTEX_ARRAY );
	glInterleavedArrays( format, 0, NULL );
	glDrawArrays( GL_LINES, 0, nVertices );
	glDisableClientState( GL_VERTEX_ARRAY );

	glColor3f( 1.0, 1.0, 1.0 );
	glEnable( GL_LIGHTING );
	glEnable( GL_TEXTURE_2D );
};


void VertexBuffer::bind( void )
{
	glBindBuffer( GL_ARRAY_BUFFER, vbId );
	glInterleavedArrays( format, 0, NULL );

};

void VertexBuffer::unbind( void )
{

};
