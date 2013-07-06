#include "Video.h"

PFNGLGENBUFFERSARBPROC            pglGenBuffersARB = 0;             // VBO Name Generation Procedure
PFNGLBINDBUFFERARBPROC            pglBindBufferARB = 0;             // VBO Bind Procedure
PFNGLBUFFERDATAARBPROC            pglBufferDataARB = 0;             // VBO Data Loading Procedure
PFNGLBUFFERSUBDATAARBPROC         pglBufferSubDataARB = 0;          // VBO Sub Data Loading Procedure
PFNGLDELETEBUFFERSARBPROC         pglDeleteBuffersARB = 0;          // VBO Deletion Procedure
PFNGLGETBUFFERPARAMETERIVARBPROC  pglGetBufferParameterivARB = 0;   // return various parameters of VBO
PFNGLMAPBUFFERARBPROC             pglMapBufferARB = 0;              // map VBO procedure
PFNGLUNMAPBUFFERARBPROC           pglUnmapBufferARB = 0;            // unmap VBO procedure


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
    glGenBuffersARB = (PFNGLGENBUFFERSARBPROC)wglGetProcAddress("glGenBuffersARB");
    glBindBufferARB = (PFNGLBINDBUFFERARBPROC)wglGetProcAddress("glBindBufferARB");
    glBufferDataARB = (PFNGLBUFFERDATAARBPROC)wglGetProcAddress("glBufferDataARB");
    glBufferSubDataARB = (PFNGLBUFFERSUBDATAARBPROC)wglGetProcAddress("glBufferSubDataARB");
    glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC)wglGetProcAddress("glDeleteBuffersARB");
    glGetBufferParameterivARB = (PFNGLGETBUFFERPARAMETERIVARBPROC)wglGetProcAddress("glGetBufferParameterivARB");
    glMapBufferARB = (PFNGLMAPBUFFERARBPROC)wglGetProcAddress("glMapBufferARB");
    glUnmapBufferARB = (PFNGLUNMAPBUFFERARBPROC)wglGetProcAddress("glUnmapBufferARB");
};

#define STRESS_TEST
#define VBO_RENDER

void Video::render( void )
{
	glClear( GL_COLOR_BUFFER_BIT );

	if ( model == nullptr ) return;

	glColor4f( 1.0, 1.0, 1.0, 1.0 );

	currentCam.transform();

	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	/**
	 * monkHiRes.raw has 3936 triangles
	 * stress tests involve 125 of these models (492000 triangles)
	 * SINGLE VBO		- ~1200 fps
	 * SINGLE NO BUFFER	- ~780 fps
	 * STRESS VBO		- ~420 fps
	 * STRESS NO BUFFER - ~15 fps
	 */

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