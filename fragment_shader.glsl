uniform sampler2D surfaceTexture;
uniform sampler2D lightmapTexture;

varying vec3 normal;
varying vec3 pos;

void main( void )
{
	gl_FragColor = texture( surfaceTexture, gl_TexCoord[ 0 ] ) * texture( lightmapTexture, gl_TexCoord[ 1 ] ) * 2.0;
};