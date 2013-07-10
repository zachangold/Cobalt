#include "Model.h"

#include <fstream>
#include "Video.h"
//#include <gl/GL.h>
//#include <gl/GLU.h>

const Model Model::NONE;
const Model Model::DEFAULT;

Model::Model( void )
{

};


Model::~Model( void )
{

};


void Model::load( string fileName )
{
	// file extension
	string ext = fileName.substr( fileName.find_last_of( '.' ), fileName.size() );
	this->fileName = fileName;

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
		v.u = v.x;
		v.v = v.y;

		vertices.push_back( v );
	}

	input.close();

	// generate the vertex buffer object
	vBuffer.setFormat( GL_T2F_V3F );
	vBuffer.load( ( float* ) &vertices[ 0 ], vertices.size(), sizeof( Vertex ) );
};
