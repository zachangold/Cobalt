#ifndef CameraH
#define CameraH

#include "Input.h"
#include <math.h>

typedef struct Point3f
{
	Point3f( void )
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	};

	Point3f( float x, float y, float z )
	{
		this->x = x;
		this->y = y;
		this->z = z;
	};

	Point3f cross( Point3f rhs )
	{
		Point3f rtn;
		rtn.x = y * rhs.z - z * rhs.y;
		rtn.y = z * rhs.x - x * rhs.z;
		rtn.z = x * rhs.y - y * rhs.x;
		return rtn;
	};

	void normalize( void )
	{
		int mag = sqrt( x * x + y * y + z * z );
		x /= mag;
		y /= mag;
		z /= mag;
	};

	Point3f operator - ( Point3f other )
	{
		return Point3f( x - other.x, y - other.y, z - other.z );
	};

	float dot( Point3f other )
	{
		return x * other.x + y * other.y + z * other.z;
	};

	Point3f operator * ( float r )
	{
		return Point3f( x * r, y * r, z * r );
	};

	float x, y, z;
} Point3f;

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