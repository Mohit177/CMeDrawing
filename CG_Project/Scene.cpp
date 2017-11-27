/** \file Scene.h
Implementation file for functions to draw primitive shapes & other objects.
*/

#include "Scene.h"
#include "Utility.h"
#include <fstream>
#include <vector>
#include <map>
#include <cstring>
#include <cstdlib>
using namespace std;

/**
Face struct for a face of object
*/
struct Face
{
	int p1;	//!< First point
	int p2; //!< Second point
	int p3; //!< Third point
};

/**
Vertex struct for vertex of object	
*/
struct TVertex
{
	Vector3 v1;	//!< First vertex
	Vector3 v2;	//!< Second vertex
	Vector3 v3;	//!< Third vertex
};
vector<GLfloat> vtriangs;
GLfloat* tarray;
GLfloat* carray;
GLfloat* garray;

void importFile(string fname)
{
	vtriangs.clear();
	ifstream ifil;
	ifil.open(fname.c_str());
	string line;
	while(!ifil.eof())
	{
		getline(ifil,line);
		//cout<<line<<endl;
		if(line.length()>0)
		{
			int size = line.length();
			int i;
			string temp="";
			for(i=0;i<size;i++)
			{
				if(line[i]==' ')
				{
					vtriangs.push_back(atof(temp.c_str()));
					temp="";
				}
				else
				{
					temp.push_back(line[i]);
				}
			}
			if(temp.size()>0)
			{
				vtriangs.push_back(atof(temp.c_str()));
			}
		}
	}
	ifil.close();
	//cout<<vtriangs.size()<<endl;
	int size = vtriangs.size();
	tarray = new GLfloat[size];
	carray = new GLfloat[size];
	garray = new GLfloat[size];
	int i;
	int j=0;
	for(i=0;i<size;i++)
	{
		j++;
		tarray[i] = vtriangs[i];
		garray[i]=0.0;
		if(j%3==0)
		{
			carray[i] = 0.1;
		}
		else
		{
			carray[i] = 0.5;
		}
	}
	//cout<<vtriangs.size()<<endl;
}

void drawFile()
{
	//int size = vtriangs.size();
	//cout<<"here"<<size<<endl;
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glEnable(GL_POLYGON_OFFSET_LINE);
	glPolygonOffset(-1.f,-1.f);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, tarray);
	glColorPointer(3, GL_FLOAT, 0, garray);
	glDrawArrays(GL_TRIANGLES, 0, vtriangs.size()/3);
	glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, tarray);
    glColorPointer(3, GL_FLOAT, 0, carray);
    glDrawArrays(GL_TRIANGLES, 0, vtriangs.size()/3);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}
