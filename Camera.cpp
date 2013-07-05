#include "Camera.h"
#include <math.h>
#include <gl/GL.h>

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
	glRotatef( pitch * 180.0 / 3.14159, 1.0, 0.0, 0.0 );
	glRotatef(   yaw * 180.0 / 3.14159, 0.0, 1.0, 0.0 );
	glRotatef(  roll * 180.0 / 3.14159, 0.0, 0.0, 1.0 );
	glTranslatef( -x, -y, -z );
};

void Camera::update( Input& input )
{
	const float SPEED = 0.003;
	const float ROT_SPEED = 0.001;

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
