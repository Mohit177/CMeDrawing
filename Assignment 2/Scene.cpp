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
	GLfloat colors[sizeof(vertices)/sizeof(vertices[0])];
	
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
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);

    /* Send data : 24 vertices */
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

    GLfloat colors[] =			// Each vertex has a color component
    {
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

/*	static float alpha = 0;
    //attempt to rotate cube
    glRotatef(alpha, 1, 1, 1);			// Comment this line to stop rotation about y axis.
*/

    /* Enable color array and a vertex array */
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);

    /* Draw rectangles, 32 vertices */
    glDrawArrays(GL_QUADS, 0, 32);
    
    /* Draw Triangles, 6 vertices */
    glVertexPointer(3, GL_FLOAT, 0, vert_triangles);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    

    /* Cleanup states */
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

// alpha += 1;
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
		0.7,10,0, 0.7,10,5,	5,10,5,	5,10,0,
		0.7,9,0, 0.7,9,5,	5,9,5,	5,9,0,
		0.7,9,0, 0.7,10,0,	5,10,0,	5,9,0,
		0.7,9,5, 0.7,10,5,	5,10,5, 5,9,5,
		
		// Slide 
		5,9,0,	5,10,0,	20,0,0, 20,0,0,
		5,9,0.5, 5,10,0.5, 20,0,0.5, 20,0,0.5,
		5,9,4.5, 5,10,4.5, 
		5,9,5,	5,10,5,	20,0,5, 20,0,5
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
	};

	GLfloat colors1[] = 
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
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3
	};
	glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glTranslatef(10,0,10);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glRotatef(-5.0,0,0,1);
    /* Send data : 96 vertices */
    glDrawArrays(GL_QUADS, 0, 96);
    glRotatef(5.0,0,0,1);
    glVertexPointer(3, GL_FLOAT, 0, vertices1);
    glColorPointer(3, GL_FLOAT, 0, colors);

    /* Send data : 24 vertices */
    glDrawArrays(GL_QUADS, 0, 64);
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    

    /* Cleanup states */
    glTranslatef(-20,0,-20);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    //alpha += 1;
}


void drawCylinder(GLfloat radius, GLfloat height)
{
	glPushMatrix();
	GLUquadric* obj;
	obj= gluNewQuadric();
	gluQuadricNormals(obj, GLU_SMOOTH);
	glColor3f(0.3,0.3,0.3);
	gluCylinder(obj, radius, radius, height, 10000, 1);
	gluDeleteQuadric(obj);
	glPopMatrix();

}

void drawJungleGym()
{	
	glPushMatrix();
	glTranslatef(0,0,-15);
	
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

