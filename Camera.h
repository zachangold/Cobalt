#ifndef CameraH
#define CameraH

#include "Input.h"

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


	void transform( void );
	void update( Input& input );

private:
	float x, y, z;
	float pitch, yaw, roll;
	Mode mode;
};

#endif /* CameraH */