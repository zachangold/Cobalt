varying vec3 normal;
varying vec3 pos;

void main( void )
{
	pos = vec3( gl_ModelViewMatrix * gl_Vertex );
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	normal = gl_Normal;
};