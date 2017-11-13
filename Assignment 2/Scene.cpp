#include "Scene.h"

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
		colors[i]	= 0.486;
		colors[i+1] = 0.988;
		colors[i+2] = 0;
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


void drawSeeSaw(){

	// For rectangles
    GLfloat vertices[] =
    {
    	// Wedge
		-1,0,-1,	0,2,-1,		0,2,1,	-1,0,1,		// Left face of Wedge
		1,0,-1,		0,2,-1,		0,2,1,	1,0,1,		// Right face of Wedge
		
		// Inclined plane
		-8,0,-1,					8,4,-1,					8,4,1,					-8,0,1,					//  bottom face
		-8.097014,0.124254,-1,		7.902985,4.124253,-1,	7.902986,4.124253,1,	-8.097014,0.124254,1,		//	top face
		-8,0,-1,					8,4,-1,					7.902985,4.124253,-1,   -8.097014, 0.124254,-1,	// rear face
		-8,0,1,						8,4,1,					7.902985,4.124253,1,	-8.097014, 0.124254,1,		// front face
		-8,0,-1,					-8,0,1,					-8.097014,0.124254,1,	-8.097014,0.124254,-1,		// Left face
		8,4,-1,						8,4,1,					7.902985,4.124253,1,	7.902985,4.124253,-1		// Right face
    };
    
    GLfloat vert_triangles[] = 
    {
		-1,0,1,		0,2,1,	1,0,1,			// Front face of Wedge
    	-1,0,-1,	0,2,-1,	1,0,-1		// Rear face of Wedge
    };

    GLfloat colors[96] = {0.0f};			// Each vertex has a color component
   /* {
    	// Wedge
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,			
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,
        // Inclined plane
	    0.35, 0.35, 0.35,	0.35, 0.35, 0.35,	0.35, 0.35, 0.35,	0.35, 0.35, 0.35,
	    0.35, 0.35, 0.35,	0.35, 0.35, 0.35,	0.35, 0.35, 0.35,	0.35, 0.35, 0.35,
	    0.35, 0.35, 0.35,	0.35, 0.35, 0.35,	0.35, 0.35, 0.35,	0.35, 0.35, 0.35,
	    0.35, 0.35, 0.35,	0.35, 0.35, 0.35,	0.35, 0.35, 0.35,	0.35, 0.35, 0.35,
	    0.35, 0.35, 0.35,	0.35, 0.35, 0.35,	0.35, 0.35, 0.35,	0.35, 0.35, 0.35,
	    0.35, 0.35, 0.35,	0.35, 0.35, 0.35,	0.35, 0.35, 0.35,	0.35, 0.35, 0.35
    };
    
    */

/*	static float alpha = 0;
    //attempt to rotate cube
    glRotatef(alpha, 1, 1, 1);			// Comment this line to stop rotation about y axis.
*/

    /* Enable color array and a vertex array */
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    
    // Draw outline
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glEnable(GL_POLYGON_OFFSET_LINE);
	glPolygonOffset(-1.f,-1.f);
    glEnable(GL_DEPTH_TEST);
    glDrawArrays(GL_QUADS, 0, 32);
    
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    
    // Set Red Color
    for(int i=0;i<96;i+=3){
    	colors[i] = 1.0; colors[i+1]=0.0; colors[i+2]=0.0;
    }
    
    // Draw Triangles, 6 vertices
    glVertexPointer(3, GL_FLOAT, 0, vert_triangles);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY); 
	
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
	
	// Set Blue Color for wedge
    for(int i=24;i<96;i+=3){
    	colors[i] = 0.0; colors[i+1]=0.0; colors[i+2]=1.0;
    }
    
    // Draw rectangles, 32 vertices
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glDrawArrays(GL_QUADS, 0, 32);
   
    
    /* Cleanup states */
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void drawSlide(){

	GLfloat vertices[] = 
	{
		// Rods to be slanted.
		// Vertical rods
		0,0,0,	1,0,0,	1,10,0,	0,10,0,
		0,0,4,	1,0,4,	1,10,4,	0,10,4,
		0,0,1,	1,0,1,	1,10,1,	0,10,1,
		0,0,5,	1,0,5,	1,10,5,	0,10,5,
		0,0,0,	0,10,0,	0,10,1,	0,0,1,
		1,0,0,	1,10,0,	1,10,1,	1,0,1,
		0,0,4,	0,0,5,	0,10,5, 0,10,4,
		1,0,4,	1,0,5,	1,10,5,	1,10,4,

		// steps
		0,1,1,	0,1,4,	0,2,4,	0,2,1,
		1,1,1,	1,1,4,	1,2,4,	1,2,1,
		0,1,1,	1,1,1,	1,1,4,	0,1,4,
		0,2,1,	1,2,1,	1,2,4,	0,2,4,

		0,3,1,	0,3,4,	0,4,4,	0,4,1,
		1,3,1,	1,3,4,	1,4,4,	1,4,1,
		0,3,1,	1,3,1,	1,3,4,	0,3,4,
		0,4,1,	1,4,1,	1,4,4,	0,4,4,

		0,5,1,	0,5,4,	0,6,4,	0,6,1,
		1,5,1,	1,5,4,	1,6,4,	1,6,1,
		0,5,1,	1,5,1,	1,5,4,	0,5,4,
		0,6,1,	1,6,1,	1,6,4,	0,6,4,

		0,7,1,	0,7,4,	0,8,4,	0,8,1,
		1,7,1,	1,7,4,	1,8,4,	1,8,1,
		0,7,1,	1,7,1,	1,7,4,	0,7,4,
		0,8,1,	1,8,1,	1,8,4,	0,8,4,

	};

	GLfloat vertices1[] =
	{	
		4,0,0,	5,0,0,	5,10,0,	4,10,0,
		4,0,4,	5,0,4,	5,10,4,	4,10,4,
		4,0,1,	5,0,1,	5,10,1,	4,10,1,
		4,0,5,	5,0,5,	5,10,5,	4,10,5,
		4,0,0,	4,10,0,	4,10,1,	4,0,1,
		5,0,0,	5,10,0,	5,10,1,	5,0,1,
		4,0,4,	4,0,5,	4,10,5, 4,10,4,
		5,0,4,	5,0,5,	5,10,5,	5,10,4,
		//top plank
		//0.7,10,0, 0.7,10,5,	5,10,5,	5,10,0,
		0.7,9,0, 0.7,9,5,	5,9,5,	5,9,0,
		0.7,9,0, 0.7,10,0,	5,10,0,	5,9,0,
		0.7,9,5, 0.7,10,5,	5,10,5, 5,9,5,
		
		// Slide
		// sides
		5,9,0,	5,10,0,	20,1,0, 20,0,0,
		5,9,0.5, 5,10,0.5, 20,1,0.5, 20,0,0.5,
		5,9,4.5, 5,10,4.5, 20,1,4.5, 20,0,4.5,
		5,9,5,	5,10,5,	20,1,5, 20,0,5,

		5,10,0, 5,10,5, 20,0,5, 20,0,0,
		5,10,0, 5,10,0.5, 20,1,0, 20,1,0.5,
		5,10,4.5, 5,10,5, 20,1,4.5, 20,1,5
	};

	GLfloat colors[] =
	{
		//Vertical Rods
		0.01, 0.01, 0.01,	0.01, 0.01, 0.01,	 0.01, 0.01, 0.01,	 0.01, 0.01, 0.01,			
        0.01, 0.01, 0.01,	0.01, 0.01, 0.01,	 0.01, 0.01, 0.01,	 0.01, 0.01, 0.01,
        0.01, 0.01, 0.01,	0.01, 0.01, 0.01,	 0.01, 0.01, 0.01,	 0.01, 0.01, 0.01,			
        0.01, 0.01, 0.01,	0.01, 0.01, 0.01,	 0.01, 0.01, 0.01,	 0.01, 0.01, 0.01,
        0.01, 0.01, 0.01,	0.01, 0.01, 0.01,	 0.01, 0.01, 0.01,	 0.01, 0.01, 0.01,			
        0.01, 0.01, 0.01,	0.01, 0.01, 0.01,	 0.01, 0.01, 0.01,	 0.01, 0.01, 0.01,
        0.01, 0.01, 0.01,	0.01, 0.01, 0.01,	 0.01, 0.01, 0.01,	 0.01, 0.01, 0.01,			
        0.01, 0.01, 0.01,	0.01, 0.01, 0.01,	 0.01, 0.01, 0.01,	 0.01, 0.01, 0.01,
        
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
	};

	GLfloat colors1[76]={0.01};
	glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glTranslatef(20,0,20);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glRotatef(-5.0,0,0,1);
    /* Send data : 96 vertices */
    glDrawArrays(GL_QUADS, 0, 96);
    glRotatef(5.0,0,0,1);
    glVertexPointer(3, GL_FLOAT, 0, vertices1);
    glColorPointer(3, GL_FLOAT, 0, colors);

    /* Send data : 24 vertices */
    glDrawArrays(GL_QUADS, 0, 76);
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    

    /* Cleanup states */
    glTranslatef(-20,0,-20);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    //alpha += 1;
}


