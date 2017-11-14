/** \file Scene.h
Implementation file for functions to draw primitive shapes & other objects.
*/

#include "Scene.h"
#include "Utility.h"
#include <fstream>
#include <vector>
#include <map>
#include <cstring>
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


vector<TVertex> vset;
vector<Vector3> cset;
GLfloat* varr;
GLfloat* carr;


/**
Method to draw a boundary centered at origin, with length, width & height 100,100 and 6.
@param void
@return void
*/
void drawBoundary(){

	// Rectangles
	GLfloat vertices[] =
    {
	    // Outer Boundary
		-50,0,50,	-3,0,50,	-3,6,50,	-50,6,50,		//Front left
		3,0,50,		50,0,50,	50,6,50,	3,6,50,			//Front right
		-50,0,-50,	-50,0,50,	-50,6,50,	-50,6,-50,		// Left
		50,0,50,	50,0,-50,	50,6,-50,	50,6,50,		// Right
		50,0,-50,	-50,0,-50,	-50,6,-50,	50,6,-50,		// Back
	    // Top of Boundary
		-50,6,50,	-3,6,50,	-3,6,47,	-50,6,47,		// Front Left
		3,6,50,		50,6,50,	50,6,47,	3,6,47,			// Front Right
		-50,6,-50,	-50,6,50,	-47,6,50,	-47,6,-50,		// Left
		50,6,50,	50,6,-50,	47,6,-50,	47,6,50,		// Right
		-50,6,-47,	50,6,-47,	50,6,-50,	-50,6,-50,		// Top
	    // Inner Boundary
		-47,0,47,	-3,0,47,	-3,6,47,	-47,6,47,	// Front Left
		3,0,47,		47,0,47,	47,6,47,	3,6,47,		// Front Right
		-47,0,47,	-47,0,-47,	-47,6,-47,	-47,6,47,	// Left
		47,0,47,	47,0,-47,	47,6,-47,	47,6,47,	// Left
		-47,0,-47,	47,0,-47,	47,6,-47,	-47,6,-47,	// back
		// Gate faces
		-3,0,47,	-3,0,50,	-3,6,50,	-3,6,47,		// Left
		3,0,47,		3,0,50,		3,6,50,		3,6,47,			// Right
		// Ground Bottom
		-50,0,50,	-50,0,3,	-3,0,3,	   -3,0,50,
        3,0,50,     3,0,3,      50,0,3,     50,0,50,
        -50,0,-3,   -50,0,-50,  -3,0,-50,   -3,0,-3,
        3,0,-3,     3,0,-50,    50,0,-50,   50,0,-3,
        // Roadways.
        -3,0,50,    -3,0,-50,   3,0,-50,    3,0,50,
        -47,0,3,    -47,0,-3,   47,0,-3,    47,0,3 
	};
	
	// Boundary
		
	GLfloat colors[sizeof(vertices)/sizeof(vertices[0])] = {0.0};
	
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
	
	
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glEnable(GL_POLYGON_OFFSET_LINE);
	glPolygonOffset(-1.f,-1.f);
    glDrawArrays(GL_QUADS, 0, 92);
	
	for(int i=0;i<204;i++){
		colors[i] = 0.2;
	}
	// Ground
	for(int i=204;i<204+48;i+=3){
		colors[i]	= 0.0;
		colors[i+1] = 128.0/255;
		colors[i+2] = 0.0;
	}
	// Roadways
	for(int i=252;i<252+24;i+=3){
		colors[i]	= 0.933;
		colors[i+1] = 0.855;
		colors[i+2] = 0.679;
	}
	
/*    static float alpha = 0;
    //attempt to rotate cube
   glRotatef(alpha, 1, 1, 1);			// Comment this line to stop rotation about y axis.
*/    


    /* Send data : 24 vertices */
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glDrawArrays(GL_QUADS, 0, 92);

    /* Cleanup states */
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
//	alpha+=1;
}

/**
Method to draw see-saw centered at origin, with length, width & height 16, 2 and 2.
@param void
@return void
*/
void drawSeeSaw(){

	// For rectangles
	glPushMatrix();
		GLfloat vert_rect[] = {-1,0,-1,	0,2,-1,		0,2,1,	-1,0,1,			1,0,-1,		0,2,-1,		0,2,1,	1,0,1};
		GLfloat vert_triangles[] = {-1,0,1,		0,2,1,		1,0,1,			-1,0,-1,	0,2,-1,	1,0,-1};

		GLfloat colors[96] = {0.0f};

		/* Enable color array and a vertex array */
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vert_rect);
		glColorPointer(3, GL_FLOAT, 0, colors);
    
		// Draw outline
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		glEnable(GL_POLYGON_OFFSET_LINE);
		glPolygonOffset(-1.f,-1.f);
		glEnable(GL_DEPTH_TEST);
		glDrawArrays(GL_QUADS, 0, 8);			// Draw wire rectangles
		
	    glDisableClientState(GL_COLOR_ARRAY);
	    glDisableClientState(GL_VERTEX_ARRAY);				
	glPopMatrix();

	glPushMatrix();
		static double alpha = 15.466009963004;
		static double d_angle = 0.8f;
		glRotatef(alpha,0,0,1);
		glPushMatrix();
			glTranslatef(-7.5,2,1);
			glScalef(15,0.3,2);
			glTranslatef(0,0,-1);
			drawUnitCube(0.0,0.0,1.0);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(-5.5,2,1);
			glScalef(0.3,1,2);
			glTranslatef(0,0,-1);
			drawUnitCube(0.0,0.0,1.0);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(5.5,2,1);
			glScalef(0.3,1,2);
			glTranslatef(0,0,-1);
			drawUnitCube(0.0,0.0,1.0);
		glPopMatrix();
		
		if(alpha >= 15.466009963004)
			d_angle = -0.8f;
		else if(alpha <= -15.466009963004)
			d_angle = 0.8f;
		alpha += d_angle;
	glPopMatrix();
