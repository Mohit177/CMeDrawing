/** \file Polymesh.cpp
Implementation file for Polymesh data structure
*/
#include "Polymesh.h"

/**
Default constructor for Point2 class
*/
Point2::Point2()
{
	this->x = 0;
	this->y = 0;
}


/**
Constructor for Point2 class.
@param x : x coordinate of the point
@param y : y coordinate of the point
*/
Point2::Point2(double x,double y)
{
	this->x = x;
	this->y = y;
}

/**
Function to set coordinates of a point represented by Point2 class object.
@param x : x coordinate of the point
@param y : y coordinate of the point
@return: nothing
*/
void Point2::setCords(double x, double y)
{
	this->x = x;
	this->y = y;
}


/**
Default constructor for Point3 class
*/
Point3::Point3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

/**
Constructor for Point2 class.
@param x : x coordinate of the point
@param y : y coordinate of the point
@param z : z coordinate of the point
*/
Point3::Point3(double x,double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

/**
Default constructor for Polymesh class
*/
Polymesh::Polymesh(){
	this->vertices.clear();
	this->faces.clear();	
}

/**
Constructor for Polymesh class.
@param n_vertices : x coordinate of the point
@param n_faces : y coordinate of the point
*/
Polymesh::Polymesh(int n_vertices, int n_faces){	
	this->vertices.resize(n_vertices);
	this->faces.resize(n_faces);
}

/**
\brief Function to generate the Polymesh from a set of 2D points in xy coordinate system.
It samples the points vector for every 50th point, and finds the set of points around the axis of revolution.
@param points : Vector of points(pixels on the curve)
@param slices : number of slices along the y axis, which determines the angle of rotation for each point generation.
@return : void
*/
void Polymesh::generateMesh(std::vector<Point2> points, int slices){
	int vec_size = points.size();
	std:: cout << "Buffer size: " << vec_size <<"\n";
	for(Point2& p:points){
		p.x = p.x - SCREEN_WIDTH/2;
		p.y = SCREEN_HEIGHT - p.y;
	}
	
	int layers = 0;
	for(int v=0;v<vec_size;v+=50){
		double radius = points[v].x;
		
		for(double angle= (double)0.0; angle < (double)360.0;angle += (double)360.0/slices){
			Point3 temp;
			temp.x = radius*cos(angle*M_PI/180.0);
			temp.y = points[v].y;
			temp.z = radius*sin(angle*M_PI/180.0);
			(this->vertices).push_back(temp);
		}
		layers++;
	}
	int ref=0;
	for(int i=1;i<layers;i++){
		for(int k=0;k<slices;k++){
			Face f;
			f.vertices[0] = ref+k;
			f.vertices[1] = ref+k+slices;
			f.vertices[2] = ref+slices+(k+1)%slices;
			f.vertices[3] = ref+(k+1)%slices;
			this->faces.push_back(f);
		}
		ref += slices;
	}
}

/**
Function to write the Polymesh to an output file in OFF format.
Visit <a href="http://people.sc.fsu.edu/~jburkardt/data/off/off.html">OFF file format</a> for more details. \n Installing <a href="http://www.meshlab.net/">Meshlab</a> is suggested for visualization.
@param filename : Name of output file.
@return : void
*/
void Polymesh::writeToFile(const std::string& filename){
	std::ofstream file_stream;
	file_stream.open(filename);
	file_stream << "OFF\n";
	file_stream << this->vertices.size() << " " << this->faces.size() << " 0\n";
	for(auto p:this->vertices){
		file_stream << p.x << " " << p.y << " " << p.z << "\n";
	}
	for(auto f:this->faces){
		file_stream << 4 << " " << f.vertices[0] <<" "<< f.vertices[1] <<" "<< f.vertices[2] <<" "<< f.vertices[3] << "\n";
	}
	file_stream.close();
}

