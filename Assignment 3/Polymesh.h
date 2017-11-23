#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <cstring>

const int SCREEN_WIDTH = 1300.0;
const int SCREEN_HEIGHT = 744.0;

class Point2
{
	public:
		double x,y;
		Point2();
		Point2(double x, double y);
		void setCords(double x, double y);
};

class Point3
{
	public:
		double x,y,z;
		Point3();
		Point3(double x, double y, double z);
};

struct Face{
	int vertices[4];
};


class Polymesh
{
	public:
		int n_vertices;
		int n_faces;
		std::vector<Point3> vertices;
		std::vector<Face> faces;
	
		Polymesh();
		Polymesh(int n_ver, int n_face);
		void generateMesh(std::vector<Point2> points, int slices);
		void writeToFile(const std::string& filename);
};


