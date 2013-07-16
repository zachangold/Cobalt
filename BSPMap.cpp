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


	BSPEdge *edgeArray = ( BSPEdge * ) &fileData[ header.lump[ BSP_EDGE_LUMP ].offset ];
	Point3f *vtxArray = ( Point3f * ) &fileData[ header.lump[ BSP_VERTEX_LUMP ].offset ];
	BSPFace *faceArray = ( BSPFace * ) &fileData[ header.lump[ BSP_FACE_LUMP ].offset ];
	__int32 *faceEdgeArray = ( __int32 * ) &fileData[ header.lump[ BSP_FACE_EDGE_LUMP ].offset ];


	int numEdges = header.lump[ BSP_EDGE_LUMP ].length / sizeof( BSPEdge );
	int numVertices = header.lump[ BSP_VERTEX_LUMP ].length / sizeof( Point3f );

	// contains indices into vertices
	vector< Index32 > triList;

	// contains a set of vertices for each BSPFace
	vector< BSPVertex > vertices;

	for ( int i = 0; i < header.lump[ BSP_FACE_LUMP ].length / sizeof( BSPFace ); ++i )
	{
		vector< BSPEdge > polyEdges;

		// Set up the list of edges in order
		for ( int e = faceArray[ i ].firstEdgeIndex; e < faceArray[ i ].firstEdgeIndex + faceArray[ i ].num_edges; ++e )
		{
			if ( faceEdgeArray[ e ] < 0 )
			{
				BSPEdge reversedEdge;
				reversedEdge.p1 = edgeArray[ -faceEdgeArray[ e ] ].p2;
				reversedEdge.p2 = edgeArray[ -faceEdgeArray[ e ] ].p1;
				polyEdges.push_back( reversedEdge );
			}
			else
			{
				polyEdges.push_back( edgeArray[ faceEdgeArray[ e ] ] );
			}
		}

		// Add the polygon's vertices
		for ( int d = 0; d < polyEdges.size(); ++d )
		{
			BSPVertex vtx;
			vtx.x = vtxArray[ polyEdges[ d ].p1 ].x;
			vtx.y = vtxArray[ polyEdges[ d ].p1 ].y;
			vtx.z = vtxArray[ polyEdges[ d ].p1 ].z;

			// Calculate texture coordinates here
			//vtx.u = 0.0;
			//vtx.v = 0.0;

			// Add the vertex to the end of the vertex buffer
			vertices.push_back( vtx );
		}

		// Set up the indices for the triangles
		for ( int idx = vertices.size() - polyEdges.size() + 2; idx < vertices.size(); ++idx )
		{
			// fan the polygon from the first vertex
			triList.push_back( vertices.size() - polyEdges.size() );

			triList.push_back( idx - 1 );
			triList.push_back( idx );
		}
	}

	//vBuffer.load( ( float * ) &fileData[ header.lump[ BSP_VERTEX_LUMP ].offset ], 
	//			  header.lump[ BSP_VERTEX_LUMP ].length / sizeof( Point3f ), sizeof( Point3f ) );

	vBuffer.load( ( float * ) &vertices[ 0 ], vertices.size(), sizeof( BSPVertex ) );
	iBuffer.load( &triList[ 0 ], triList.size(), sizeof( Index32 ) );

	delete[] fileData;
};


void BSPMap::draw( Camera &camera )
{
	vBuffer.bind();
	iBuffer.draw();
};



