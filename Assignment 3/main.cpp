/**	\file demo.cpp
Test file containing main function.
*/
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

using namespace std;
const double SCREEN_WIDTH = 1024.0;
const double SCREEN_HEIGHT = 768.0;

class Point2
{
	public:
		double x,y;
		Point2();
		Point2(double x, double y);
		void setCords(double x, double y);
};

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

/**
Mouse Button callback function to handle mouse click.
*/
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
  	
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
	
	// Set Cursor shape to Cross-hair
//	GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
//	glfwSetCursor(window, cursor);

	
	// Set cursor to center initailly
	glfwSetCursorPos(window,SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
    
    return window;
}



void drawPixel(double xPos,double yPos){
	glBegin(GL_POINTS);
		for(int i=0;i<100;i++)
			glVertex3f((unsigned int)xPos,(unsigned int)yPos+i,0);
	glEnd();
}

/**
Method to display the primitives i.e redrawing the screen.
*/
void display( GLFWwindow* window ){

    while(!glfwWindowShouldClose(window)){

		glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

	    //attempt to draw lines
	    glColor3f(1.0,0.0,0.0);
		drawPixel(100,100);

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
