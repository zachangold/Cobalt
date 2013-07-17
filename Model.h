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

	static Model *load( string fileName );
	
	static void deleteAll( void )
	{
		for ( size_t i = 0; i < loaded.size(); ++i )
		{
			delete loaded[ i ];
		}
		loaded.resize( 0 );
	};

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
	// loading for specific file formats
	void loadRAW( string fileName );
	//void loadMD2( string fileName );

	// Data to keep track of which models are loaded
	static vector< Model * > loaded;
	// fileName for identity comparison between models
	string fileName;

	vector< Vertex > vertices;

	Texture texture;
	VertexBuffer vBuffer;

};

#endif /* ModelH */
