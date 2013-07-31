#ifndef PipelineH
#define PipelineH

#include "GLFunctions.h"

/**
 * Currently unused/unimplemented, but in the future will hold the
 * openGL pipeline handle, which (to my knowledge) is a number of 
 * custom programs for the graphics card. Pipelines will become more
 * useful as the concepts that we want to use become more complex.
 */
class Pipeline
{
public:
	Pipeline( void );
	~Pipeline( void );

private:
	//GLuint handle;
};

#endif /* PipelineH */