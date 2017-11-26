/** \file Polymesh.h
Header file for Polymesh data structure
*/
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <cstring>

const int SCREEN_WIDTH = 1300.0;  //!< Width of screen/window, in pixels
const int SCREEN_HEIGHT = 744.0;  //!< Height of screen/window, in pixels


/**
Point2 class for representing a 2D point in xy coordinate system.
It repersents the position of a pixel on the screen, with top-left corner as origin.
*/
class Point2
{
	public:
		double x;  //!< x-coordinate of the point
		double y;  //!< y-coordinate of the point
		Point2();
		Point2(double x, double y);
		void setCords(double x, double y);
};


/**
Point3 class for representing a 3D point in xyz coordinate space.
*/
class Point3
{
	public:
		double x;	//!< x-coordinate of the point
		double y;	//!< y-coordinate of the point
		double z;	//!< z-coordinate of the point
		Point3();
		Point3(double x, double y, double z);
};

/**
Face structure, which contains indexes of vertices in the Polymesh.
*/
struct Face{
	int vertices[4];	//!< Indices of the four vertices of a face in the Polymesh
};

/**
Polymesh class to represent a Polymesh in 3D space.
*/
class Polymesh
{
	public:
		std::vector<Point3> vertices;	//!< Vector of vertices(Point3 with x,y,z coordinates) of the Polymesh.
		std::vector<Face> faces;		//!< Vector of faces(contains indices of vertices) of the Polymesh.
	
		Polymesh();
		Polymesh(int n_ver, int n_face);
		void generateMesh(std::vector<Point2> points, int slices);
		void writeToFile(const std::string& filename);
};


