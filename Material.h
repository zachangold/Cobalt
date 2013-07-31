#ifndef MaterialH
#define MaterialH

#include "Math.h"
#include "GLFunctions.h"

/**
 * Stores the properties of an openGL material for use when rendering
 * and changes the pertinent openGL values when needed.
 */

class Material
{
public:
	/**
	 * Sets the properties of the material to the openGL defaults:
	 *     ambient = ( 0.2, 0.2, 0.2, 1.0 )
	 *     diffuse = ( 0.8, 0.8, 0.8, 1.0 )
	 *     specular = ( 0.0, 0.0, 0.0, 1.0 )
	 *     emissive = ( 0.0, 0.0, 0.0, 1.0 )
	 *     shininess = 0.0
	 */
	Material( void );

	/**
	 * Does nothing (should this disable the material in openGL?)
	 */
	~Material( void );

	/**
	 * Sets the specular exponent of the material, in the range from
	 * 0 to 128, inclusive
	 */
	void setShininess( float shine );

	/**
	 * Sets the colours of the material simultaneously
	 */
	void setColour( Colour4f ambient, Colour4f diffuse, Colour4f specular );
	void setColour( Colour4f ambient, Colour4f diffuse, Colour4f specular, Colour4f emissive );

	/**
	 * Set the ambient, diffuse, specular, or emissive colour of the
	 * material
	 */
	void setAmbientColour( Colour4f col );
	void setDiffuseColour( Colour4f col );
	void setSpecularColour( Colour4f col );
	void setEmissiveColour( Colour4f col );

	/**
	 * Sets the OpenGL material properties to the ones in this class
	 */
	void bind( void );

private:
	// reflective/light properties of the material
	Colour4f ambient;
	Colour4f diffuse;
	Colour4f specular;
	Colour4f emissive;

	// Specular exponent in [0, 128]
	float shininess;
};


#endif /* MaterialH */