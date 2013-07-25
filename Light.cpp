#include "Light.h"


Light::Light( void )
{
	ambient.set( 0.0, 0.0, 0.0, 1.0 );
	diffuse.set( 1.0, 1.0, 1.0, 1.0 );
	specular.set( 1.0, 1.0, 1.0, 1.0 );

	position.set( 0.0, 0.0, 1.0, 0.0 );
	
	spotDirection.set( 0.0, 0.0, -1.0, 0.0 );
	spotExponent = 0.0;
	spotCutoff = 180.0;

	constantAttenuation = 1.0;
	linearAttenuation = 0.0;
	quadraticAttenuation = 0.0;
};


Light::~Light( void )
{

};


void Light::setPosition( Point4f pos )
{
	position = pos;
};

void Light::setColour( Colour4f ambient, Colour4f diffuse, Colour4f specular )
{
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
};

void Light::setAmbientColour( Colour4f col )
{
	ambient = col;
};

void Light::setDiffuseColour( Colour4f col )
{
	diffuse = col;
};

void Light::setSpecularColour( Colour4f col )
{
	specular = col;
};


void Light::setAttenuation( float constant, float linear, float quadratic )
{
	constantAttenuation = constant;
	linearAttenuation = constant;
	quadraticAttenuation = constant;
};

void Light::setConstantAttenuation( float att )
{
	constantAttenuation = att;
};

void Light::setLinearAttenuation( float att )
{
	linearAttenuation = att;
};

void Light::setQuadraticAttenuation( float att )
{
	quadraticAttenuation = att;
};


void Light::setSpot( float exponent, float cutoff, Point4f direction )
{
	spotExponent = exponent;
	spotCutoff = cutoff;
	spotDirection = direction;
};

void Light::setSpotExponent( float exp )
{
	spotExponent = exp;
};

void Light::setSpotCutoff( float cut )
{
	spotCutoff = cut;
};

void Light::setSpotDirection( Point4f dir )
{
	spotDirection = dir;
};


// Sets the specified opengl light's properties to this one's
// lightNum is an integer referring to the opengl light number (0 -> GL_LIGHT0, 1 -> GL_LIGHT1, etc.)
void Light::bind( int lightNum )
{
	if ( spotCutoff != 180.0f )
	{
		glLightf( GL_LIGHT0 + lightNum, GL_SPOT_EXPONENT, spotExponent );
		glLightf( GL_LIGHT0 + lightNum, GL_SPOT_CUTOFF, spotCutoff );
		
		glLightfv( GL_LIGHT0 + lightNum, GL_SPOT_DIRECTION, ( GLfloat * ) &spotDirection );
	}

	glLightf( GL_LIGHT0 + lightNum, GL_CONSTANT_ATTENUATION, constantAttenuation );
	glLightf( GL_LIGHT0 + lightNum, GL_LINEAR_ATTENUATION, linearAttenuation );
	glLightf( GL_LIGHT0 + lightNum, GL_QUADRATIC_ATTENUATION, quadraticAttenuation );

	glLightfv( GL_LIGHT0 + lightNum, GL_AMBIENT, ( GLfloat* ) &ambient );
	glLightfv( GL_LIGHT0 + lightNum, GL_DIFFUSE, ( GLfloat* ) &diffuse );
	glLightfv( GL_LIGHT0 + lightNum, GL_SPECULAR, ( GLfloat* ) &specular );

	glLightfv( GL_LIGHT0 + lightNum, GL_POSITION, ( GLfloat* ) &position );
};

