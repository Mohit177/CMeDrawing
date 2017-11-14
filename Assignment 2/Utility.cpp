/**	@file Utility.cpp
Utility functions implementation file.
*/

#include "Utility.h"

/**
Empty constructor to initialize a point in 3D coordinate space.
*/
Point3::Point3(){
	x=0;
	y=0;
	z=0;
}

/**
Constructor to initialize a point in 3D coordinate space, with passed parameters.
@param x_: x coordinate
@param y_: y coordinate
@param z_: z coordinate
*/
Point3::Point3(float x_, float y_, float z_){
	x=x_;
	y=y_;
	z=z_;
}

/**
Method to set a 3D point with passed parameters.
@param x_: x coordinate
@param y_: y coordinate
@param z_: z coordinate
@return: void
*/
void Point3::set(float x_, float y_, float z_){
	x=x_;
	y=y_;
	z=z_;
}


/**
Method to set a 3D point with another 3D point.
@param x_: x coordinate
@param y_: y coordinate
@param z_: z coordinate
@return: void
*/
void Point3::set(Point3 p){
	x=p.x;
	y=p.y;
	z=p.z;
}


/**
Empty constructor to initialize a 3D vector.
*/
Vector3::Vector3(){
	x=0; y=0; z=0;
}

/**
Constructor to initialize a 3D vector, with passed parameters.
@param x_: x coordinate
@param y_: y coordinate
@param z_: z coordinate
*/
Vector3::Vector3(float x_, float y_, float z_){
	x=x_;
	y=y_;
	z=z_;
}


/**
Method to set a 3D vector with passed parameters.
@param x_: x coordinate
@param y_: y coordinate
@param z_: z coordinate
@return: void
*/
void Vector3::set(float x_, float y_, float z_){
	x=x_;
	y=y_;
	z=z_;
}

/**
Method to set a 3D vector with another 3D vector.
@param x_: x coordinate
@param y_: y coordinate
@param z_: z coordinate
@return: void
*/
void Vector3::set(Vector3 v){
	x=v.x;
	y=v.y;
	z=v.z;
}

/**
Method to normalize a 3D vector.
@param x_: x coordinate
@param y_: y coordinate
@param z_: z coordinate
@return: void
*/
void Vector3::normalize(){
	x=(float(x))/sqrt(x*x + y*y + z*z);
	y=(float(y))/sqrt(x*x + y*y + z*z);
	z=(float(z))/sqrt(x*x + y*y + z*z);
}

/**
Method to find dot product with another 3D vector.
@param x_: x coordinate
@param y_: y coordinate
@param z_: z coordinate
@return: dot product
*/
float Vector3::dot(Vector3 b){
	float result;
	result = (x * b.x) + (y * b.y) + (z * b.z);
	return result;
}

/**
Method to find cross product with another 3D vector.
@param x_: x coordinate
@param y_: y coordinate
@param z_: z coordinate
@return: cross product
*/
Vector3 Vector3::cross(Vector3 b){
	Vector3 result;
	result.x= y* b.z - z * b.y;
	result.y= z * b.x - x * b.z;
	result.z= x * b.y - y * b.x;
	return result;
}

/**
Method to find difference vector, with another 3D vector.
@param x_: x coordinate
@param y_: y coordinate
@param z_: z coordinate
@return: dot product
*/
Vector3 Vector3::diff(Vector3 b)
{
	Vector3 result;
	result.x = x-b.x;
	result.y = y-b.y;
	result.z = z-b.z;
	return result;
}