//----		Solid -----
	glPushMatrix();
		// Set Red Color
		for(int i=0;i<96;i+=3){
			colors[i] = 1.0; colors[i+1]=0.0; colors[i+2]=0.0;
		}
    
		// Draw Triangles, 6 vertices
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vert_triangles);
		glColorPointer(3, GL_FLOAT, 0, colors);
		
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glVertexPointer(3, GL_FLOAT, 0, vert_rect);
		glColorPointer(3, GL_FLOAT, 0, colors);
		glDrawArrays(GL_QUADS, 0, 8);
	   
    
    /* Cleanup states */
	    glDisableClientState(GL_COLOR_ARRAY);
	    glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
    
}

/**
Method to draw a slide
@param void
@return void
*/
void drawSlide(){

	GLfloat vertices[] = 
	{
		// Rods to be slanted.
		// Vertical rods
		0,0,0,	1,0,0,	1,9,0,	0,9,0,
		0,0,4,	1,0,4,	1,9,4,	0,9,4,
		0,0,1,	1,0,1,	1,9,1,	0,9,1,
		0,0,5,	1,0,5,	1,9,5,	0,9,5,
		0,0,0,	0,9,0,	0,9,1,	0,0,1,
		1,0,0,	1,9,0,	1,9,1,	1,0,1,
		0,0,4,	0,0,5,	0,9,5, 0,9,4,
		1,0,4,	1,0,5,	1,9,5,	1,9,4,

		// steps
		0,1,1,	0,1,4,	0,1.5,4,	0,1.5,1,
		1,1,1,	1,1,4,	1,1.5,4,	1,1.5,1,
		0,1,1,	1,1,1,	1,1,4,	0,1,4,
		0,1.5,1,	1,1.5,1,	1,1.5,4,	0,1.5,4,
		0,1,1,	0,1.5,1,	1,1.5,1,	1,1,1,
		0,1,4,	0,1.5,4,	1,1.5,4,	1,1,4,

		0,3,1,	0,3,4,	0,3.5,4,	0,3.5,1,
		1,3,1,	1,3,4,	1,3.5,4,	1,3.5,1,
		0,3,1,	1,3,1,	1,3,4,	0,3,4,
		0,3.5,1,	1,3.5,1,	1,3.5,4,	0,3.5,4,
		0,3,1,	0,3.5,1,	1,3.5,1,	1,3,1,
		0,3,4,	0,3.5,4,	1,3.5,4,	1,3,4,

		0,5,1,	0,5,4,	0,5.5,4,	0,5.5,1,
		1,5,1,	1,5,4,	1,5.5,4,	1,5.5,1,
		0,5,1,	1,5,1,	1,5,4,	0,5,4,
		0,5.5,1,	1,5.5,1,	1,5.5,4,	0,5.5,4,
		0,5,1,	0,5.5,1,	1,5.5,1,	1,5,1,
		0,5,4,	0,5.5,4,	1,5.5,4,	1,5,4,

		0,7,1,	0,7,4,	0,7.5,4,	0,7.5,1,
		1,7,1,	1,7,4,	1,7.5,4,	1,7.5,1,
		0,7,1,	1,7,1,	1,7,4,	0,7,4,
		0,7.5,1,	1,7.5,1,	1,7.5,4,	0,7.5,4,
		0,7,1,	0,7.5,1,	1,7.5,1,	1,7,1,
		0,7,4,	0,7.5,4,	1,7.5,4,	1,7,4
	};

	GLfloat vertices1[] =
	{	
		4,0,0,	5,0,0,	5,9,0,	4,9,0,
		4,0,4,	5,0,4,	5,9,4,	4,9,4,
		4,0,1,	5,0,1,	5,9,1,	4,9,1,
		4,0,5,	5,0,5,	5,9,5,	4,9,5,
		4,0,0,	4,9,0,	4,9,1,	4,0,1,
		5,0,0,	5,9,0,	5,9,1,	5,0,1,
		4,0,4,	4,0,5,	4,9,5, 4,9,4,
		5,0,4,	5,0,5,	5,9,5,	5,9,4,

		5,8,0,	5,8.5,0,	20,1,0, 20,0,0,
		5,8,0.5, 5,8.5,0.5, 20,1,0.5, 20,0,0.5,
		5,8,4.5, 5,8.5,4.5, 20,1,4.5, 20,0,4.5,
		5,8,5,	5,8.5,5,	20,1,5, 20,0,5,

		5,8.5,0, 5,8.5,5, 20,0,5, 20,0,0,
		5,8.5,0, 5,8.5,0.5, 20,0.5,0, 20,0.5,0.5,

		5,8,4.5, 5,8,5,		20,0,4.5,	20,0,5,
		5,8.5,4.5, 5,8.5,5, 20,0.5,4.5, 20,0.5,5,

		0.8,8,1,  5,8,1,	5,8,4,	0.8,8,4,
		0.8,8.5,1,	5,8.5,1,	5,8.5,4,	0.8,8.5,4,
		0.8,8,1,	0.8,8.5,1,	0.8,8.5,4,	0.8,8,4,
		5,8,1,	5,8.5,1,	5,8.5,4,	5,8,4,

		0.8,8,1,	0.8,8.5,1,	5,8.5,1,	5,8,1,
		0.8,8,4,	0.8,8.5,4,	5,8.5,4,	5,8,4
	};

	GLfloat colors[] =
	{
		//Vertical Rods
		0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,			
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,			
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,			
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,			
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,
        
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,			
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,			
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,			
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,

        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,			
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,			
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,			
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,

        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,			
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,			
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,			
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,

        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,			
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,			
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,			
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3
	};

	GLfloat colors1[]=
	{
		0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,			
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,			
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,			
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,			
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,
        
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,			
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,			
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,

        0.7, 0.7, 0.7,	0.7, 0.7, 0.7,	 0.7, 0.7, 0.7,	 0.7, 0.7, 0.7,			
        0.7, 0.7, 0.7,	0.7, 0.7, 0.7,	 0.7, 0.7, 0.7,	 0.7, 0.7, 0.7,

        0.7, 0.7, 0.7,	0.7, 0.7, 0.7,	 0.7, 0.7, 0.7,	 0.7, 0.7, 0.7,
        0.7, 0.7, 0.7,	0.7, 0.7, 0.7,	 0.7, 0.7, 0.7,	 0.7, 0.7, 0.7,			
        
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,			
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,			
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,

        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,
	};
	glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    //glTranslatef(20,0,20);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glRotatef(-5.0,0,0,1);
    /* Send data : 96 vertices */
    glDrawArrays(GL_QUADS, 0, 128);
    glRotatef(5.0,0,0,1);
    glVertexPointer(3, GL_FLOAT, 0, vertices1);
    glColorPointer(3, GL_FLOAT, 0, colors1);

    /* Send data : 24 vertices */
    glDrawArrays(GL_QUADS, 0, 88);
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    

    /* Cleanup states */
    //glTranslatef(-20,0,-20);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    //alpha += 1;
    //alpha += 1;
}

