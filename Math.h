#ifndef MathH
#define MathH

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
		float mag = sqrt( x * x + y * y + z * z );
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

typedef struct Point4f
{
	Point4f( void )
	{
		set( 0.0, 0.0, 0.0, 0.0 );
	};

	Point4f( Point3f &p )
	{
		set( p.x, p.y, p.z, 0.0 );
	};

	Point4f( float x, float y, float z, float a )
	{
		set( x, y, z, a );
	};

	void set( float x, float y, float z, float a )
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->a = a;
	};

	float x, y, z, a;
} Point4f;

// TODO: Doesn't belong here
typedef struct Colour4f
{
	Colour4f( void )
	{
		set( 0.0, 0.0, 0.0, 0.0 );
	};

	Colour4f( float r, float g, float b, float a )
	{
		set( r, g, b, a );
	};

	void set( float r, float g, float b, float a )
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	};

	float r, g, b, a;
} Colour4f;


#endif /* MathH */