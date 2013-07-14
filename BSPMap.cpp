#include "BSPMap.h"
#include <fstream>
using namespace std;

BSPMap::BSPMap( void )
{

};


BSPMap::~BSPMap( void )
{

};


void BSPMap::load( string fileName )
{
	ifstream file( fileName, fstream::in | fstream::binary | fstream::ate );
	int fileLen = file.tellg();
	file.seekg( 0 );
	vector< char > fileData( fileLen );
	file.read( &fileData[ 0 ], fileLen );
	file.close();

	// read in the header
	memcpy( &header, &fileData[ 0 ], sizeof( BSPHeader ) );

	/*
	Point3f *firstVertex = ( Point3f * ) &fileData[ header.lump[ BSP_VERTEX_LUMP ].offset ];
	for ( int v = 0; v < header.lump[ BSP_VERTEX_LUMP ].length / 12; ++v )
	{
		float temp = (firstVertex+v)->y;
		(firstVertex+v)->y = (firstVertex+v)->x;
		(firstVertex+v)->x = (firstVertex+v)->z;
		(firstVertex+v)->z = temp;
	}
	*/

	vBuffer.setFormat( BSP_VERTEX_FORMAT );
	vBuffer.load( ( float * ) &fileData[ header.lump[ BSP_VERTEX_LUMP ].offset ], 
				  header.lump[ BSP_VERTEX_LUMP ].length / sizeof( Point3f ), sizeof( Point3f ) );

	iBuffer.load( &fileData[ header.lump[ BSP_EDGE_LUMP ].offset ], header.lump[ BSP_EDGE_LUMP ].length / sizeof( Index16 ), sizeof( Index16 ) );
};


void BSPMap::draw( Camera &camera )
{
	glBindBuffer( GL_ARRAY_BUFFER, vBuffer.vbId );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, iBuffer.ibId );
	glEnableClientState( GL_ELEMENT_ARRAY_BUFFER );
	glEnableClientState( GL_VERTEX_ARRAY );
	glVertexPointer( 3, GL_FLOAT, 0, 0 );
	glDrawElements( GL_LINES, header.lump[ BSP_EDGE_LUMP ].length / 4, GL_UNSIGNED_SHORT, 0 );

	//vBuffer.draw();

	//vBuffer.bind();
	//iBuffer.draw();
	//vBuffer.unbind();
};



