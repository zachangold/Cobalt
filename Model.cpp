#include "Model.h"

#include <fstream>
#include "Video.h"
//#include <gl/GL.h>
//#include <gl/GLU.h>
#include "glut/Include/GL/glut.h"
#include "glext.h"

Model::Model( void )
{

};


Model::~Model( void )
{
	glDeleteBuffersARB( 1, &glvbo );
};


void Model::load( string fileName )
{
	// file extension
	string ext = fileName.substr( fileName.find_last_of( '.' ), fileName.size() );
	if ( ext.compare( ".raw" ) == 0 )
	{
		loadRAW( fileName );
	}
	else
	{
		throw "Error: model file format not recognized";
	}
};


void Model::loadRAW( string fileName )
{
	ifstream input( fileName );
	
	Vertex v;
	while ( !input.eof() )
	{
		input >> v.x;
		input >> v.y;
		input >> v.z;

		vertices.push_back( v );
	}

	input.close();

	// generate the vertex buffer object
	glGenBuffersARB( 1, &glvbo );
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, glvbo );
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, sizeof( Vertex ) * vertices.size(), &vertices[ 0 ], GL_STATIC_DRAW_ARB );

};
