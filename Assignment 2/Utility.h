#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include <cmath>
using namespace std;

class Point3 
{
	public: 
		
		float x,y,z;
		Point3();
		Point3(float dx, float dy, float dz);
		void set(float dx, float dy, float dz);
		void set(Point3 p);
};

class Vector3
{
	public:
		float x,y,z;
		Vector3();
		Vector3(float dx, float dy, float dz);
		void set(float dx, float dy, float dz);
		void set(Vector3 v);
		void normalize();
		float dot(Vector3 b);
		Vector3 cross(Vector3 b);
		Vector3 diff(Vector3 b);
};

#endif
