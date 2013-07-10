#ifndef EntityH
#define EntityH

#include <iostream>
using namespace std;

#include "Model.h"
#include "Texture.h"

class Entity
{
public:
	Entity( void );
	~Entity( void );


protected:
	void loadModel( string modelPath );
	void loadTexture( string texPath );


private:
	//Texture& texture;
	//Model& model;


};

#endif /* EntityH */