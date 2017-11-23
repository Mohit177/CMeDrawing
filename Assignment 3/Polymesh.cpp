#include "Polymesh.h"

Point2::Point2()
{
	this->x = 0;
	this->y = 0;
}

Point2::Point2(double x,double y)
{
	this->x = x;
	this->y = y;
}

void Point2::setCords(double x, double y)
{
	this->x = x;
	this->y = y;
}

Point3::Point3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Point3::Point3(double x,double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}


Polymesh::Polymesh(){
	this->n_vertices = 0;
	this->n_faces = 0;	
}

Polymesh::Polymesh(int n_ver, int n_fac){
	this->n_vertices = n_ver;
	this->n_faces = n_fac;	
	this->vertices.resize(n_ver);
	this->faces.resize(n_fac);
}

void generateMesh(std::vector<Point2> points){
	
		// To-Do
}


