#ifndef LightH
#define LightH

#include "Math.h"
#include "GLFunctions.h"

class Light
{
public:
	Light( void );
	~Light( void );

	void setPosition( Point4f pos );

	void setColour( Colour4f ambient, Colour4f diffuse, Colour4f specular );
	void setAmbientColour( Colour4f col );
	void setDiffuseColour( Colour4f col );
	void setSpecularColour( Colour4f col );

	void setAttenuation( float constant, float linear, float quadratic );
	void setConstantAttenuation( float att );
	void setLinearAttenuation( float att );
	void setQuadraticAttenuation( float att );

	void setSpot( float exponent, float cutoff, Point4f direction );
	void setSpotExponent( float exp );
	void setSpotCutoff( float cut );
	void setSpotDirection( Point4f dir );

	// Sets the specified opengl light's properties to this one's
	// lightNum is an integer referring to the opengl light number (0 -> GL_LIGHT0, 1 -> GL_LIGHT1, etc.)
	void bind( int lightNum );

private:
	Point4f position;
	Point4f spotDirection;

	Colour4f ambient;
	Colour4f diffuse;
	Colour4f specular;

	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;

	float spotExponent;
	float spotCutoff;
};

#endif /* LightH*/