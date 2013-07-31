#include "Material.h"


/**
 * Sets the properties of the material to the openGL defaults
 */
Material::Material( void )
{
	ambient.set( 0.2, 0.2, 0.2, 1.0 );
	diffuse.set( 0.8, 0.8, 0.8, 1.0 );
	specular.set( 0.0, 0.0, 0.0, 1.0 );
	emissive.set( 0.0, 0.0, 0.0, 1.0 );
	shininess = 0.0;
};


/**
 * Does nothing (should this disable the material in openGL?)
 */
Material::~Material( void )
{

};


/**
 * Sets the specular exponent of the material, in the range from
 * 0 to 128, inclusive
 */
void Material::setShininess( float shine )
{
	shininess = shine;
};

/**
 * Sets the ambient, diffuse, and specular colours of the material 
 * simultaneously.
 */
void Material::setColour( Colour4f ambient, Colour4f diffuse, Colour4f specular )
{
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
};

/**
 * Sets the ambient, diffuse, specular, and emissive colours of the 
 * material simultaneously.
 */
void Material::setColour( Colour4f ambient, Colour4f diffuse, Colour4f specular, Colour4f emissive )
{
	setColour( ambient, diffuse, specular );
	this->emissive = emissive;
};

/**
 * Sets the ambient colour of the material
 */
void Material::setAmbientColour( Colour4f col )
{
	ambient = col;
};

/**
 * Sets the diffuse colour of the material
 */
void Material::setDiffuseColour( Colour4f col )
{
	diffuse = col;
};

/**
 * Sets the specular colour of the material
 */
void Material::setSpecularColour( Colour4f col )
{
	specular = col;
};

/**
 * Sets the emissive colour of the material
 */
void Material::setEmissiveColour( Colour4f col )
{
	emissive = col;
};


/**
 * Sets up the Material's properties with OpenGL, putting this 
 * material into use for rendering.
 */
void Material::bind( void )
{
	glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, shininess );

	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, ( GLfloat * ) &ambient );
	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, ( GLfloat * ) &diffuse );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, ( GLfloat * ) &specular );
	glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, ( GLfloat * ) &emissive );
};
