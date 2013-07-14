#ifndef MapH
#define MapH

#include "Entity.h"

class Map : public Entity
{
public:
	Map( void );
	Map( string fileName );
	virtual ~Map( void );

	void load( string fileName );
	void unload( void );

	void draw( Camera &camera );

protected:
	

private:
	void loadBSP( void )

};


#endif /* MapH */