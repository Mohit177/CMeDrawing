/** @file Utility.h
Utility functions header file.
*/

#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include <cmath>
using namespace std;
/**
Class to represent 3D point in space.
*/
class Point3 
{
	public: 
		
		float x;	//!< x coordinate 
		float y;	//!< y coordinate 
		float z;	//!< z coordinate 
		Point3();
		Point3(float, float, float);
		void set(float, float, float);
		void set(Point3 p);
};

/**
Class to represent a 3D vector in space.
*/
class Vector3
{
	public:
		float x; //!< x component of vector
		float y; //!< y component of vector
		float z; //!< z component of vector
		Vector3();
		Vector3(float, float, float);
		void set(float, float, float);
		void set(Vector3 v);
		void normalize();
		float dot(Vector3 b);
		Vector3 cross(Vector3 b);
		Vector3 diff(Vector3 b);
};

#endif
