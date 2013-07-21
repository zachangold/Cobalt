#include "Camera.h"
#include <math.h>
#include <gl/GL.h>
#include <gl/GLU.h>

Camera::Camera( void )
{
	mode = GHOST;
};

Camera::Camera( Mode mode )
{
	this->mode = mode;
};

Camera::~Camera( void )
{

};


void Camera::transform( void )
{
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 60.0, 4.0/3.0, 0.1, 100.0 );
	
	glRotatef( rotation.x * 180.0f / 3.14159f, 1.0f, 0.0f, 0.0f );
	glRotatef( rotation.y * 180.0f / 3.14159f, 0.0f, 1.0f, 0.0f );
	glRotatef( rotation.z * 180.0f / 3.14159f, 0.0f, 0.0f, 1.0f );
	glTranslatef( -position.x, -position.y, -position.z );

	glMatrixMode( GL_MODELVIEW );
};

void Camera::update( Input& input )
{
	const float SPEED = 0.03f;
	const float ROT_SPEED = 0.001f;

	if ( input.keyDown( DIK_W ) )
	{
		position.x += SPEED * sin( rotation.y ) * cos( rotation.x );
		position.y -= SPEED * sin( rotation.x );
		position.z -= SPEED * cos( rotation.y ) * cos( rotation.x );
	}
	if ( input.keyDown( DIK_S ) )
	{
		position.x -= SPEED * sin( rotation.y ) * cos( rotation.x );
		position.y += SPEED * sin( rotation.x );
		position.z += SPEED * cos( rotation.y ) * cos( rotation.x );
	}
	if ( input.keyDown( DIK_A ) )
	{
		position.x -= SPEED * cos( rotation.y );
		position.z -= SPEED * sin( rotation.y );
	}
	if ( input.keyDown( DIK_D ) )
	{
		position.x += SPEED * cos( rotation.y );
		position.z += SPEED * sin( rotation.y );
	}
	if ( input.keyDown( DIK_SPACE ) )
	{
		position.y += SPEED;
	}
	if ( input.keyDown( DIK_LCONTROL ) )
	{
		position.y -= SPEED;
	}

	rotation.y += input.getRelX() * input.getSensitivity();
	rotation.x += input.getRelY() * input.getSensitivity();
	if ( input.buttonDown( DIMOUSE_LEFTBUTTON ) )
	{
		rotation.x = 0.0f;
		rotation.y = 0.0f;
	}
};
