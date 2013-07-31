#include "Video.h"

Video::Video( Window &_window ) : window( _window ), currentCam( defaultCam )
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

};

Video::Video( Window &_window, Camera &cam ) : window( _window ), currentCam( cam )
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
};


Video::~Video( void )
{

};


void Video::init( void )
{
    // get pointers to GL functions, set some default OpenGL enables
	initGL();

	map.load( "mat/Q2/maps/fact3.bsp" );
	wglSwapIntervalEXT( 1 );

	light.setPosition( Point4f( 1.0, 1.0, 1.0, 0.0 ) );
	light.setDiffuseColour( Colour4f( 0.2, 0.2, 0.2, 1.0 ) );
	light.setSpecularColour( Colour4f( 0.0, 0.0, 0.0, 1.0 ) );

	material.setSpecularColour( Colour4f( 0.0, 0.0, 0.0, 1.0 ) );
	material.setShininess( 0.0 );
	
	glEnable( GL_LIGHT0 );

	vertexShader.create( GL_VERTEX_SHADER, "vertex_shader.glsl" );
	fragmentShader.create( GL_FRAGMENT_SHADER, "fragment_shader.glsl" );
	prog.create();
	prog.attach( vertexShader );
	prog.attach( fragmentShader );
	prog.link();
	prog.use();
	
	// This should probably be done automatically after use() is called on the program
	prog.detach( vertexShader );
	prog.detach( fragmentShader );

	prog.setUniform( "surfaceTexture", 0 );
	prog.setUniform( "lightmapTexture", 1 );
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

