uniform sampler2D surfaceTexture;
uniform sampler2D lightmapTexture;

varying vec3 normal;
varying vec3 pos;

void main( void )
{
	vec3 lightVector = gl_LightSource[ 0 ].position.xyz - pos;
	float dist = length( lightVector );
	float attenuationFactor = 1.0 / (gl_LightSource[ 0 ].constantAttenuation + dist * gl_LightSource[ 0 ].linearAttenuation + dist * dist * gl_LightSource[ 0 ].quadraticAttenuation );
	lightVector /= dist;
	float lightMultiplier = dot( lightVector, normalize( normal ) ) * attenuationFactor;

	gl_FragColor = lightMultiplier * texture( surfaceTexture, gl_TexCoord[ 0 ] );
	//gl_FragColor = texture( surfaceTexture, gl_TexCoord[ 0 ] ) * texture( lightmapTexture, gl_TexCoord[ 1 ] ) * 2.0;
	//gl_FragColor = texture( surfaceTexture, gl_TexCoord[ 0 ] );
};