#include "Video.h"

PFNGLGENBUFFERSPROC            pglGenBuffers = 0;             // VBO Name Generation Procedure
PFNGLBINDBUFFERPROC            pglBindBuffer = 0;             // VBO Bind Procedure
PFNGLBUFFERDATAPROC            pglBufferData = 0;             // VBO Data Loading Procedure
PFNGLBUFFERSUBDATAPROC         pglBufferSubData = 0;          // VBO Sub Data Loading Procedure
PFNGLDELETEBUFFERSPROC         pglDeleteBuffers = 0;          // VBO Deletion Procedure
PFNGLGETBUFFERPARAMETERIVPROC  pglGetBufferParameteriv = 0;   // return various parameters of VBO
PFNGLMAPBUFFERPROC             pglMapBuffer = 0;              // map VBO procedure
PFNGLUNMAPBUFFERPROC           pglUnmapBuffer = 0;            // unmap VBO procedure


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
    glGenBuffers = ( PFNGLGENBUFFERSPROC ) wglGetProcAddress( "glGenBuffers" );
    glBindBuffer = ( PFNGLBINDBUFFERPROC ) wglGetProcAddress( "glBindBuffer" );
    glBufferData = ( PFNGLBUFFERDATAPROC ) wglGetProcAddress( "glBufferData" );
    glBufferSubData = ( PFNGLBUFFERSUBDATAPROC ) wglGetProcAddress( "glBufferSubData" );
    glDeleteBuffers = ( PFNGLDELETEBUFFERSPROC ) wglGetProcAddress( "glDeleteBuffers" );
    glGetBufferParameteriv = ( PFNGLGETBUFFERPARAMETERIVPROC ) wglGetProcAddress( "glGetBufferParameteriv" );
    glMapBuffer = ( PFNGLMAPBUFFERPROC ) wglGetProcAddress( "glMapBuffer" );
    glUnmapBuffer = ( PFNGLUNMAPBUFFERPROC ) wglGetProcAddress( "glUnmapBuffer" );

	texture.load( "mat/error.bmp" );
	//texture.load( "mat/Q2/models/monsters/tank/skin.pcx" );
	map.load( "mat/Q2/maps/base1.bsp" );

	glColor4f( 1.0, 1.0, 1.0, 1.0 );
	//glEnable( GL_CULL_FACE );
	//glFrontFace( GL_CW );
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_DEPTH_TEST );

};

//#define STRESS_TEST
#define VBO_RENDER

void Video::render( void )
{
	glClear( GL_COLOR_BUFFER_BIT );
	glClear( GL_DEPTH_BUFFER_BIT );

	currentCam.transform();

	glDisable( GL_TEXTURE_2D );
	
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	glPushMatrix();
		glScalef( 0.01f, 0.01f, 0.01f );
		map.draw( currentCam );
	glPopMatrix();

	/**
	 * monkHiRes.raw has 3936 triangles
	 * stress tests involve 125 of these models (492000 triangles)
	 * SINGLE VBO		- ~1200 fps
	 * SINGLE NO BUFFER	- ~780 fps
	 * STRESS VBO		- ~420 fps
	 * STRESS NO BUFFER - ~15 fps
	 */
	glEnable( GL_TEXTURE_2D );
	texture.setCurrent();

	// Testing code:
#ifdef STRESS_TEST
	const int CUBE_SIDE = 5;
	for ( int x = 0; x < CUBE_SIDE; ++x )
	{
		for ( int y = 0; y < CUBE_SIDE; ++y )
		{
			for ( int z = 0; z < CUBE_SIDE; ++z )
			{
				glPushMatrix();
				glTranslatef( x*2, y*2, z*2 );
#endif
#ifndef VBO_RENDER
	glBegin( GL_TRIANGLES );
		for ( int i = 0; i < model->getVertices().size(); ++i )
		{
			Vertex v = model->getVertices()[ i ];
			glVertex3f( v.x, v.y, v.z );
		}
	glEnd();
#else
	model->getVBO().draw();
#endif	
#ifdef STRESS_TEST
				glPopMatrix();
			}
		}
	}
#endif
};