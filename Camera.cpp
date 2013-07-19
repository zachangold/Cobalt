#include "Camera.h"
#include <math.h>
#include <gl/GL.h>
#include <gl/GLU.h>

Camera::Camera( void )
{
	mode = GHOST;
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	pitch = 0.0f;
	yaw = 0.0f;
	roll = 0.0f;
};

Camera::Camera( Mode mode )
{
	this->mode = mode;
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	pitch = 0.0f;
	yaw = 0.0f;
	roll = 0.0f;
};

Camera::~Camera( void )
{

};


void Camera::transform( void )
{
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 60.0, 4.0/3.0, 0.1, 100.0 );
	
	glRotatef( pitch * 180.0f / 3.14159f, 1.0f, 0.0f, 0.0f );
	glRotatef(   yaw * 180.0f / 3.14159f, 0.0f, 1.0f, 0.0f );
	glRotatef(  roll * 180.0f / 3.14159f, 0.0f, 0.0f, 1.0f );
	glTranslatef( -x, -y, -z );

	glMatrixMode( GL_MODELVIEW );
};

void Camera::update( Input& input )
{
	const float SPEED = 0.03f;
	const float ROT_SPEED = 0.001f;

	if ( input.keyDown( DIK_W ) )
	{
		x += SPEED * sin( yaw ) * cos( pitch );
		y -= SPEED * sin( pitch );
		z -= SPEED * cos( yaw ) * cos( pitch );
	}
	if ( input.keyDown( DIK_S ) )
	{
		x -= SPEED * sin( yaw ) * cos( pitch );
		y += SPEED * sin( pitch );
		z += SPEED * cos( yaw ) * cos( pitch );
	}
	if ( input.keyDown( DIK_A ) )
	{
		x -= SPEED * cos( yaw );
		z -= SPEED * sin( yaw );
	}
	if ( input.keyDown( DIK_D ) )
	{
		x += SPEED * cos( yaw );
		z += SPEED * sin( yaw );
	}
	if ( input.keyDown( DIK_SPACE ) )
	{
		y += SPEED;
	}
	if ( input.keyDown( DIK_LCONTROL ) )
	{
		y -= SPEED;
	}

	yaw += input.getRelX() * input.getSensitivity();
	pitch += input.getRelY() * input.getSensitivity();
	if ( input.buttonDown( DIMOUSE_LEFTBUTTON ) )
	{
		pitch = 0.0f;
		yaw = 0.0f;
	}
};
