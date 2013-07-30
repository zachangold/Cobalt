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

		s.normal = surfaceNormal;

		float minu = +10000.0, minv = +10000.0;
		float maxu = -10000.0, maxv = -10000.0;

		s.firstVertex.x = vtxArray[ polyEdges[ 0 ].p1 ].y;
		s.firstVertex.y = vtxArray[ polyEdges[ 0 ].p1 ].z;
		s.firstVertex.z = vtxArray[ polyEdges[ 0 ].p1 ].x;

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

			// Calculate texture coordinates here
			vtx.u = ( vtx.z * texInfo.u_axis.x + vtx.x * texInfo.u_axis.y + vtx.y * texInfo.u_axis.z + texInfo.u_offset ) / (float) s.tex.getWidth();
			vtx.v = ( vtx.z * texInfo.v_axis.x + vtx.x * texInfo.v_axis.y + vtx.y * texInfo.v_axis.z + texInfo.v_offset ) / (float) s.tex.getHeight();

			if ( vtx.z * texInfo.u_axis.x + vtx.x * texInfo.u_axis.y + vtx.y * texInfo.u_axis.z + texInfo.u_offset > maxu )
			{
				maxu = vtx.z * texInfo.u_axis.x + vtx.x * texInfo.u_axis.y + vtx.y * texInfo.u_axis.z + texInfo.u_offset;
			}
			if ( vtx.z * texInfo.v_axis.x + vtx.x * texInfo.v_axis.y + vtx.y * texInfo.v_axis.z + texInfo.v_offset > maxv )
			{
				maxv = vtx.z * texInfo.v_axis.x + vtx.x * texInfo.v_axis.y + vtx.y * texInfo.v_axis.z + texInfo.v_offset;
			}

			if ( vtx.z * texInfo.u_axis.x + vtx.x * texInfo.u_axis.y + vtx.y * texInfo.u_axis.z + texInfo.u_offset < minu )
			{
				minu = vtx.z * texInfo.u_axis.x + vtx.x * texInfo.u_axis.y + vtx.y * texInfo.u_axis.z + texInfo.u_offset;
			}
			if ( vtx.z * texInfo.v_axis.x + vtx.x * texInfo.v_axis.y + vtx.y * texInfo.v_axis.z + texInfo.v_offset < minv )
			{
				minv = vtx.z * texInfo.v_axis.x + vtx.x * texInfo.v_axis.y + vtx.y * texInfo.v_axis.z + texInfo.v_offset;
			}

			// Add the vertex to the end of the vertex buffer
			vertices.push_back( vtx );
		}

		int lmw = ceil( maxu / 16 ) - floor( minu / 16 ) + 1;
		int lmh = ceil( maxv / 16 ) - floor( minv / 16 ) + 1;
		s.lightmap.loadLightmap( lmw, lmh, &fileData[ header.lump[ BSP_LIGHTMAP_LUMP ].offset + faceArray[ i ].lightmapOffset ] );

		// generate the texture coordinates for the lightmaps
		for ( int v = vertices.size() - polyEdges.size(); v < vertices.size(); ++v )
		{
			vertices[ v ].lmu = ( vertices[ v ].u * ( ( float ) s.tex.getWidth() ) - minu ) / ( maxu - minu );
			vertices[ v ].lmv = ( vertices[ v ].v * ( ( float ) s.tex.getHeight() ) - minv ) / ( maxv - minv );
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

	//normalLineBuffer.load( ( float * ) &normalLines[ 0 ], normalLines.size(), sizeof( Point3f ) );
	vBuffer.load( ( float * ) &vertices[ 0 ], vertices.size(), sizeof( BSPVertex ) );
	iBuffer.load( &triList[ 0 ], triList.size(), sizeof( Index32 ) );

	//normalLineBuffer.setFormat( GL_V3F );

	delete[] fileData;
};


void BSPMap::draw( Camera &camera )
{
	//normalLineBuffer.draw();
	vBuffer.bind();
	//iBuffer.draw();

	for ( size_t s = 0; s < surfaces.size(); ++s )
	{
		if ( ( camera.getPosition() - surfaces[ s ].firstVertex * 0.01f ).dot( surfaces[ s ].normal ) < 0 ) continue;

		glActiveTexture( GL_TEXTURE0 );
		surfaces[ s ].tex.setCurrent();
		glActiveTexture( GL_TEXTURE1 );
		surfaces[ s ].lightmap.setCurrent();
		iBuffer.draw( surfaces[ s ].polys.start, surfaces[ s ].polys.end );
	}

};



