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

 #define BSP_ENTITY_LUMP         0  // MAP entity text buffer
 #define BSP_PLANE_LUMP          1  // Plane array
  #define BSP_VERTEX_LUMP         2  // Vertex array
 #define BSP_VISIBILITY_LUMP     3  // Compressed PVS data and directory for all clusters
 #define BSP_NODE_LUMP           4  // Internal node array for the BSP tree
 #define BSP_TEX_INFO_LUMP       5  // Face texture application array
 #define BSP_FACE_LUMP           6  // Face array
 #define BSP_LIGHTMAP_LUMP       7  // Lightmaps
 #define BSP_LEAF_LUMP           8  // Internal leaf array of the BSP tree
 #define BSP_LEAF_FACE_LUMP      9  // Index lookup table for referencing the face array from a leaf
#define BSP_LEAF_BRUSH_LUMP    10 // ?
  #define BSP_EDGE_LUMP          11 // Edge array
  #define BSP_FACE_EDGE_LUMP     12 // Index lookup table for referencing the edge array from a face
#define BSP_MODEL_LUMP         13 // ?
#define BSP_BRUSH_LUMP         14 // ?
#define BSP_BRUSH_SIDE_LUMP    15 // ?
#define BSP_POP_LUMP           16 // ?
#define BSP_AREA_LUMP          17 // ?
#define BSP_AREA_PORTAL_LUMP   18 // ?

#define BSP_VERTEX_FORMAT GL_T2F_N3F_V3F

//#pragma pack ( push, 1 )

typedef unsigned __int16 Index16;
typedef unsigned __int32 Index32;

typedef struct Point3f
{
    float x, y, z;

	Point3f cross( Point3f rhs )
	{
		Point3f rtn;
		rtn.x = y * rhs.z - z * rhs.y;
		rtn.y = z * rhs.x - x * rhs.z;
		rtn.z = x * rhs.y - y * rhs.x;
		return rtn;
	};

	void normalize( void )
	{
		int mag = sqrt( x * x + y * y + z * z );
		x /= mag;
		y /= mag;
		z /= mag;
	};
} Point3f;

typedef struct
{
    short x, y, z;
} Point3s;

typedef struct
{
	float u, v;
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

//#pragma pack( pop )

class BSPMap : public Map
{
public:
	BSPMap( void );
	//BSPMap( string fileName );
	~BSPMap( void );

	void load( string fileName );

	void draw( Camera &camera );

private:
	BSPHeader header;

	VertexBuffer vBuffer;
	VertexBuffer normalLineBuffer;
	IndexBuffer iBuffer;

	typedef struct
	{
		Index32 start, end;
	} IndexRange;

	typedef struct
	{
		IndexRange polys;
		TextureHandle tex;
	} Surface;

	vector< Surface > surfaces;
};

#endif /* BSPMapH */