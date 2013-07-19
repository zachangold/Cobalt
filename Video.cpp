#include "Video.h"

PFNGLGENBUFFERSPROC            pglGenBuffers = 0;             // VBO Name Generation Procedure
PFNGLBINDBUFFERPROC            pglBindBuffer = 0;             // VBO Bind Procedure
PFNGLBUFFERDATAPROC            pglBufferData = 0;             // VBO Data Loading Procedure
PFNGLBUFFERSUBDATAPROC         pglBufferSubData = 0;          // VBO Sub Data Loading Procedure
PFNGLDELETEBUFFERSPROC         pglDeleteBuffers = 0;          // VBO Deletion Procedure
PFNGLGETBUFFERPARAMETERIVPROC  pglGetBufferParameteriv = 0;   // return various parameters of VBO
PFNGLMAPBUFFERPROC             pglMapBuffer = 0;              // map VBO procedure
PFNGLUNMAPBUFFERPROC           pglUnmapBuffer = 0;            // unmap VBO procedure

PFNGLCREATESHADERPROC          glCreateShader = 0;
PFNGLSHADERSOURCEPROC          glShaderSource = 0;
PFNGLCOMPILESHADERPROC         glCompileShader = 0;

PFNGLCREATEPROGRAMPROC glCreateProgram = 0;
PFNGLATTACHSHADERPROC glAttachShader = 0;
PFNGLDETACHSHADERPROC glDetachShader = 0;
PFNGLLINKPROGRAMPROC glLinkProgram = 0;
PFNGLUSEPROGRAMPROC glUseProgram = 0;
PFNGLDELETEPROGRAMPROC glDeleteProgram = 0;
PFNGLDELETESHADERPROC glDeleteShader = 0;

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

	glCreateShader = ( PFNGLCREATESHADERPROC ) wglGetProcAddress( "glCreateShader" );
	glShaderSource = ( PFNGLSHADERSOURCEPROC ) wglGetProcAddress( "glShaderSource" );
	glCompileShader = ( PFNGLCOMPILESHADERPROC ) wglGetProcAddress( "glCompileShader" );

	glCreateProgram = ( PFNGLCREATEPROGRAMPROC ) wglGetProcAddress( "glCreateProgram" );
	glAttachShader = ( PFNGLATTACHSHADERPROC ) wglGetProcAddress( "glAttachShader" );
	glDetachShader = ( PFNGLDETACHSHADERPROC ) wglGetProcAddress( "glDetachShader" );
	glLinkProgram = ( PFNGLLINKPROGRAMPROC ) wglGetProcAddress( "glLinkProgram" );
	glUseProgram = ( PFNGLUSEPROGRAMPROC ) wglGetProcAddress( "glUseProgram" );

	glDeleteProgram = ( PFNGLDELETEPROGRAMPROC ) wglGetProcAddress( "glDeleteProgram" );
	glDeleteShader = ( PFNGLDELETESHADERPROC ) wglGetProcAddress( "glDeleteShader" );

	texture.load( "mat/error.bmp" );
	//texture.load( "mat/Q2/models/monsters/tank/skin.pcx" );
	map.load( "mat/Q2/maps/base1.bsp" );

	glColor4f( 1.0, 1.0, 1.0, 1.0 );
	//glEnable( GL_CULL_FACE );
	glFrontFace( GL_CW );
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_DEPTH_TEST );

	GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_shininess[] = { 0.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat light_diffuse[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat light_specular[] = { 0.0, 0.0, 0.0, 1.0 };
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	vertexShader.create( GL_VERTEX_SHADER, "vertex_shader.glsl" );
	fragmentShader.create( GL_FRAGMENT_SHADER, "fragment_shader.glsl" );
	prog.create();
	prog.attachShader( vertexShader );
	prog.attachShader( fragmentShader );
	prog.link();
	prog.use();
	prog.detachShader( vertexShader );
	prog.detachShader( fragmentShader );
};

//#define STRESS_TEST
//#define VBO_RENDER

void Video::render( void )
{
	glClear( GL_COLOR_BUFFER_BIT );
	glClear( GL_DEPTH_BUFFER_BIT );

	//glDisable( GL_TEXTURE_2D );
	
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	GLfloat lightPos[ 4 ] = { currentCam.getX(), currentCam.getY(), currentCam.getZ(), 0.0f };
	/*
	glDisable( GL_LIGHTING );
	glPushMatrix();
		currentCam.transform();
		glTranslatef( lightPos[ 0 ], lightPos[ 1 ], lightPos[ 2 ] );
		model->getVBO().draw();
	glPopMatrix();
	*/

	glEnable( GL_LIGHTING );
	glLightfv( GL_LIGHT0, GL_POSITION, lightPos );
	glPushMatrix();
		currentCam.transform();
		glScalef( 0.01f, 0.01f, 0.01f );
		//GLfloat lightPos[ 3 ] = { 0.0f, 1.0f, 0.0f };

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
	/*
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
	*/
};