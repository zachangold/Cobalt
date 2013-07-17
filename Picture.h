#ifndef PictureH
#define PictureH

#include <iostream>
#include <vector>
using namespace std;

class Picture
{
public:
	Picture( void );
	Picture( string fileName );
	~Picture( void );

	// load( fileName ) opens the file and processes it into an RGBA bitmap
	void load( string fileName );
	void unload( void );

	char *getBitmap( void );
	int getWidth( void );
	int getHeight( void );

private:
	void loadBMP( string fileName );
	void loadPCX( string fileName );
	void loadWAL( string fileName );
	// Other file formats go here

	vector< char > bitmap;
	int width;
	int height;

};

#endif /* PictureH */