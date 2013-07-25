#include "Material.h"


Material::Material( void )
{
	ambient.set( 0.2, 0.2, 0.2, 1.0 );
	diffuse.set( 0.8, 0.8, 0.8, 1.0 );
	specular.set( 0.0, 0.0, 0.0, 1.0 );
	emissive.set( 0.0, 0.0, 0.0, 1.0 );
	shininess = 0.0;
};


Material::~Material( void )
{

};


void Material::setShininess( float shine )
{
	this->shininess = shine;
};

void Material::setColour( Colour4f ambient, Colour4f diffuse, Colour4f specular )
{
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
};

void Material::setColour( Colour4f ambient, Colour4f diffuse, Colour4f specular, Colour4f emissive )
{
	setColour( ambient, diffuse, specular );
	this->emissive = emissive;
};


void Material::setAmbientColour( Colour4f col )
{
	ambient = col;
};

void Material::setDiffuseColour( Colour4f col )
{
	diffuse = col;
};

void Material::setSpecularColour( Colour4f col )
{
	specular = col;
};

void Material::setEmissiveColour( Colour4f col )
{
	emissive = col;
};



// Sets the OpenGL material properties to the ones in this class
void Material::bind( void )
{
	glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, shininess );

	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, ( GLfloat * ) &ambient );
	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, ( GLfloat * ) &diffuse );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, ( GLfloat * ) &specular );
	glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, ( GLfloat * ) &emissive );
};