/**
Method to draw a solid colored cylinder with base centered at origin, and height towards positive z axis.
@param radius: radius of cylinder
@param height: height of cylinder
@param red: red component
@param green: green component
@param blue: blue component
@return void
*/

void drawCylinder(GLfloat radius, GLfloat height, GLfloat red = 0.1, GLfloat green = 0.1, GLfloat blue = 0.1)
{
	glPushMatrix();
	GLUquadric* obj;
	obj= gluNewQuadric();
	gluQuadricNormals(obj, GLU_SMOOTH);
	glColor3f(red,green,blue);
	gluCylinder(obj, radius, radius, height, 10000, 1);
	gluDeleteQuadric(obj);
	glPopMatrix();
}

/**
Method to draw a solid colored disk centered at origin, with inner & outer radius.
@param inner_radius: inner radius of cylinder
@param outer_radius: outer radius of cylinder
@param red: red component
@param green: green component
@param blue: blue component
@return void
*/
void drawDisk(GLfloat inner_radius, GLfloat outer_radius,GLfloat red = 0.3, GLfloat green = 0.3, GLfloat blue = 0.3){
	glPushMatrix();
	GLUquadric* obj;
	obj= gluNewQuadric();
	gluQuadricNormals(obj, GLU_SMOOTH);
	glColor3f(red,green,blue);
	gluDisk(obj, inner_radius, outer_radius, 10000, 1);
	gluDeleteQuadric(obj);
	glPopMatrix();
}


void drawSlide1()
{
	glPushMatrix();
	glRotatef(-7,0,0,1);
	glRotatef(-90,1,0,0);
	drawCylinder(0.25,10,60.0/255,82.0/255,45.0/255);
	glRotatef(90,1,0,0);
	glTranslatef(0,0,4);
	glRotatef(-90,1,0,0);
	drawCylinder(0.25,10,60.0/255,82.0/255,45.0/255);
	glRotatef(90,1,0,0);
	int i,j;
	glTranslatef(0,0,-4);
	for(i=0;i<7;i++)
	{
		glTranslatef(0,1.25,0);
		//glRotatef(-90,1,0,0);
		drawCylinder(0.25,4,0.1,0.1,0.1);
		//glRotatef(90,1,0,0);
	}
	glRotatef(7,0,0,1);

	glTranslatef(0,1.2,0);

	glPushMatrix();
		glScalef(4,0.5,0.5);
		drawUnitCube(60.0/255,82.0/255,45.0/255);
	glPopMatrix();

	glTranslatef(3.5,0,0);
	glRotatef(-90,0,0,1);
	glPushMatrix();
		glScalef(0.5,0.5,0.5);
		drawUnitCube(60.0/255,82.0/255,45.0/255);
	glPopMatrix();
	glRotatef(90,0,0,1);
	glTranslatef(-3.5,0,0);

	glTranslatef(0,0,3.5);

	glPushMatrix();
		glScalef(4,0.5,0.5);
		drawUnitCube(60.0/255,82.0/255,45.0/255);
	glPopMatrix();

	glTranslatef(3.5,0,0);
	glRotatef(-90,0,0,1);
	glPushMatrix();
		glScalef(0.5,0.5,0.5);
		drawUnitCube(60.0/255,82.0/255,45.0/255);
	glPopMatrix();
	glRotatef(90,0,0,1);
	glTranslatef(-3.5,0,0);

	glTranslatef(0,-1.2,-3.5);

	glPushMatrix();
		glScalef(4,0.7,4);
		drawUnitCube(0.1,0.1,0.1);
	glPopMatrix();

	glTranslatef(3.4,-7*1.25,0);
	glPushMatrix();
		glScalef(0.5,7*1.25,0.5);
		drawUnitCube(60.0/255,82.0/255,45.0/255);
	glPopMatrix();

	glTranslatef(0,0,3.5);
	glPushMatrix();
		glScalef(0.5,7*1.25,0.5);
		drawUnitCube(60.0/255,82.0/255,45.0/255);
	glPopMatrix();


	glTranslatef(0.3,7*1.25,0);
	glRotatef(-35,0,0,1);
	glPushMatrix();
		glScalef(15,0.7,0.5);
		drawUnitCube(0.5,0.5,0.5);
	glPopMatrix();

	glTranslatef(0,0,-3.5);
	glPushMatrix();
		glScalef(15,0.7,0.5);
		drawUnitCube(0.5,0.5,0.5);
	glPopMatrix();

	glTranslatef(0,0,0.5);
	glPushMatrix();
		glScalef(15,0.2,3);
		drawUnitCube(0.8666667f,0.2f,0.137255f);
	glPopMatrix();

	glRotatef(35,0,0,1);


	glPopMatrix();
}


