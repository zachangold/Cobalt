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

	/*
	Point3f *firstVertex = ( Point3f * ) &fileData[ header.lump[ BSP_VERTEX_LUMP ].offset ];
	for ( int v = 0; v < header.lump[ BSP_VERTEX_LUMP ].length / 12; ++v )
	{
		float temp = (firstVertex+v)->z;
		(firstVertex+v)->z = (firstVertex+v)->x;
		(firstVertex+v)->x = (firstVertex+v)->y;
		(firstVertex+v)->y = temp;
	}
	*/


	BSPEdge *edgeArray = ( BSPEdge * ) &fileData[ header.lump[ BSP_EDGE_LUMP ].offset ];
	Point3f *vtxArray = ( Point3f * ) &fileData[ header.lump[ BSP_VERTEX_LUMP ].offset ];
	BSPFace *faceArray = ( BSPFace * ) &fileData[ header.lump[ BSP_FACE_LUMP ].offset ];
	__int32 *faceEdgeArray = ( __int32 * ) &fileData[ header.lump[ BSP_FACE_EDGE_LUMP ].offset ];
	BSPTexInfo *texInfoArray = ( BSPTexInfo * ) &fileData[ header.lump[ BSP_TEX_INFO_LUMP ].offset ];


	int numEdges = header.lump[ BSP_EDGE_LUMP ].length / sizeof( BSPEdge );
	int numVertices = header.lump[ BSP_VERTEX_LUMP ].length / sizeof( Point3f );

	// contains indices into vertices
	vector< Index32 > triList;

	// contains a set of vertices for each BSPFace
	vector< BSPVertex > vertices;

	vector< Point3f > normalLines;

	for ( size_t i = 0; i < header.lump[ BSP_FACE_LUMP ].length / sizeof( BSPFace ); ++i )
	{
		vector< BSPEdge > polyEdges;
		BSPTexInfo texInfo = texInfoArray[ faceArray[ i ].texInfoIndex ];
		Surface s;
		s.tex.load( string( "mat/Q2/textures/" ).append( texInfo.texture_name ).append( ".wal" ) );

		// Set up the list of edges in order
		for ( size_t e = faceArray[ i ].firstEdgeIndex; e < faceArray[ i ].firstEdgeIndex + faceArray[ i ].num_edges; ++e )
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

		Point3f surfaceNormal;
		Point3f armA, armB;

		armA.x = vtxArray[ polyEdges[ 1 ].p1 ].y - vtxArray[ polyEdges[ 0 ].p1 ].y;
		armA.y = vtxArray[ polyEdges[ 1 ].p1 ].z - vtxArray[ polyEdges[ 0 ].p1 ].z;
		armA.z = vtxArray[ polyEdges[ 1 ].p1 ].x - vtxArray[ polyEdges[ 0 ].p1 ].x;

		armB.x = vtxArray[ polyEdges[ polyEdges.size() - 1 ].p1 ].y - vtxArray[ polyEdges[ 0 ].p1 ].y;
		armB.y = vtxArray[ polyEdges[ polyEdges.size() - 1 ].p1 ].z - vtxArray[ polyEdges[ 0 ].p1 ].z;
		armB.z = vtxArray[ polyEdges[ polyEdges.size() - 1 ].p1 ].x - vtxArray[ polyEdges[ 0 ].p1 ].x;

		surfaceNormal = armB.cross( armA );
		surfaceNormal.normalize();


		// Add the polygon's vertices
		for ( size_t d = 0; d < polyEdges.size(); ++d )
		{
			BSPVertex vtx;
			vtx.x = vtxArray[ polyEdges[ d ].p1 ].y;
			vtx.y = vtxArray[ polyEdges[ d ].p1 ].z;
			vtx.z = vtxArray[ polyEdges[ d ].p1 ].x;

			vtx.nx = surfaceNormal.x;
			vtx.ny = surfaceNormal.y;
			vtx.nz = surfaceNormal.z;

			//vtx.nx = 0.0;
			//vtx.ny = 1.0;
			//vtx.nz = 0.0;

			Point3f NLINEBASE;
			NLINEBASE.x = vtx.x;
			NLINEBASE.y = vtx.y;
			NLINEBASE.z = vtx.z;

			Point3f NLINEEND;
			NLINEEND.x = vtx.x + vtx.nx * 10.0;
			NLINEEND.y = vtx.y + vtx.ny * 10.0;
			NLINEEND.z = vtx.z + vtx.nz * 10.0;

			normalLines.push_back( NLINEBASE );
			normalLines.push_back( NLINEEND );


			// Calculate texture coordinates here
			vtx.u = ( vtx.z * texInfo.u_axis.x + vtx.x * texInfo.u_axis.y + vtx.y * texInfo.u_axis.z + texInfo.u_offset ) / s.tex.getWidth();
			vtx.v = ( vtx.z * texInfo.v_axis.x + vtx.x * texInfo.v_axis.y + vtx.y * texInfo.v_axis.z + texInfo.v_offset ) / s.tex.getHeight();

			// Add the vertex to the end of the vertex buffer
			vertices.push_back( vtx );
		}

		// Set up the indices for the triangles
		for ( size_t idx = vertices.size() - polyEdges.size() + 2; idx < vertices.size(); ++idx )
		{
			// fan the polygon from the first vertex
			triList.push_back( vertices.size() - polyEdges.size() );

			triList.push_back( idx - 1 );
			triList.push_back( idx );
		}

		s.polys.start = triList.size() - 3 * ( polyEdges.size() - 2 );
		s.polys.end = triList.size();

		surfaces.push_back( s );
	}

	//vBuffer.load( ( float * ) &fileData[ header.lump[ BSP_VERTEX_LUMP ].offset ], 
	//			  header.lump[ BSP_VERTEX_LUMP ].length / sizeof( Point3f ), sizeof( Point3f ) );

	normalLineBuffer.load( ( float * ) &normalLines[ 0 ], normalLines.size(), sizeof( Point3f ) );
	vBuffer.load( ( float * ) &vertices[ 0 ], vertices.size(), sizeof( BSPVertex ) );
	iBuffer.load( &triList[ 0 ], triList.size(), sizeof( Index32 ) );

	vBuffer.setFormat( BSP_VERTEX_FORMAT );
	normalLineBuffer.setFormat( GL_V3F );

	delete[] fileData;
};


void BSPMap::draw( Camera &camera )
{
	//normalLineBuffer.draw();
	vBuffer.bind();
	//iBuffer.draw();

	for ( size_t s = 0; s < surfaces.size(); ++s )
	{
		surfaces[ s ].tex.setCurrent();
		iBuffer.draw( surfaces[ s ].polys.start, surfaces[ s ].polys.end );
	}

};



