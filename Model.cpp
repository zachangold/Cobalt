#include "Model.h"

#include <fstream>
#include "Video.h"
//#include <gl/GL.h>
//#include <gl/GLU.h>

const Model Model::NONE;
const Model Model::DEFAULT;
vector< Model * > Model::loaded;

Model::Model( void )
{

};


Model::~Model( void )
{

};

Model *Model::load( string fileName )
{
	// search for another Model object with the same filename
	for ( size_t i = 0; i < loaded.size(); ++i )
	{
		if ( loaded[ i ]->fileName.compare( fileName ) == 0 )
		{
			return loaded[ i ];
		}
	}

	// If this model hasn't already been loaded, make a new one

	// file extension
	string ext = fileName.substr( fileName.find_last_of( '.' ), fileName.size() );
	Model *m = new Model();
	m->fileName = fileName;

	if ( ext.compare( ".raw" ) == 0 )
	{
		m->loadRAW( fileName );
	}
	else
	{
		throw "Error: model file format not recognized";
	}

	loaded.push_back( m );
	return m;
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
