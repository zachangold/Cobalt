varying vec3 normal;
varying vec3 pos;

void main( void )
{
    //gl_FragColor = vec4(abs(normal[0]), abs(normal[1]), abs(normal[ 2 ]), 1.0);
	//gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
	//float dist = distance( gl_LightSource[ 0 ].position.xyz, pos );

	//float attenFactor = 1.0/( gl_LightSource[0].constantAttenuation + 
	//					gl_LightSource[0].linearAttenuation * dist +
	//					gl_LightSource[0].quadraticAttenuation * dist * dist );
	vec3 lightDir = normalize( pos - gl_LightSource[ 0 ].position.xyz );
	normal = normalize( normal );

	float col = -dot( lightDir, normal );

	if ( col < 0.0f )
	{
		col = 0.0f;
	}

	gl_FragColor = vec4( col, col, col, 1 );
};