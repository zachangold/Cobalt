#include "Shader.h"


Shader::Shader( void )
{
	handle = 0xFFFFFFFF;
};


Shader::~Shader( void )
{
	destroy();
};
