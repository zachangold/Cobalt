#ifndef ModelH
#define ModelH

#include <iostream>
#include <vector>
using namespace std;

#include "VertexBuffer.h"

typedef struct
{
	float x, y, z;
} Vertex;

class Model
{
public:
	Model( void );
	virtual ~Model( void );

	void load( string fileName );
	vector< Vertex > &getVertices( void )
	{
		return vertices;
	};

	VertexBuffer& getVBO( void )
	{
		return vBuffer;
	};

private:
	void loadRAW( string fileName );

	vector< Vertex > vertices;
	VertexBuffer vBuffer;
};

#endif /* ModelH */
