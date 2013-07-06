#ifndef VideoH
#define VideoH

#include <vector>
using namespace std;

#include "Window.h"
#include "Camera.h"
#include "Model.h"

extern PFNGLGENBUFFERSARBPROC            pglGenBuffersARB;             // VBO Name Generation Procedure
extern PFNGLBINDBUFFERARBPROC            pglBindBufferARB;             // VBO Bind Procedure
extern PFNGLBUFFERDATAARBPROC            pglBufferDataARB;             // VBO Data Loading Procedure
extern PFNGLBUFFERSUBDATAARBPROC         pglBufferSubDataARB;          // VBO Sub Data Loading Procedure
extern PFNGLDELETEBUFFERSARBPROC         pglDeleteBuffersARB;          // VBO Deletion Procedure
extern PFNGLGETBUFFERPARAMETERIVARBPROC  pglGetBufferParameterivARB;   // return various parameters of VBO
extern PFNGLMAPBUFFERARBPROC             pglMapBufferARB;              // map VBO procedure
extern PFNGLUNMAPBUFFERARBPROC           pglUnmapBufferARB;            // unmap VBO procedure

#define glGenBuffersARB           pglGenBuffersARB
#define glBindBufferARB           pglBindBufferARB
#define glBufferDataARB           pglBufferDataARB
#define glBufferSubDataARB        pglBufferSubDataARB
#define glDeleteBuffersARB        pglDeleteBuffersARB
#define glGetBufferParameterivARB pglGetBufferParameterivARB
#define glMapBufferARB            pglMapBufferARB
#define glUnmapBufferARB          pglUnmapBufferARB

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

	Model *model; 

private:
	Window &window;

	Camera &currentCam;
	Camera  defaultCam;

};

#endif /* VideoH */