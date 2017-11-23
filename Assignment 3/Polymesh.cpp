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
	
/*	for(auto f: this->faces){
		for(int i=0;i<4;i++) std:: cout << f.vertices[i] <<" ";
		std::cout << "\n";
	}*/
}

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