void drawCylinder(GLfloat radius, GLfloat height, GLfloat red = 0.3, GLfloat green = 0.3, GLfloat blue = 0.3)
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

void drawJungleGym()
{	
	glPushMatrix();
	
	glPushMatrix(); // fisrt vertical
	glRotatef(-90,1,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glPopMatrix();
	
	glPushMatrix(); //fisrt horizontal
	glRotatef(90,0,1,0);
	glTranslatef(0,5,0);
	drawCylinder(0.5,5);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5);
	glPopMatrix();

	glPushMatrix(); // first back connectors
	glTranslatef(0,5,-5);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glPopMatrix();

	glPushMatrix(); // second vertical
	glTranslatef(0,0,-5);
	glRotatef(-90,1,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glPopMatrix();

	glPushMatrix(); //second horizontal
	glTranslatef(0,0,-5);
	glRotatef(90,0,1,0);
	glTranslatef(0,5,0);
	drawCylinder(0.5,5);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5);
	glPopMatrix();

	glPushMatrix(); // second back connectors
	glTranslatef(0,0,-5);
	glTranslatef(0,5,-5);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glPopMatrix();

	glPushMatrix(); // third vertical
	glTranslatef(0,0,-10);
	glRotatef(-90,1,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glPopMatrix();

	glPushMatrix(); //third horizontal
	glTranslatef(0,0,-10);
	glRotatef(90,0,1,0);
	glTranslatef(0,5,0);
	drawCylinder(0.5,5);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5);
	glPopMatrix();

	glPushMatrix(); // third back connectors
	glTranslatef(0,0,-10);
	glTranslatef(0,5,-5);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glPopMatrix();

	glPushMatrix(); // fourth vertical
	glTranslatef(0,0,-15);
	glRotatef(-90,1,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glPopMatrix();

	glPushMatrix(); //fourth horizontal
	glTranslatef(0,0,-15);
	glRotatef(90,0,1,0);
	glTranslatef(0,5,0);
	drawCylinder(0.5,5);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5);
	glPopMatrix();

	// layer - 2
	glPushMatrix();
	glTranslatef(0,5,0);
	glPushMatrix(); // fisrt vertical
	glRotatef(-90,1,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glPopMatrix();
	
	glPushMatrix(); //fisrt horizontal
	glRotatef(90,0,1,0);
	glTranslatef(0,5,0);
	drawCylinder(0.5,5);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5);
	glPopMatrix();

	glPushMatrix(); // first back connectors
	glTranslatef(0,5,-5);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glPopMatrix();

	glPushMatrix(); // second vertical
	glTranslatef(0,0,-5);
	glRotatef(-90,1,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glPopMatrix();

	glPushMatrix(); //second horizontal
	glTranslatef(0,0,-5);
	glRotatef(90,0,1,0);
	glTranslatef(0,5,0);
	drawCylinder(0.5,5);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5);
	glPopMatrix();

	glPushMatrix(); // second back connectors
	glTranslatef(0,0,-5);
	glTranslatef(0,5,-5);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glPopMatrix();

	glPushMatrix(); // third vertical
	glTranslatef(0,0,-10);
	glRotatef(-90,1,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glPopMatrix();

	glPushMatrix(); //third horizontal
	glTranslatef(0,0,-10);
	glRotatef(90,0,1,0);
	glTranslatef(0,5,0);
	drawCylinder(0.5,5);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5);
	glPopMatrix();

	glPushMatrix(); // third back connectors
	glTranslatef(0,0,-10);
	glTranslatef(0,5,-5);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glPopMatrix();

	glPushMatrix(); // fourth vertical
	glTranslatef(0,0,-15);
	glRotatef(-90,1,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glTranslatef(5,0,0);
	drawCylinder(0.5,5);
	glPopMatrix();

	glPushMatrix(); //fourth horizontal
	glTranslatef(0,0,-15);
	glRotatef(90,0,1,0);
	glTranslatef(0,5,0);
	drawCylinder(0.5,5);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5);
	glTranslatef(0,0,5);
	drawCylinder(0.5,5);
	glPopMatrix();
	
	glPopMatrix();
	glPopMatrix();
}

