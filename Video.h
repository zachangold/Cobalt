#ifndef VideoH
#define VideoH

#include <vector>
using namespace std;

#include "Window.h"
#include "Camera.h"
#include "Model.h"
#include "VertexBuffer.h"
#include "BSPMap.h"

#include "Program.h"
#include "Shader.h"

#include "Light.h"
#include "Material.h"

class Video
{
public:
	Video( Window &window );
	Video( Window &window, Camera &cam );
	~Video( void );

	void init( void );
	void setCamera( Camera& cam );
	void render( void );

	// This is purely temporary
	void update( Input &input )
	{
		defaultCam.update( input );
	};


private:
	Window &window;

	Camera &currentCam;
	Camera  defaultCam;

	Program prog;
	Shader vertexShader;
	Shader fragmentShader;

	Light light;
	Material material;

	BSPMap map;
};

#endif /* VideoH */