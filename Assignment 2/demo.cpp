#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include "interaction.h"

void controls(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS)
        if(key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, GL_TRUE);
}

GLFWwindow* initWindow(const int resX, const int resY)
{
    if(!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return NULL;
    }
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing

    // Open a window and create its OpenGL context
    GLFWwindow* window = glfwCreateWindow(resX, resY, "TEST", NULL, NULL);

    if(window == NULL)
    {
        fprintf(stderr, "Failed to open GLFW window.\n");
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, controls);
    
    // Set Mouse Button function
    glfwSetMouseButtonCallback( window, mouseButtonCallback );
    glfwSetInputMode( window, GLFW_STICKY_MOUSE_BUTTONS, 1 );
    

    // Get info of GPU and supported OpenGL version
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("OpenGL version supported %s\n", glGetString(GL_VERSION));

    glEnable(GL_DEPTH_TEST); // Depth Testing
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    return window;
}

void drawSeeSaw()
{

	
	// For rectangles
    GLfloat vertices[] =
    {
		-1,0,-1,	0,2,-1,		0,2,1,	-1,0,1,	// Left face of Wedge
		1,0,-1,	0,2,-1,		0,2,1,	1,0,1,		// Right face of Wedge
		-1,0,-1,	-1,0,1,	1,0,1,	1,0,-1,		// Bottom face of Wedge
		// Inclined plane
		-8,0,-1,					8,4,-1,					8,4,1,					-8,0,1,					//  bottom face
		-8.097014,0.124254,-1,		7.902985,4.124253,-1,	7.902986,4.124253,1,	-8.097014,0.124254,1,		//	top face
		-8,0,-1,					8,4,-1,					7.902985,4.124253,-1,   -8.097014, 0.124254,-1,	// rear face
		-8,0,1,						8,4,1,					7.902985,4.124253,1,	-8.097014, 0.124254,1,		// front face
		-8,0,-1,					-8,0,1,					-8.097014,0.124254,1,	-8.097014,0.124254,-1,		// Left face
		8,4,-1,						8,4,1,					7.902985,4.124253,1,	7.902985,4.124253,-1,		// Right face
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
		-50,0,50,	50,0,50,	50,0,-50,	-50,0,-50
		
    };
    
    GLfloat vert_triangles[] = 
    {
    	-1,0,-1,	0,0,-1,	1,0,-1,	// Front face of Wedge
    	-1,0,1,		0,0,1,	1,0,1		// Rear face of Wedge
    };

    GLfloat colors[] =			// Each vertex has a color component
    {
    	// Wedge
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,			
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,
        0.3, 0.3, 0.3,	0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,	 0.3, 0.3, 0.3,
        // Inclined plane
	    0.35, 0.35, 0.35,	0.35, 0.35, 0.35,	0.35, 0.35, 0.35,	0.35, 0.35, 0.35,
	    0.35, 0.35, 0.35,	0.35, 0.35, 0.35,	0.35, 0.35, 0.35,	0.35, 0.35, 0.35,
	    0.35, 0.35, 0.35,	0.35, 0.35, 0.35,	0.35, 0.35, 0.35,	0.35, 0.35, 0.35,
	    0.35, 0.35, 0.35,	0.35, 0.35, 0.35,	0.35, 0.35, 0.35,	0.35, 0.35, 0.35,
	    0.35, 0.35, 0.35,	0.35, 0.35, 0.35,	0.35, 0.35, 0.35,	0.35, 0.35, 0.35,
	    0.35, 0.35, 0.35,	0.35, 0.35, 0.35,	0.35, 0.35, 0.35,	0.35, 0.35, 0.35,
	    // Boundary
	    0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,
	    0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,
	    0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,
	    0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,	    
	    0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,
		// Top of Boundary
	    0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,
	    0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,
	    0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,
	    0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,	    
	    0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,
	    // Inner Boundary
	    0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,
	    0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,
	    0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,
	    0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,	    
	    0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,
	    // Gate faces
	    0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,	    
	    0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,		0.2,0.2,0.2,
	    // Ground Bottom
	    0.486,0.988,0,		0.486,0.988,0,		0.486,0.988,0,		0.486,0.988,0
	    
    };

    static float alpha = 0;
    //attempt to rotate cube
    glRotatef(alpha, 0, 1, 0);			// Comment this line to stop rotation about y axis.

    /* We have a color array and a vertex array */
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);

    /* Send data : 24 vertices */
    glDrawArrays(GL_QUADS, 0, 108);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    

    /* Cleanup states */
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
   alpha += 1;
}

void drawCylinder(GLfloat radius, GLfloat height){
	glPushMatrix();
	GLUquadric* qobj;
	qobj = gluNewQuadric();
//	static float alpha = 0;
//	glTranslatef(, 0, -50);
	glRotatef(-90, 1, 0, 0);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	glColor3f(0.3,0.3,0.3);
	gluCylinder(qobj, radius, radius, height, 10000, 1);
	gluDeleteQuadric(qobj);
	glPopMatrix();
	
}

void display( GLFWwindow* window )
{
    while(!glfwWindowShouldClose(window))
    {
        // Scale to window size
        GLint windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        glViewport(0, 0, windowWidth, windowHeight);

        // Draw stuff
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION_MATRIX);
        glLoadIdentity();
        gluPerspective( 80, (double)windowWidth / (double)windowHeight, 25, 300 );

        glMatrixMode(GL_MODELVIEW_MATRIX);
        glTranslatef(0,-50,-100);

        drawSeeSaw();
		drawCylinder(10,30);

        // Update Screen
        glfwSwapBuffers(window);

        // Check for any input, or window movement
        glfwPollEvents();
    }
}

int main(int argc, char** argv)
{
    GLFWwindow* window = initWindow(1024, 620);
    if( NULL != window )
    {
        display( window );
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
