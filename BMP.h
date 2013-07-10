#define BI_RGB 0

#pragma pack( push, 1 )
typedef struct
{
	unsigned __int16 magic;
	__int32 fileSize;
	__int16 res1, res2;
	__int32 dataOffset;
} BMPHeader;

typedef struct
{
	__int32 headerSize;
	__int32 width;
	__int32 height;
	__int16 nColorPlanes;
	__int16 bpp;
	__int32 comprMethod;
	__int32 imgSize;
	__int32 hRes;
	__int32 vres;
	__int32 nColors;
	__int32 nImportantColors;
} DIBHeader;
#pragma pack( pop )