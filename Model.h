#ifndef ModelH
#define ModelH

#include <iostream>
#include <vector>
using namespace std;

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

private:
	void loadRAW( string fileName );

	vector< Vertex > vertices;
};

#endif /* ModelH */
