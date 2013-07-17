#ifndef IndexBufferH
#define IndexBufferH

#include "VertexBuffer.h"

class IndexBuffer
{
public:
	IndexBuffer( void );
	~IndexBuffer( void );

	void load( void *indexData, int nIndices, int indexSize );
	void unload( void );

	void draw( void );
	void draw( int startIndex, int endIndex );

	GLuint ibId;
private:
	int nIndices;
	int indexSize;
};


#endif /* IndexBufferH */