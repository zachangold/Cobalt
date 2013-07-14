#ifndef MapH
#define MapH

#include "Entity.h"

class Map : public Entity
{
public:
	Map( void );
	Map( string fileName );
	virtual ~Map( void );

	static Map *load( string fileName );
	void unload( void );

	virtual void draw( Camera &camera ) = 0;

protected:
	

private:


};


#endif /* MapH */