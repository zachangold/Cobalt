#ifndef CameraH
#define CameraH

#include "Input.h"
#include "Math.h"

class Camera
{
public:
	typedef enum
	{
		GHOST = 1,	// Fly around the map freely
		FIXED,		// Fixed to some entity (not usable atm)
		THIRDPERSON // Fixed to rotate around some entity (not usable atm)
	} Mode;

	Camera( void );
	Camera( Mode mode );
	~Camera( void );

	Point3f &getPosition( void ) { return position; };
	Point3f &getRotation( void ) { return rotation; };

	void transform( void );
	void update( Input& input );

private:
	Point3f position;
	Point3f rotation;
	Mode mode;
};

#endif /* CameraH */