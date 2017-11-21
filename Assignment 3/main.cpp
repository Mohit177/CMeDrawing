/**	\file main.cpp
Test file containing main function.
*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <climits>
#include <cstdlib>
#include <stack>
#include <unistd.h>
#include <ctime>

#include "Point2.h"

using namespace std;
const double SCREEN_WIDTH = 1024.0;
const double SCREEN_HEIGHT = 768.0;

std::vector<Point2> point_buffer;
std::vector<Point2> control_points;

// function definitions
void drawPixel(double xPos, double yPos, double red, double green, double blue);


/**
Mouse Button callback function to handle mouse click.
*/
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
		double xPos=0.0, yPos = 0.0;
		glfwGetCursorPos(window, &xPos,&yPos);
		control_points.push_back(Point2(xPos,yPos));
		std::cout << xPos <<" "<< yPos <<"\n";
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
        
    }
}

/**
Cursor postion callback to handle cursor position update.
*/
void cursor_position_callback(GLFWwindow* window, double xPos, double yPos){

}


/**
Keyboard callback to handle key press events.
*/
void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if(key == GLFW_KEY_ESCAPE){
		glfwSetWindowShouldClose(window, GL_TRUE);
		return;
	}
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

    // Open a window and create its OpenGL context
    GLFWwindow* window = glfwCreateWindow(resX, resY, "Bezier curve", NULL, NULL); // glfwGetPrimaryMonitor()

    if(window == NULL)
    {
        fprintf(stderr, "Failed to open GLFW window.\n");
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);
    
    // Keyboard settings
    glfwSetKeyCallback(window, keyboard_callback);
    
    // Set Mouse Button function
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetInputMode( window, GLFW_STICKY_MOUSE_BUTTONS, 1 );
	
	// Set Cursor position function
	glfwSetCursorPosCallback(window, cursor_position_callback);
	
	// Set cursor to center initailly
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	glfwSetCursorPos(window,width/2,height/2);
    
    return window;
}

void drawPixel(double xPos, double yPos, double red=1.0, double green=0.0,double blue=0.0){
	glColor3f(red, green,blue);
	glBegin(GL_POINTS);
		glVertex2f(xPos,yPos);
	glEnd();	
}


void drawCurve(){
	for(int i=0;i<point_buffer.size();i++){
		drawPixel(point_buffer[i].x, point_buffer[i].y);
	}
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

	    //attempt to draw lines
	    for(Point2 point: control_points ){
	    	drawPixel(point.x , point.y);
	    }
	    
		drawCurve();

    	glfwSwapBuffers(window);
	    glfwPollEvents();
    }
}

	
/**
Main function
*/
int main(int argc, char** argv){
    GLFWwindow* window = initWindow(1024, 620);

    if( window != NULL )
    {
        display( window );
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
