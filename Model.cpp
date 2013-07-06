#include "Model.h"

#include <fstream>


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
};
