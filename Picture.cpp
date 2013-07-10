#include "Picture.h"

#include <fstream>

#include "BMP.h"
#include "PCX.h"

Picture::Picture( void )
{
	width = 0;
	height = 0;
};


Picture::Picture( string fileName )
{
	load( fileName );
};

Picture::~Picture( void )
{
	unload();
};


// load( fileName ) opens the file and processes it into an RGBA bitmap
void Picture::load( string fileName )
{
	unload();

	string ext = fileName.substr( fileName.find_last_of( '.' ), fileName.size() );
	if ( ext.compare( ".bmp" ) == 0 )
	{
		loadBMP( fileName );
	}
	else if ( ext.compare( ".pcx" ) == 0 )
	{
		loadPCX( fileName );
	}
};

void Picture::unload( void )
{
	bitmap.resize( 0 );
	width = 0;
	height = 0;
};


char *Picture::getBitmap( void )
{
	return &bitmap[ 0 ];
};

int Picture::getWidth( void )
{
	return width;
};

int Picture::getHeight( void )
{
	return height;
};


void Picture::loadBMP( string fileName )
{
	vector< char > fileData;

	ifstream file( fileName, ios::in | ios::binary | ios::ate );
	fileData.resize( file.tellg() );
	file.seekg( 0 );
	file.read( &fileData[ 0 ], fileData.size() );
	file.close();

	BMPHeader *bmpH = ( BMPHeader * ) &fileData[ 0 ];
	DIBHeader *dibH = ( DIBHeader * ) &fileData[ 0xE ];

	width = dibH->width;
	height = dibH->height;

	// too lazy to implement decompressors
	if ( dibH->comprMethod != BI_RGB ) return;

	bitmap.resize( width * height * 4 );
	//memcpy( &bitmap[ 0 ], &fileData[ bmpH->dataOffset ], dibH->imgSize );

	for ( int i = 0; i < width * height; ++i )
	{
		bitmap[ i * 4 + 0 ] = fileData[ bmpH->dataOffset + i * 3 + 2 ]; // r
		bitmap[ i * 4 + 1 ] = fileData[ bmpH->dataOffset + i * 3 + 1 ]; // g
		bitmap[ i * 4 + 2 ] = fileData[ bmpH->dataOffset + i * 3 + 0 ]; // b
		bitmap[ i * 4 + 3 ] = 255; // a
	}

};

void Picture::loadPCX( string fileName )
{
	std::ifstream		file;			// fichier
	PCXHEADER			*header;		// header PCX
	RGBTriple			*palette;		// palette
	unsigned char		*data;			// données images RLE
	unsigned char		*ptr;			// pointeur données pixels
	unsigned char		c;				// variable temporaire
	char				*buffer;		// buffer stockant l'intégralité du fichier
	int					idx = 0;		// variable temporaire
	int					numRepeat;		// variable temporaire
	int					i, j;			// variable temporaire



	/////////////////////////////////////////////////////
	// lit l'intégralité du fichier dans le buffer

	file.open( fileName, std::ios::in | std::ios::binary );

	if ( file.fail() ) return;

	file.seekg( 0, std::ios::end );
	long flen = file.tellg();
	file.seekg( 0, std::ios::beg );

	buffer = new char[ flen + 1 ];
	file.read( buffer, flen );
	char *pBuff = buffer;

	file.close();

	/////////////////////////////////////////////////////

	// on lit le header
	header = (PCXHEADER *)pBuff;

	// vérification de l'authenticité du PCX
	if( (header->manufacturer	!= 10)	||
		(header->version		!= 5)	||
		(header->encoding		!= 1)	||
		(header->bitsPerPixel	!= 8) )
	{
		delete [] buffer;
		return;
	}


	header->width	= header->width	 - header->x + 1;
	header->height	= header->height - header->y + 1;

	width = header->width;
	height = header->height;


	// allocatation mémoire pour les données image
	data = new unsigned char[ header->width * header->height * 3 ];
	pBuff = (char *)&buffer[ 128 ];

	// décode l'image compressée (RLE)
	while( idx < (header->width * header->height) )
	{
		if( (c = *(pBuff++)) > 0xbf )
		{
			numRepeat = 0x3f & c;
			c = *(pBuff++);

			for( i = 0; i < numRepeat; i++ )
				data[ idx++ ] = c;
		}
		else
			data[ idx++ ] = c;
	}

	// la palette se trouve au 769 dernier octet du fichier
	pBuff = &buffer[ flen - 769 ];

	// on vérifie la palette ; le premier char doit être égal à 12
	if( *(pBuff++) != 12 )
	{
		delete [] buffer;
		delete [] data;
		return;
	}

	// on lit la palette
	palette = (RGBTriple *)pBuff;

	// allocatation mémoire pour les données pixels 32 bits
	//*pixels = new unsigned char[ header->width * header->height * 4 ];
	bitmap.resize( width * height * 4 );
	ptr = ( unsigned char * ) &bitmap[ 0 ];

	// conversion pixel index couleur bgr en pixel rgba 32 bits
	for ( j = header->height - 1; j >= 0; j-- )
	{
		//if( flipvert )
		//	ptr = &(*pixels)[ j * header->width * 4 ];

		for( i = 0; i < header->width; i++, ptr += 4 )
		{
			int color = data[ j * header->width + i ];

			ptr[ 0 ] = ( unsigned char ) palette[ color ].rgbRed;	// b->r
			ptr[ 1 ] = ( unsigned char ) palette[ color ].rgbGreen;	// g->g
			ptr[ 2 ] = ( unsigned char ) palette[ color ].rgbBlue; 	// r->b
			ptr[ 3 ] = ( unsigned char ) 255;					    // alpha
		}
	}


	// désallocation mémoire tampon
	delete [] data;
	delete [] buffer;
};