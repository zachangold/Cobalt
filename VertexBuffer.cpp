#include "VertexBuffer.h"


VertexBuffer::VertexBuffer( void )
{

};


VertexBuffer::~VertexBuffer( void )
{
	glDeleteBuffersARB( 1, &vbId );
};