void drawMonkeyBars()
{
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
	drawCylinder(0.5,3);
	glTranslatef(0,2,0);
	drawCylinder(0.5,3);
	glTranslatef(0,2,0);
	drawCylinder(0.5,3);
	glTranslatef(0,2,0);
	drawCylinder(0.5,3);
	glTranslatef(0,2,0);
	drawCylinder(0.5,3);
	glPopMatrix();

	glPushMatrix(); // right steps
	glTranslatef(20,2,-3);
	drawCylinder(0.5,3);
	glTranslatef(0,2,0);
	drawCylinder(0.5,3);
	glTranslatef(0,2,0);
	drawCylinder(0.5,3);
	glTranslatef(0,2,0);
	drawCylinder(0.5,3);
	glTranslatef(0,2,0);
	drawCylinder(0.5,3);
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
	drawCylinder(0.5,3);
	glTranslatef(2,0,0);
	drawCylinder(0.5,3);
	glTranslatef(2,0,0);
	drawCylinder(0.5,3);
	glTranslatef(2,0,0);
	drawCylinder(0.5,3);
	glTranslatef(2,0,0);
	drawCylinder(0.5,3);
	glTranslatef(2,0,0);
	drawCylinder(0.5,3);
	glTranslatef(2,0,0);
	drawCylinder(0.5,3);
	glTranslatef(2,0,0);
	drawCylinder(0.5,3);
	glTranslatef(2,0,0);
	drawCylinder(0.5,3);
	

	glPopMatrix();

	glPopMatrix();
}


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


void drawSwings()
{
	glPushMatrix();
	glTranslatef(-10,0,10);
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

	glTranslatef(0,12,-5);
	glRotatef(90,0,1,0);
	drawCylinder(0.25,20);
	glRotatef(-90,0,1,0);
	
	glTranslatef(2,0,0);
	
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

	GLfloat colors1[56] = {0.3};

	GLfloat colors[16]={0.3};
	glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glDrawArrays(GL_QUADS, 0, 16);

    glTranslatef(5,0,0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glDrawArrays(GL_QUADS, 0, 16);

    glTranslatef(6,0,0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glDrawArrays(GL_QUADS, 0, 16);

    glTranslatef(5,0,0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glDrawArrays(GL_QUADS, 0, 16);

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
			glEnableClientState(GL_VERTEX_ARRAY);
    		glVertexPointer(3, GL_FLOAT, 0, vertices1);
    		glColorPointer(3, GL_FLOAT, 0, colors1);
    		glDrawArrays(GL_QUADS, 0, 56);
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
}

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

void drawBench(GLfloat red=0.4, GLfloat green=0.4, GLfloat blue=0.4){
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
}
