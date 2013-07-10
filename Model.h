#ifndef ModelH
#define ModelH

#include <iostream>
#include <vector>
using namespace std;

#include "VertexBuffer.h"
#include "Texture.h"

typedef struct
{
	float u, v;
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

	static const Model NONE;
	static const Model DEFAULT;


private:
	void loadRAW( string fileName );

	static vector< Model * > loaded;

	vector< Vertex > vertices;
	string fileName;

	Texture texture;
	VertexBuffer vBuffer;

};

#endif /* ModelH */
