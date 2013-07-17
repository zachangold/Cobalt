#include "IndexBuffer.h"


IndexBuffer::IndexBuffer( void )
{
	ibId = 0xFFFFFFFF;
};


IndexBuffer::~IndexBuffer( void )
{
	unload();
};

void IndexBuffer::load( void *indexData, int nIndices, int indexSize )
{
	this->nIndices = nIndices;
	this->indexSize = indexSize;

	glGenBuffers( 1, &ibId );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ibId );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, nIndices * indexSize, indexData, GL_STATIC_DRAW );
};

void IndexBuffer::unload( void )
{
	if ( ibId != 0xFFFFFFFF )
	{
		glDeleteBuffers( 1, &ibId );
		ibId = 0xFFFFFFFF;
	}
};

void IndexBuffer::draw( void )
{
	if ( ibId == 0xFFFFFFFF ) return;

	glEnableClientState( GL_ELEMENT_ARRAY_BUFFER );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ibId );
	glDrawElements( GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0 );
	glDisableClientState( GL_ELEMENT_ARRAY_BUFFER );
};

void IndexBuffer::draw( int startIndex, int endIndex )
{
	if ( ibId == 0xFFFFFFFF ) return;

	glEnableClientState( GL_ELEMENT_ARRAY_BUFFER );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ibId );
	glDrawElements( GL_TRIANGLES, endIndex - startIndex, GL_UNSIGNED_INT, ( GLvoid * ) ( startIndex*4 ) );
	glDisableClientState( GL_ELEMENT_ARRAY_BUFFER );
};