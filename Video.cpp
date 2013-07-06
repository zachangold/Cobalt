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


void Video::render( void )
{
	glClear( GL_COLOR_BUFFER_BIT );

	if ( model == nullptr ) return;

	glColor4f( 1.0, 1.0, 1.0, 1.0 );

	currentCam.transform();

	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	glBegin( GL_TRIANGLES );
		for ( int i = 0; i < model->getVertices().size(); ++i )
		{
			Vertex v = model->getVertices()[ i ];
			glVertex3f( v.x, v.y, v.z );
		}
	glEnd();
};