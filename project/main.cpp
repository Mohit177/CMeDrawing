/**	\file main.cpp
Test file containing main function
*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

#include "const.h"
#include "callbacks.cpp"
using namespace std;

const int SCREEN_WIDTH = 1300;
const int SCREEN_HEIGHT = 768;

// function definitions
GLFWwindow* initWindow(const int resX, const int resY);

/**
Keyboard callback to handle key press events.
*/
void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if(action == GLFW_RELEASE)
		return;
}

/**
Method to initialize glfw window.
*/
GLFWwindow* initWindow(const int resX, const int resY){
    if(!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return NULL;
    }

    GLFWwindow* window = glfwCreateWindow(resX, resY, "Marching Cube", NULL, NULL);		// glfwGetPrimaryMonitor()

    if(window == NULL)
    {
        fprintf(stderr, "Failed to open GLFW window.\n");
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);
 
    
    // Keyboard settings
    glfwSetKeyCallback(window, keyboard_callback);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(DEFAULT_LINE_WIDTH);
	glPointSize(DEFAULT_POINT_SIZE);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

/*    // Set Mouse Button function
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetInputMode( window, GLFW_STICKY_MOUSE_BUTTONS, 1 );
*/	
	// Set Cursor position function
//	glfwSetCursorPosCallback(window, cursor_position_callback);
    return window;
}


/**
Method to display the primitives i.e redrawing the screen.
*/
void display( GLFWwindow* window ){

    while(!glfwWindowShouldClose(window)){
		int width=0, height=0;
		glfwGetWindowSize(window, &width, &height);
		glViewport(0, 0, width, height);
		
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
	   
        show(inpfile_s, dim_x, dim_y, dim_z);

    	glfwSwapBuffers(window);
	    glfwPollEvents();
    }
}
	
/**
Main function to run the program.
*/
int main(int argc, char** argv){

    GLFWwindow* window = initWindow(SCREEN_WIDTH, SCREEN_HEIGHT);

    if( window != NULL )
    {
        display( window );
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}