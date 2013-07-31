#ifndef BSPMapH
#define BSPMapH

/**
 * BSP structure and loading information for the BSP maps used by
 * quake 2.
 */

#include "Map.h"
#include "Camera.h"
#include "IndexBuffer.h"
#include "Texture.h"

namespace Q2
{

	typedef enum BSP_LUMP
	{
		ENTITY_LUMP	     =  0,  // MAP entity text buffer
		PLANE_LUMP       =  1,  // Plane array
		VERTEX_LUMP      =  2,  // Vertex array
		VISIBILITY_LUMP  =  3,  // Compressed PVS data and directory for all clusters
		NODE_LUMP        =  4,  // Internal node array for the BSP tree
		TEX_INFO_LUMP    =  5,  // Face texture application array
		FACE_LUMP        =  6,  // Face array
		LIGHTMAP_LUMP    =  7,  // Lightmaps
		LEAF_LUMP        =  8,  // Internal leaf array of the BSP tree
		LEAF_FACE_LUMP   =  9,  // Index lookup table for referencing the face array from a leaf
		LEAF_BRUSH_LUMP  = 10, // ?
		EDGE_LUMP        = 11, // Edge array
		FACE_EDGE_LUMP   = 12, // Index lookup table for referencing the edge array from a face
		MODEL_LUMP       = 13, // ?
		BRUSH_LUMP       = 14, // ?
		BRUSH_SIDE_LUMP  = 15, // ?
		POP_LUMP         = 16, // ?
		AREA_LUMP        = 17, // ?
		AREA_PORTAL_LUMP = 18  // ?
	};
	//#pragma pack ( push, 1 )

	typedef unsigned __int16 Index16;
	typedef unsigned __int32 Index32;


	typedef struct
	{
		short x, y, z;
	} Point3s;

	typedef struct
	{
		float u, v;
		float lmu, lmv;
		float nx, ny, nz;
		float x, y, z;
	} BSPVertex;

	typedef struct
	{
		unsigned __int32 offset;
		unsigned __int32 length;
	} BSPLump;

	typedef struct
	{
		int magic;
		int version;
		BSPLump lump[ 19 ];
	} BSPHeader;

	typedef struct
	{
		Index16 p1, p2;
	} BSPEdge;

	/**
	 * Face structure:
	 *     plane: index of the bsp_plane the face is parallel to
	 *     plane_side: set if the normal is parallel to the plane normal
	 *     first_edge: index of the first edge in the face edge array
	 *     num_edges: number of edges in the face
	 *     texture_info: index of the texture info struct
	 *     lightmap_styles: styles (bit flags) for the lightmaps
	 *     lightmap_offset: offset of the lightmap (in bytes) in the lightmap lump
	 */
	typedef struct
	{
		Index16 planeIndex;
		unsigned __int16 planeSide;
		Index32 firstEdgeIndex;
		unsigned __int16 num_edges;
		Index16 texInfoIndex;
		unsigned char lightmapStyles[ 4 ];
		int lightmapOffset;
	} BSPFace;

	typedef struct
	{
		Point3f  u_axis;
		float    u_offset;
   
		Point3f  v_axis;
		float    v_offset;

		unsigned __int32 flags;
		unsigned __int32 value;

		char     texture_name[32];
		Index32  next_texinfo;
	} BSPTexInfo;

	class BSPMap : public Map
	{
	public:
		BSPMap( void );
		//BSPMap( string fileName );
		~BSPMap( void );

		void load( string fileName );

		void draw( Camera &camera );

	private:
		typedef struct
		{
			Index32 start, end;
		} IndexRange;

		typedef struct
		{
			IndexRange polys;
			TextureHandle tex;
			TextureHandle lightmap;

			// These are for software backface culling (temporary)
			Point3f normal;
			Point3f firstVertex;
		} Surface;

		BSPHeader header;

		VertexBuffer vBuffer;
		//VertexBuffer normalLineBuffer;
		IndexBuffer iBuffer;

		vector< Surface > surfaces;

	};

};

#endif /* BSPMapH */