#include "Video.h"

Video::Video( Window &_window ) : window( _window ), currentCam( defaultCam )
{
	model = NULL;
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

};

Video::Video( Window &_window, Camera &cam ) : window( _window ), currentCam( cam )
{
	model = NULL;
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
};


Video::~Video( void )
{

};


void Video::init( void )
{
    // get pointers to GL functions
	initGLFunctions();

	texture.load( "mat/error.bmp" );
	map.load( "mat/Q2/maps/space.bsp" );

	glColor4f( 1.0, 1.0, 1.0, 1.0 );
	glEnable( GL_CULL_FACE );
	glFrontFace( GL_CW );
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_DEPTH_TEST );

	light.setPosition( Point4f( 1.0, 1.0, 1.0, 0.0 ) );
	light.setDiffuseColour( Colour4f( 0.2, 0.2, 0.2, 1.0 ) );
	light.setSpecularColour( Colour4f( 0.0, 0.0, 0.0, 1.0 ) );

	material.setSpecularColour( Colour4f( 0.0, 0.0, 0.0, 1.0 ) );
	material.setShininess( 0.0 );

	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );

	vertexShader.create( GL_VERTEX_SHADER, "vertex_shader.glsl" );
	fragmentShader.create( GL_FRAGMENT_SHADER, "fragment_shader.glsl" );
	prog.create();
	prog.attachShader( vertexShader );
	prog.attachShader( fragmentShader );
	prog.link();
	prog.use();
	prog.detachShader( vertexShader );
	prog.detachShader( fragmentShader );

	int loc = glGetUniformLocation( prog.getHandle(), "surfaceTexture" );
	glUniform1i( loc, 0 );

	loc = glGetUniformLocation( prog.getHandle(), "lightmapTexture" );
	glUniform1i( loc, 1 );
};


void Video::render( void )
{
	glClear( GL_COLOR_BUFFER_BIT );
	glClear( GL_DEPTH_BUFFER_BIT );

	light.setPosition( currentCam.getPosition() );
	light.bind( 0 );
	material.bind();
	currentCam.transform();

	glPushMatrix();
		glScalef( 0.01f, 0.01f, 0.01f );
		map.draw( currentCam );
	glPopMatrix();
};

