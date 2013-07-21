uniform sampler2D texture1;
uniform sampler2D textureLightmap;

varying vec3 normal;
varying vec3 pos;

void main( void )
{
	gl_FragColor = texture( texture1, gl_TexCoord[ 0 ] ) * texture( textureLightmap, gl_TexCoord[ 1 ] ) * 2.0;
};