/**
Method to draw a Jungle gym
@param void
@return void
*/
void drawJungleGym()
{	
	//14.0/255, 117.0/255, 142.0/255
	//38.0/255, 11.0/255, 3.0/255
	//4.0/255, 51.0/255, 11.0/255
	glPushMatrix();
	
	glPushMatrix(); // fisrt vertical
	glRotatef(-90,1,0,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glPopMatrix();
	
	glPushMatrix(); //fisrt horizontal
	glRotatef(90,0,1,0);
	glTranslatef(0,5,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glPopMatrix();

	glPushMatrix(); // first back connectors
	glTranslatef(0,5,-5);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glPopMatrix();

	glPushMatrix(); // second vertical
	glTranslatef(0,0,-5);
	glRotatef(-90,1,0,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glPopMatrix();

	glPushMatrix(); //second horizontal
	glTranslatef(0,0,-5);
	glRotatef(90,0,1,0);
	glTranslatef(0,5,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glPopMatrix();

	glPushMatrix(); // second back connectors
	glTranslatef(0,0,-5);
	glTranslatef(0,5,-5);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glPopMatrix();

	glPushMatrix(); // third vertical
	glTranslatef(0,0,-10);
	glRotatef(-90,1,0,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glPopMatrix();

	glPushMatrix(); //third horizontal
	glTranslatef(0,0,-10);
	glRotatef(90,0,1,0);
	glTranslatef(0,5,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glPopMatrix();

	glPushMatrix(); // third back connectors
	glTranslatef(0,0,-10);
	glTranslatef(0,5,-5);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glPopMatrix();

	glPushMatrix(); // fourth vertical
	glTranslatef(0,0,-15);
	glRotatef(-90,1,0,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glPopMatrix();

	glPushMatrix(); //fourth horizontal
	glTranslatef(0,0,-15);
	glRotatef(90,0,1,0);
	glTranslatef(0,5,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glPopMatrix();

	// layer - 2
	glPushMatrix();
	glTranslatef(0,5,0);
	glPushMatrix(); // fisrt vertical
	glRotatef(-90,1,0,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glPopMatrix();
	
	glPushMatrix(); //fisrt horizontal
	glRotatef(90,0,1,0);
	glTranslatef(0,5,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glPopMatrix();

	glPushMatrix(); // first back connectors
	glTranslatef(0,5,-5);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glPopMatrix();

	glPushMatrix(); // second vertical
	glTranslatef(0,0,-5);
	glRotatef(-90,1,0,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glPopMatrix();

	glPushMatrix(); //second horizontal
	glTranslatef(0,0,-5);
	glRotatef(90,0,1,0);
	glTranslatef(0,5,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glPopMatrix();

	glPushMatrix(); // second back connectors
	glTranslatef(0,0,-5);
	glTranslatef(0,5,-5);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glPopMatrix();

	glPushMatrix(); // third vertical
	glTranslatef(0,0,-10);
	glRotatef(-90,1,0,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glPopMatrix();

	glPushMatrix(); //third horizontal
	glTranslatef(0,0,-10);
	glRotatef(90,0,1,0);
	glTranslatef(0,5,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glPopMatrix();

	glPushMatrix(); // third back connectors
	glTranslatef(0,0,-10);
	glTranslatef(0,5,-5);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glPopMatrix();

	glPushMatrix(); // fourth vertical
	glTranslatef(0,0,-15);
	glRotatef(-90,1,0,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5,4.0/255, 51.0/255, 11.0/255);
	glPopMatrix();

	glPushMatrix(); //fourth horizontal
	glTranslatef(0,0,-15);
	glRotatef(90,0,1,0);
	glTranslatef(0,5,0);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5,38.0/255, 11.0/255, 3.0/255);
	glPopMatrix();
	
	glPopMatrix();
	glPopMatrix();
}

/**
Method to draw a Monkey bar
@param void
@return void
*/
void drawMonkeyBars()
{

	//237.0/255, 141.0/255, 33.0/255
	glPushMatrix();
	glTranslatef(0,0,10);

	glPushMatrix();
	glRotatef(-90,1,0,0); // front vericals
	drawCylinder(0.5,10);
	glTranslatef(20,0,0);
	drawCylinder(0.5,10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,-3);
	glRotatef(-90,1,0,0); // back vericals
	drawCylinder(0.5,10);
	glTranslatef(20,0,0);
	drawCylinder(0.5,10);
	glPopMatrix();

	glPushMatrix(); // left steps
	glTranslatef(0,2,-3);
	drawCylinder(0.5,3,237.0/255, 141.0/255, 33.0/255);
	glTranslatef(0,2,0);
	drawCylinder(0.5,3,237.0/255, 141.0/255, 33.0/255);
	glTranslatef(0,2,0);
	drawCylinder(0.5,3,237.0/255, 141.0/255, 33.0/255);
	glTranslatef(0,2,0);
	drawCylinder(0.5,3,237.0/255, 141.0/255, 33.0/255);
	glTranslatef(0,2,0);
	drawCylinder(0.5,3,237.0/255, 141.0/255, 33.0/255);
	glPopMatrix();

	glPushMatrix(); // right steps
	glTranslatef(20,2,-3);
	drawCylinder(0.5,3,237.0/255, 141.0/255, 33.0/255);
	glTranslatef(0,2,0);
	drawCylinder(0.5,3,237.0/255, 141.0/255, 33.0/255);
	glTranslatef(0,2,0);
	drawCylinder(0.5,3,237.0/255, 141.0/255, 33.0/255);
	glTranslatef(0,2,0);
	drawCylinder(0.5,3,237.0/255, 141.0/255, 33.0/255);
	glTranslatef(0,2,0);
	drawCylinder(0.5,3,237.0/255, 141.0/255, 33.0/255);
	glPopMatrix();


	glPushMatrix(); //top horizontal Bars
	glTranslatef(0,10,0);
	glRotatef(90,0,1,0);
	drawCylinder(0.5,20);
	glTranslatef(3,0,0);
	drawCylinder(0.5,20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,10,-3);
	glTranslatef(2,0,0);
	drawCylinder(0.5,3,237.0/255, 141.0/255, 33.0/255);
	glTranslatef(2,0,0);
	drawCylinder(0.5,3,237.0/255, 141.0/255, 33.0/255);
	glTranslatef(2,0,0);
	drawCylinder(0.5,3,237.0/255, 141.0/255, 33.0/255);
	glTranslatef(2,0,0);
	drawCylinder(0.5,3,237.0/255, 141.0/255, 33.0/255);
	glTranslatef(2,0,0);
	drawCylinder(0.5,3,237.0/255, 141.0/255, 33.0/255);
	glTranslatef(2,0,0);
	drawCylinder(0.5,3,237.0/255, 141.0/255, 33.0/255);
	glTranslatef(2,0,0);
	drawCylinder(0.5,3,237.0/255, 141.0/255, 33.0/255);
	glTranslatef(2,0,0);
	drawCylinder(0.5,3,237.0/255, 141.0/255, 33.0/255);
	glTranslatef(2,0,0);
	drawCylinder(0.5,3,237.0/255, 141.0/255, 33.0/255);
	

	glPopMatrix();

	glPopMatrix();
}

/**
Method to draw a Merry-go-round
@param void
@return void
*/
void drawMerryGoRound(){
glPushMatrix();
	glPushMatrix();
		
		glRotatef(-90.0,1,0,0);
		drawCylinder(0.75, 0.5, 1.0,0.0,0.0);	// Red Bottom cylinder
		glRotatef(90.0,1,0,0);
		
		glTranslatef(0,0.5,0);
		
		glRotatef(-90.0,1,0,0);
		glColor3f(0.0,0.0,0.0);
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		drawDisk(0.75,4);			// medium violetred
		drawCylinder(4,0.5);
		glRotatef(90.0,1,0,0);
		
		glRotatef(-90.0,1,0,0);
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		drawDisk(0.75,4,199.0/255,21.0/255,133.0/255);			// medium violetred
		drawCylinder(4,0.5, 199.0/255,21.0/255,133.0/255);
		glRotatef(90.0,1,0,0);
		
		glTranslatef(0,0.5,0);
		glRotatef(-90.0,1,0,0);
		drawDisk(0.75,4,199.0/255,21.0/255,133.0/255);			// medium violetred
		glRotatef(90.0,1,0,0);
		
		glRotatef(-90.0,1,0,0);
		drawCylinder(0.75,3,1.0,0.0,0.0);	// Red
		glRotatef(90.0,1,0,0);
		
		glTranslatef(0,0.5,0);
		glRotatef(-90.0,1,0,0);
		drawDisk(0.0,0.75,1.0,0.0,0.0);	// Red
		glRotatef(90.0,1,0,0);
		
		// Draw four rods
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(3.8,1,0);
		glRotatef(-90.0f,1,0,0);
		drawCylinder(0.2,3,1.0,0.0,0.0);	// Red
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(-3.8,1,0);
		glRotatef(-90.0f,1,0,0);
		drawCylinder(0.2,3,1.0,0.0,0.0);	// Red
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(0,1,3.8);
		glRotatef(-90.0f,1,0,0);
		drawCylinder(0.2,3,1.0,0.0,0.0);	// Red
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(0,1,-3.8);
		glRotatef(-90.0f,1,0,0);
		drawCylinder(0.2,3,1.0,0.0,0.0);	// Red
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0,3.6,-3.8);
		drawCylinder(0.2,7.6,1.0,0.0,0.0);	// Red
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(-3.8,3.6,0.0);
		glRotatef(90.0f,0,1,0);
		drawCylinder(0.2,7.6,1.0,0.0,0.0);	// Red
	glPopMatrix();	
glPopMatrix();
}

/**
Method to draw swings
@param void
@return void
*/
void drawSwings()
{
	glPushMatrix();
	//glTranslatef(-10,0,10);
	glRotatef(-90,1,0,0);
	glRotatef(22.62,1,0,0);
	drawCylinder(0.25,13);
	glRotatef(-22.62,1,0,0);
	glRotatef(90,1,0,0);

	glTranslatef(0,0,10);
	glRotatef(-90,1,0,0);
	glRotatef(-22.62,1,0,0);
	drawCylinder(0.25,13);
	glRotatef(+22.62,1,0,0);
	glRotatef(90,1,0,0);
	//glTranslatef(-10,0,0);
	glTranslatef(-20,0,-10);
	glRotatef(-90,1,0,0);
	glRotatef(22.62,1,0,0);
	drawCylinder(0.25,13);
	glRotatef(-22.62,1,0,0);
	glRotatef(90,1,0,0);

	glTranslatef(0,0,10);
	glRotatef(-90,1,0,0);
	glRotatef(-22.62,1,0,0);
	drawCylinder(0.25,13);
	glRotatef(+22.62,1,0,0);
	glRotatef(90,1,0,0);

	//[0.8666666666666667, 0.2, 0.13725490196078433]
	glTranslatef(0,12,-5);
	glRotatef(90,0,1,0);
	drawCylinder(0.25,20,0.8666667f,0.2f,0.137255f);
	glRotatef(-90,0,1,0);
	
	glTranslatef(2,0,0);
	glPopMatrix();
	
	// Draw chains, seat and add movement
glPushMatrix();
glTranslatef(-20,12,5);
static double beta = 25.0;	
static double del_beta = -1.0f;
glRotatef(beta,1,0,0);
	glPushMatrix();

	GLfloat vertices[] = 
	{
		// connections to rod.
		0,-0.25,0.25, 0.5,-0.25,0.25, 0.5,0.25,0.25, 0,0.25,0.25,
		0,-0.25,-0.25, 0.5,-0.25,-0.25, 0.5,0.25,-0.25, 0,0.25,-0.25,
		0,0.25,0.25, 0,0.25,-0.25, 0.5,0.25,-0.25, 0.5,0.25,0.25,
		0,-0.25,0.25, 0,-0.25,-0.25, 0.5,-0.25,-0.25, 0.5,-0.25,0.25
	};
	GLfloat vertices1[] =
	{
		//Swing seat.
		0,0,1.5, 0.25,0,1.5, 0.25,0,-1.5, 0,0,-1.5,
		4.75,0,1.5, 5,0,1.5, 5,0,-1.5, 4.75,0,-1.5,

		0,0,1.5, 0.25,0,1.5, 0.25,-1.75,1.5, 0,-1.75,1.5,
		0,0,-1.5, 0.25,0,-1.5, 0.25,-1.75,-1.5, 0,-1.75,-1.5,
		4.75,0,1.5, 5,0,1.5, 5,-1.75,1.5, 4.75,-1.75,1.5,
		4.75,0,-1.5, 5,0,-1.5, 5,-1.75,-1.5, 4.75,-1.75,-1.5,	

		0,-2,1.5, 0,-1.75,1.5, 5,-1.75,1.5, 5,-2,1.5,
		0,-2,-1.5, 0,-1.75,-1.5, 5,-1.75,-1.5, 5,-2,-1.5,

		0.25,-1.75,1.5, 0.25,0,1.5, 0.25,0,-1.5, 0.25,-1.75,-1.5,
		4.75,-1.75,1.5, 4.75,0,1.5, 4.75,0,-1.5, 4.75,-1.75,-1.5,

		0,-2,1.5, 0,0,1.5, 0,0,-1.5, 0,-2,-1.5,
		5,-2,1.5, 5,0,1.5, 5,0,-1.5, 5,-2,-1.5,

		0.25,-1.75,1.5, 0.25,-1.75,-1.5, 4.75,-1.75,-1.5, 4.75,-1.75,1.5,
		0,-2,1.5, 0,-2,-1.5, 5,-2,-1.5, 5,-2,1.5
	};

	GLfloat colors1[168];
	GLfloat colors2[168];
	GLfloat ctemp[48];
	GLfloat colors[48];
	//0.7734375, 0.609375, 0.11328125
	for(int j=0;j<168;j++)
	{
		if(j<48)
		{
			ctemp[j]=0.0f;
			colors[j]=0.3f;
		}
		if(j%3==0)
		{
			colors1[j]=0.8734375f;
		}
		else if(j%3==1)
		{
			colors1[j]=0.789375f;
		}
		else
		{
			colors1[j]=0.083281f;
		}
		colors2[j]=0.0f;
	}
	//glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glEnable(GL_POLYGON_OFFSET_LINE);
	glPolygonOffset(-1.f,-1.f);
	glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, ctemp);
    glDrawArrays(GL_QUADS, 0, 16);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glTranslatef(5,0,0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, ctemp);
    glDrawArrays(GL_QUADS, 0, 16);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glTranslatef(6,0,0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, ctemp);
    glDrawArrays(GL_QUADS, 0, 16);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glTranslatef(5,0,0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, ctemp);
    glDrawArrays(GL_QUADS, 0, 16);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glTranslatef(-16,0,0);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glDrawArrays(GL_QUADS, 0, 16);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glTranslatef(5,0,0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glDrawArrays(GL_QUADS, 0, 16);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glTranslatef(6,0,0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glDrawArrays(GL_QUADS, 0, 16);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glTranslatef(5,0,0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glDrawArrays(GL_QUADS, 0, 16);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glTranslatef(0.25,0,0);
    double cl = 0.5/4;
    double radius = 0.025;
    double angle = 36.8;
    double al = 0.3*1.0/4;
    double ch = 0.3*1.0/4;
    double bl = 0.4*1.0/4;
    double diff = 0.1/4;
	int i,j;
	for(j=0;j<4;j++)
	{
		glPushMatrix();
	    for(i=0;i<18;i++)
	    {
		    glPushMatrix();
		    glRotatef(180,0,0,1);
		    glRotatef(-90,1,0,0);
		    glRotatef(angle,1,0,0);
		    drawCylinder(radius,cl);
		    glRotatef(-1*angle,1,0,0);
		    glTranslatef(0,al,bl);
		    drawCylinder(radius,ch);
		    glTranslatef(0,0,ch);
		    glRotatef(angle,1,0,0);
		    drawCylinder(radius,cl);
		    glRotatef(-1*angle,1,0,0);
		    glTranslatef(0,-1*al,-1*(bl+ch));
		    glRotatef(90,1,0,0);

		    glRotatef(-90,1,0,0);
		    glRotatef(-1*angle,1,0,0);
		    drawCylinder(radius,cl);
		    glRotatef(angle,1,0,0);
		    glTranslatef(0,-1*al,bl);
		    drawCylinder(radius,ch);
		    glTranslatef(0,0,ch);
		    glRotatef(-1*angle,1,0,0);
		    drawCylinder(radius,cl);
		    glRotatef(angle,1,0,0);
		    glTranslatef(0,al,-1*(bl+ch));
		    glRotatef(90,1,0,0);
		    glRotatef(180,0,0,1);
			glPopMatrix();

			glTranslatef(0,-1*(bl+ch+bl-1*diff),0);
			glPushMatrix();
			glRotatef(90,0,1,0);
			glRotatef(180,0,0,1);
		    glRotatef(-90,1,0,0);
		    glRotatef(angle,1,0,0);
		    drawCylinder(radius,cl);
		    glRotatef(-1*angle,1,0,0);
		    glTranslatef(0,al,bl);
		    drawCylinder(radius,ch);
		    glTranslatef(0,0,ch);
		    glRotatef(angle,1,0,0);
		    drawCylinder(radius,cl);
		    glRotatef(-1*angle,1,0,0);
		    glTranslatef(0,-1*al,-1*(bl+ch));
		    glRotatef(90,1,0,0);

		    glRotatef(-90,1,0,0);
		    glRotatef(-1*angle,1,0,0);
		    drawCylinder(radius,cl);
		    glRotatef(angle,1,0,0);
		    glTranslatef(0,-1*al,bl);
		    drawCylinder(radius,ch);
		    glTranslatef(0,0,ch);
		    glRotatef(-1*angle,1,0,0);
		    drawCylinder(radius,cl);
		    glRotatef(angle,1,0,0);
		    glTranslatef(0,al,-1*(bl+ch));
		    glRotatef(90,1,0,0);
		    glRotatef(180,0,0,1);
			glRotatef(-90,0,1,0);
			glPopMatrix();
			glTranslatef(0,-1*(bl+ch+bl-1*diff),0);
		}
		if(j%2!=0)
		{
			glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    		glEnable(GL_POLYGON_OFFSET_LINE);
			glPolygonOffset(-1.f,-1.f);
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);
    		glVertexPointer(3, GL_FLOAT, 0, vertices1);
    		glColorPointer(3, GL_FLOAT, 0, colors2);
    		glDrawArrays(GL_QUADS, 0, 56);
    		glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_COLOR_ARRAY);

			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);
    		glVertexPointer(3, GL_FLOAT, 0, vertices1);
    		glColorPointer(3, GL_FLOAT, 0, colors1);
    		glDrawArrays(GL_QUADS, 0, 56);
    		glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_COLOR_ARRAY);

		}
		glPopMatrix();
		if(j==1)
		{
			glTranslatef(-6,0,0);
		}
		else
		{
			glTranslatef(-5,0,0);
		}
	}
	glPopMatrix();
	if(beta >= 25.0)
	 del_beta = -1.0;
	else if(beta <=-25.0)
	 del_beta = 1.0;
	beta += del_beta;
glPopMatrix();
}

/**
Method to draw a colored solid unit cube with <left,bottom,back> point on origin.
@param red: red component
@param green: green component
@param blue: blue component
@return void
*/
void drawUnitCube(GLfloat red=0.4, GLfloat green=0.4, GLfloat blue=0.4){
	glPushMatrix();
	GLfloat vertices[] =
	{
		0.0,0.0,0.0,	0.0,1.0,0.0,	1.0,1.0,0.0,	1.0,0.0,0.0,	// Back
		0.0,0.0,0.0,	0.0,1.0,0.0,	0.0,1.0,1.0,	0.0,0.0,1.0,	// Left
		1.0,0.0,0.0,	1.0,1.0,0.0,	1.0,1.0,1.0,	1.0,0.0,1.0,	// Right
		0.0,0.0,1.0,	0.0,1.0,1.0,	1.0,1.0,1.0,	1.0,0.0,1.0,	// Front
		0.0,1.0,0.0,	0.0,1.0,1.0,	1.0,1.0,1.0,	1.0,1.0,0.0,	// Top
		0.0,0.01,0.0,	0.0,0.01,1.0,	1.0,0.01,1.0,	1.0,0.01,0.0,	// Bottom
	};
	
	GLfloat colors[72] = {0.0};
		
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
	
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glEnable(GL_POLYGON_OFFSET_LINE);
	glPolygonOffset(-1.f,-1.f);
    glDrawArrays(GL_QUADS, 0, 24);

    /* Cleanup states */
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);

	for(int i=0;i<72;i+=3){
		colors[i]=red;
		colors[i+1]=green;
		colors[i+2]=blue;		
	}
	
	glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
	
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glDrawArrays(GL_QUADS, 0, 24);

    /* Cleanup states */
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
}

/**
Method to draw a colored solid Bench with <left,bottom,back> point on origin.
@param red: red component
@param green: green component
@param blue: blue component
@return void
*/
void drawBench(GLfloat red=0.4, GLfloat green=0.4, GLfloat blue=0.4){
	int i;
	glPushMatrix();
	glTranslatef(-25,0,-45);
	for(i=0;i<8;i++)
	{
		glScalef(0.8,0.8,0.8);
		glPushMatrix();
			glPushMatrix();
				glScalef(0.5,5,0.5);				// Left leg back
				drawUnitCube(red,green,blue);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(10,0,0);				// Right leg back
				glScalef(0.5,5,0.5);
				drawUnitCube(red,green,blue);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(0,0,5);				// Left leg front
				glScalef(0.5,3,0.5);
				drawUnitCube(red,green,blue);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(10,0,5);				// Right leg front
				glScalef(0.5,3,0.5);
				drawUnitCube(red,green,blue);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0,2,0);				// Seat
				glScalef(10,0.5,5);
				drawUnitCube(red,green,blue);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0,3,0);				// left handrest
				glScalef(0.5,0.5,6);
				drawUnitCube(red,green,blue);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(10,3,0);				// Right handrest
				glScalef(0.5,0.5,6);
				drawUnitCube(red,green,blue);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(0,5,0);				// Top bar
				glScalef(10.5,0.5,0.5);
				drawUnitCube(red,green,blue);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(0,3,0);				// back bar
				glScalef(10,0.5,0.5);
				drawUnitCube(red,green,blue);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(0,4,0);				// back bar
				glScalef(10.5,0.5,0.5);
				drawUnitCube(red,green,blue);
			glPopMatrix();
		glPopMatrix();
		glScalef(1.25,1.25,1.25);
		if(i%2!=0)
		{
			glTranslatef(20,0,20);
			glRotatef(-90,0,1,0);
		}
		else
		{
			glTranslatef(50,0,0);
		}
	}
	glPopMatrix();
}


/**
Method to import an .obj file.
@param objfile: obj file name
@param mtlfile: mtl fine name
@return void
*/
void importObjFile(const string& objfile,const string& mtlfile)
{
	ifstream ifil;
	int i,j;
	string line;
	ifil.open(mtlfile.c_str());
	int state=0;
	map<string,Vector3> cmap;
	string mtlname="";
	while(!ifil.eof())
	{
		getline(ifil,line);
		if(line.length()>=2 && line[0]!='#')
		{
			if(state==1)
			{
				if(line.find("Kd")!=string::npos)
				{
					int size = line.length();
					string temp="";
					vector<string> tt;
					for(i=3;i<size;i++)
					{
						if(line[i]==' ')
						{
							tt.push_back(temp);
							temp="";
						}
						else
						{
							temp.push_back(line[i]);
						}
					}
					tt.push_back(temp);
					Vector3 v3;
					v3.x = atof(tt[0].c_str());
					v3.y = atof(tt[1].c_str());
					v3.z = atof(tt[2].c_str());
					//v3.normalize();
					cmap[mtlname]=v3;
					state=0;
				}
			}
			if(line.find("newmtl")!=string::npos)
			{
				mtlname = line.substr(7,line.length());
				state=1;
			}
		}
	}
	ifil.close();
	ifil.open(objfile.c_str());
	vector<Vector3> vlist;
	vector<Face> flist;
	Vector3 lcl;
	lcl.set(0.3,0.3,0.3);
	vset.clear();
	while(!ifil.eof())
	{
		getline(ifil,line);
		//cout<<line<<endl;
		if(line.length()>=2 && line[0]!='#')
		{
			if(line[0]=='o' && line[1]==' ')
			{
				int size = flist.size();
				//cout<<"#####"<<endl;
				for(i=0;i<size;i++)
				{
					TVertex tvx;
					tvx.v1 = vlist[flist[i].p1];
					tvx.v2 = vlist[flist[i].p2];
					tvx.v3 = vlist[flist[i].p3];
					vset.push_back(tvx);
				}
				//cout<<"*****"<<endl;
				//vlist.clear();
				flist.clear();
			}
			else
			{
				if(line[0]=='v' && line[1]==' ')
				{
					int size = line.length();
					string temp = "";
					vector<string> tt;
					for(i=2;i<size;i++)
					{
						if(line[i]==' ')
						{
							tt.push_back(temp);
							temp = "";
						}
						else
						{
							temp.push_back(line[i]);
						}
					}
					tt.push_back(temp);
					//cout<<tt[0]<<" "<<tt[1]<<" "<<tt[2]<<endl;
					Vector3 tv;
					tv.x = atof(tt[0].c_str());
					tv.y = atof(tt[1].c_str());
					tv.z = atof(tt[2].c_str());
					vlist.push_back(tv);
				}
				else if(line[0]=='f' && line[1]==' ')
				{
					cset.push_back(lcl);
					int size = line.length();
					string temp = "";
					vector<string> tt;
					for(i=2;i<size;i++)
					{
						if(line[i]==' ')
						{
							tt.push_back(temp);
							temp = "";
						}
						else
						{
							temp.push_back(line[i]);
						}
					}
					tt.push_back(temp);
					//cout<<tt[0]<<" "<<tt[1]<<" "<<tt[2]<<endl;
					Face face;
					for(i=0;i<3;i++)
					{
						int ss = tt[i].length();
						string temps="";
						for(j=0;j<ss;j++)
						{
							if(tt[i][j]=='/')
							{
								if(i==0)
								{
									face.p1 = atoi(temps.c_str());
								}
								else if(i==1)
								{
									face.p2 = atoi(temps.c_str());
								}
								else
								{
									face.p3 = atoi(temps.c_str());
								}
								break;
							}
							else
							{
								temps.push_back(tt[i][j]);
							}
						}
					}
					flist.push_back(face);
				}
				else if(line.find("usemtl ")!=string::npos)
				{
					string tem_string = line.substr(7,line.length());
					lcl = cmap[tem_string];
					cout<<"Idhar: "<<tem_string<<" "<<lcl.x<<" "<<lcl.y<<" "<<lcl.z<<endl;
				}
			}
		}
	}
	if(flist.size()>0)
	{
		int size = flist.size();
		for(i=0;i<size;i++)
		{
			TVertex tvx;
			tvx.v1 = vlist[flist[i].p1];
			tvx.v2 = vlist[flist[i].p2];
			tvx.v3 = vlist[flist[i].p3];
			vset.push_back(tvx);
		}
		vlist.clear();
	}
	ifil.close();
	
	int size = vset.size()*9;
	varr = new GLfloat[size];
	carr = new GLfloat[size];
	size = vset.size();
	int k=0;
	for(i=0;i<size;i++)
	{
		varr[k]=vset[i].v1.x;
		carr[k++]=cset[i].x;
		varr[k]=vset[i].v1.y;
		carr[k++]=cset[i].y;
		varr[k]=vset[i].v1.z;
		carr[k++]=cset[i].z;

		varr[k]=vset[i].v2.x;
		carr[k++]=cset[i].x;
		varr[k]=vset[i].v2.y;
		carr[k++]=cset[i].y;
		varr[k]=vset[i].v2.z;
		carr[k++]=cset[i].z;

		varr[k]=vset[i].v3.x;
		carr[k++]=cset[i].x;
		varr[k]=vset[i].v3.y;
		carr[k++]=cset[i].y;
		varr[k]=vset[i].v3.z;
		carr[k++]=cset[i].z;
	}
}

void drawObjFile()
{
	int size = vset.size()*3;
	glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, varr);
    glColorPointer(3, GL_FLOAT, 0, carr);
    glDrawArrays(GL_TRIANGLES, 0, size);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

