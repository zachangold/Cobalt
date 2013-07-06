#ifndef ModelH
#define ModelH

#include <iostream>
#include <vector>
using namespace std;

#include "glut/Include/GL/glut.h"
#include "glext.h"
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

	GLuint glvbo;
private:
	void loadRAW( string fileName );

	vector< Vertex > vertices;

};

#endif /* ModelH */
