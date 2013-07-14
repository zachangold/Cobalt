#include "Texture.h"

vector< TextureHandle::TextureReference > TextureHandle::loadedTextures;

Texture::Texture( void )
{
	texId = 0xFFFFFFFF;
};

Texture::~Texture( void )
{
	unload();
};

void Texture::load( string fileName )
{
	glGenTextures( 1, &texId );
	glBindTexture( GL_TEXTURE_2D, texId );

	// select modulate to mix texture with color for shading
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

	// when texture area is small, bilinear filter the closest mipmap
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
					 GL_LINEAR_MIPMAP_NEAREST );

	// when texture area is large, bilinear filter the original
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	// the texture wraps over at the edges (repeat)
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

	GLfloat largest_supported_anisotropy;
	glGetFloatv( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest_supported_anisotropy );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest_supported_anisotropy );

	Picture pic( fileName );
	gluBuild2DMipmaps( GL_TEXTURE_2D, 4, pic.getWidth(), pic.getHeight(), GL_RGBA, GL_UNSIGNED_BYTE, pic.getBitmap() );
};

void Texture::unload( void )
{
	if ( texId != 0xFFFFFFFF )
	{
		glDeleteTextures( 1, &texId );
		texId = 0xFFFFFFFF;
	}
};

void Texture::setCurrent( void )
{
	glBindTexture( GL_TEXTURE_2D, texId );
};

void TextureHandle::deleteAll( void )
{
	for ( int i = 0; i < loadedTextures.size(); ++i )
	{
		loadedTextures[ i ].refCount = 0;
		loadedTextures[ i ].fileName = "";

		if ( loadedTextures[ i ].texture != nullptr )
		{
			delete loadedTextures[ i ].texture;
			loadedTextures[ i ].texture = nullptr;
		}
	}

	loadedTextures.resize( 0 );
};


TextureHandle::TextureReference::TextureReference( void )
{
	refCount = 0;
	texture = nullptr;
	fileName = "";
};