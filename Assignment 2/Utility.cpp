#include "Utility.h"

Point3::Point3(){
	x=0; y=0; z=0;
}

Point3::Point3(float dx, float dy, float dz){
	x=dx; y=dy; z=dz;
}

void Point3::set(float dx, float dy, float dz){
	x=dx;
	y=dy;
	z=dz;
}

void Point3::set(Point3 p){
	x=p.x;
	y=p.y;
	z=p.z;
}

Vector3::Vector3(){
	x=0; y=0; z=0;
}

Vector3::Vector3(float dx, float dy, float dz){
	x=dx; y=dy; z=dz;
}

void Vector3::set(float dx, float dy, float dz){
	x=dx;
	y=dy;
	z=dz;
}

void Vector3::set(Vector3 v){
	x=v.x;
	y=v.y;
	z=v.z;
}

void Vector3::normalize(){
	x=(float(x))/sqrt(x*x + y*y + z*z);
	y=(float(y))/sqrt(x*x + y*y + z*z);
	z=(float(z))/sqrt(x*x + y*y + z*z);
}

float Vector3::dot(Vector3 b){
	float result;
	result= x * b.x + y * b.y + z * b.z;
	return result;
}

Vector3 Vector3::cross(Vector3 b){
	Vector3 result;
	result.x= y* b.z - z * b.y;
	result.y= z * b.x - x * b.z;
	result.z= x * b.y - y * b.x;
	return result;
}

Vector3 Vector3::diff(Vector3 b)
{
	Vector3 result;
	result.x = x-b.x;
	result.y = y-b.y;
	result.z = z-b.z;
	return result;
}