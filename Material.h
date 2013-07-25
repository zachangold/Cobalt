#ifndef MaterialH
#define MaterialH

#include "Math.h"
#include "GLFunctions.h"

class Material
{
public:
	Material( void );
	~Material( void );

	void setShininess( float shine );

	void setColour( Colour4f ambient, Colour4f diffuse, Colour4f specular );
	void setColour( Colour4f ambient, Colour4f diffuse, Colour4f specular, Colour4f emissive );

	void setAmbientColour( Colour4f col );
	void setDiffuseColour( Colour4f col );
	void setSpecularColour( Colour4f col );
	void setEmissiveColour( Colour4f col );

	// Sets the OpenGL material properties to the ones in this class
	void bind( void );

private:
	Colour4f ambient;
	Colour4f diffuse;
	Colour4f specular;
	Colour4f emissive;

	float shininess;
};


#endif /* MaterialH */