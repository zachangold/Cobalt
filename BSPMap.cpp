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
	/*
	ifstream file( fileName, fstream::in | fstream::binary | fstream::ate );
	int fileLen = file.tellg();
	file.seekg( 0 );
	//vector< char > fileData( fileLen );
	char *fileData = new char[ fileLen ];
	
	file.read( &fileData[ 0 ], fileLen );
	file.close();
	*/

	FILE *file = fopen( fileName.c_str(), "rb" );
	fseek( file, 0L, SEEK_END );
	int fileLen = ftell( file );
	fseek( file, 0L, SEEK_SET );
	char *fileData = new char[ fileLen ];
	fread( fileData, 1, fileLen, file );
	fclose( file );


	// read in the header
	memcpy( &header, &fileData[ 0 ], sizeof( BSPHeader ) );

	Point3f *firstVertex = ( Point3f * ) &fileData[ header.lump[ BSP_VERTEX_LUMP ].offset ];
	for ( int v = 0; v < header.lump[ BSP_VERTEX_LUMP ].length / 12; ++v )
	{
		float temp = (firstVertex+v)->z;
		(firstVertex+v)->z = (firstVertex+v)->x;
		(firstVertex+v)->x = (firstVertex+v)->y;
		(firstVertex+v)->y = temp;
	}

	vBuffer.setFormat( BSP_VERTEX_FORMAT );

	vector< unsigned short > lineList;

	BSPEdge *edgeArray = ( BSPEdge * ) &fileData[ header.lump[ BSP_EDGE_LUMP ].offset ];
	Point3f *vtxArray = ( Point3f * ) &fileData[ header.lump[ BSP_VERTEX_LUMP ].offset ];
	BSPFace *faceArray = ( BSPFace * ) &fileData[ header.lump[ BSP_FACE_LUMP ].offset ];
	__int32 *faceEdgeArray = ( __int32 * ) &fileData[ header.lump[ BSP_FACE_EDGE_LUMP ].offset ];


	int numEdges = header.lump[ BSP_EDGE_LUMP ].length / sizeof( BSPEdge );
	int numVertices = header.lump[ BSP_VERTEX_LUMP ].length / sizeof( Point3f );

	for ( int i = 0; i < header.lump[ BSP_FACE_LUMP ].length / sizeof( BSPFace ); ++i )
	{
		for ( int e = faceArray[ i ].firstEdgeIndex; e < faceArray[ i ].firstEdgeIndex + faceArray[ i ].num_edges; ++e )
		{
			if ( faceEdgeArray[ e ] < 0 )
			{
				lineList.push_back( edgeArray[ -faceEdgeArray[ e ] ].p2 );
				lineList.push_back( edgeArray[ -faceEdgeArray[ e ] ].p1 );
			}
			else
			{
				lineList.push_back( edgeArray[ faceEdgeArray[ e ] ].p1 );
				lineList.push_back( edgeArray[ faceEdgeArray[ e ] ].p2 );
			}
		}
	}

	vBuffer.load( ( float * ) &fileData[ header.lump[ BSP_VERTEX_LUMP ].offset ], 
				  header.lump[ BSP_VERTEX_LUMP ].length / sizeof( Point3f ), sizeof( Point3f ) );

	iBuffer.load( &lineList[ 0 ], lineList.size(), sizeof( Index16 ) );

	delete[] fileData;
};


void BSPMap::draw( Camera &camera )
{
	vBuffer.bind();
	iBuffer.draw();
};



