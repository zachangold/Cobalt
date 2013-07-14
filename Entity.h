#ifndef EntityH
#define EntityH

#include <iostream>
using namespace std;

#include "Model.h"
#include "Texture.h"
#include "Entity.h"

class Entity
{
public:
	Entity( void );
	~Entity( void );

	/**
	 * Draws the entity. The camera is there just for binary-space
	 * partitioning culling and frustum culling
	 */
	virtual void draw( Camera& camera );

};

#endif /* EntityH */