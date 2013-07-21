#ifndef TextureH
#define TextureH

#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "glext.h"
#include <iostream>

#include "Picture.h"

using namespace std;

/**
 * 
 * 
 */
class Texture
{
public:
	/**
	 * Initializes the Texture object with an invalid OpenGL texture
	 * ID.
	 */
	Texture( void );

	/**
	 * Loads the Texture with the specified image file
	 *
	 * @param fileName the file path of the image
	 */
	Texture( string fileName );

	/**
	 * Deletes the OpenGL texture object if it exists
	 */
	~Texture( void );

	/**
	 * Loads the Texture with the specified image file
	 *
	 * @param fileName the file path of the image
	 */
	void load( string fileName );

	void loadLightmap( int width, int height, char *lightmap )
	{
		glGenTextures( 1, &texId );
		glBindTexture( GL_TEXTURE_2D, texId );

		// select modulate to mix texture with color for shading
		glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

		// when texture area is small, bilinear filter the closest mipmap
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );

		// when texture area is large, bilinear filter the original
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		// the texture wraps over at the edges (repeat)
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

		//GLfloat largest_supported_anisotropy;
		//glGetFloatv( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest_supported_anisotropy );
		//glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest_supported_anisotropy );

		vector< unsigned char > bitmap( width * height * 4 );
		for ( int p = 0; p < width * height; ++p )
		{
			bitmap[ p * 4 + 0 ] = lightmap[ p * 3 + 0 ];
			bitmap[ p * 4 + 1 ] = lightmap[ p * 3 + 1 ];
			bitmap[ p * 4 + 2 ] = lightmap[ p * 3 + 2 ];
			bitmap[ p * 4 + 3 ] = 255;
		}

		gluBuild2DMipmaps( GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, &bitmap[ 0 ] );
		glBindTexture( GL_TEXTURE_2D, 0 );

		this->width = width;
		this->height = height;
	};

	/**
	 * Deletes the OpenGL texture object if it exists
	 */
	void unload( void );

	/**
	 * Binds this texture as the one currently in use by OpenGL
	 */
	void setCurrent( void );

	int getWidth( void ) { return width; };
	int getHeight( void ) { return height; };

private:
	/**
	 * The texture's ID, as assigned to it by OpenGL during loading.
	 */
	GLuint texId;
	int width, height;
};


/**
 * A reference to the Texture object. Exists for the purpose of 
 * memory management, so that the same Texture objects (which may
 * consume valuable system resources) only need to be loaded once
 * in order to be used from any place.
 *
 *
 */
class TextureHandle
{
public:
	/**
	 * Loads a default texture (gray)
	 */
	TextureHandle( void );

	/**
	 * Sets this TextureHandle to refer to the specified texture
	 * 
	 * @param  fileName the path of the texture to be loaded
	 */
	TextureHandle( string fileName );

	/**
	 * Copies a TextureHandle and increments the reference counter.
	 * 
	 * @return reference to object left of '='
	 */
	//TextureHandle &operator = ( TextureHandle rhs );

	/**
	 * Sets up this TextureHandle to refer to a texture that is
	 * the same as an image file.
	 *
	 * If the image has already been loaded (by another 
	 * TextureHandle->load(fileName) with the same fileName),
	 * then the TextureHandle is simply duplicated, so the texture
	 * isn't loaded twice, but is referred to twice.
	 *
	 * @param  fileName The path of the texture to be loaded
	 */
	void load( string fileName );

	void loadLightmap( int width, int height, char* lightmap )
	{
		TextureReference tr;
		tr.fileName = "LIGHTMAP";
		tr.refCount = 1;
		tr.texture = new Texture();
		tr.texture->loadLightmap( width, height, lightmap );

		loadedTextures.push_back( tr );
		texRefIndex = loadedTextures.size() - 1;
	};

	/**
	 * Deletes the Texture pointed to by this TextureHandle,
	 * invalidating all other TextureHandles that refer to the
	 * same Texture.
	 */
	void unload( void );

	/**
	 * Binds the current OpenGL texture to the one pointed to by
	 * this handle.
	 */
	void setCurrent( void );

	int getWidth( void ) { return loadedTextures[ texRefIndex ].texture->getWidth(); };
	int getHeight( void ) { return loadedTextures[ texRefIndex ].texture->getHeight(); };

	bool operator == ( TextureHandle& rhs ) { return texRefIndex == rhs.texRefIndex; };

	/**
	 * Deletes all Textures that currently have 0 TextureHandles
	 * pointing to them.
	 */
	static void deleteUnused( void );

	/**
	 * Deletes all textures, invalidating all TextureHandles.
	 */
	static void deleteAll( void );

private:
	/**
	 * An intermediate object that holds the information about a 
	 * single texture so that it can be loaded once and referred to 
	 * many times, then deleted when it isn't needed any more.
	 */
	typedef struct TextureReference
	{
		/**
		 * Creates an empty reference (refCount = 0, fileName = "",
		 * texture = nullptr)
		 */
		TextureReference( void );

		/**
		 * The OpenGL texture object that is being referred to
		 */
		Texture *texture;

		/**
		 * The number of TextureHandles referring to this texture
		 */
		int refCount;

		/**
		 * The path of the image that was loaded into the texture
		 */
		string fileName;
	} TextureReference;

	/**
	 * A list of all of the Textures that have been loaded so that
	 * they aren't loaded twice; also allows for garbage collection.
	 */
	static vector< TextureReference > loadedTextures;

	/**
	 * Error texture for when texture loading fails (not yet 
	 * implemented)
	 */
	static Texture *NONE;

	/**
	 * Default gray texture for when no texture has been loaded (not
	 * yet implemented)
	 */
	static Texture *DEFAULT;

	/**
	 * The Texture reference 
	 */
	int texRefIndex;
};


#endif /* TextureH */