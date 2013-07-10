#pragma pack( push, 1 )
//#pragma pack( 1 )

typedef struct tagPCXHEADER
{
	unsigned char	manufacturer;		// fabriquant
	unsigned char	version;			// version
	unsigned char	encoding;			// encodage
	unsigned char	bitsPerPixel;		// nombre de bits par pixel

	unsigned short	x, y;
	unsigned short	width, height;		// dimensions
	unsigned short	horzRes, vertRes;

	unsigned char	palette[ 48 ];		// palette couleur
	unsigned char	reserved;			// reservé
	unsigned char	numColorPlanes;		// nombre de plans

	unsigned short	bytesPerScanLine;	// octets par ligne
	unsigned short	paletteType;
	unsigned short	horzSize, vertSize;

	unsigned char	padding[ 54 ];

} PCXHEADER, *PPCXHEADER;

//#pragma pack( 4 )



//#ifdef WIN32
//#include	<windows.h>
//#else

// --------------------------------------------
// RGBTRIPLE - pixel 24 bits.
// --------------------------------------------

typedef struct			// rgbt
{
	unsigned char	rgbRed;			// rouge
	unsigned char	rgbGreen;		// vert
	unsigned char	rgbBlue;		// bleu

} RGBTriple, *PRGBTriple;

#pragma pack( pop )
