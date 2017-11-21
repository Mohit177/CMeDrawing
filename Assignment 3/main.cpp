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
const int SCREEN_WIDTH = 1301.0;
const int SCREEN_HEIGHT = 744.0;

std::vector<Point2> point_buffer;
std::vector<Point2> control_points;

// function definitions
void drawPixel(double xPos, double yPos, double red, double green, double blue);
void deCasteljau(double t);

/**
Mouse Button callback function to handle mouse click.
*/
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
		double xPos=0.0, yPos = 0.0;
		glfwGetCursorPos(window, &xPos,&yPos);
		
		int width=0, height=0;
		glfwGetWindowSize(window, &width, &height);
		std::cout << width <<" "<<height <<"\n";
		
		xPos = (xPos*SCREEN_WIDTH)/width;
		yPos = (yPos*SCREEN_HEIGHT)/height;
		
		control_points.push_back(Point2(xPos,yPos));
		std::cout <<"Mouse click: "<< xPos <<" "<< yPos <<"\n";
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
        
    }
}

/**
Cursor postion callback to handle cursor position update.
*/
void cursor_position_callback(GLFWwindow* window, double xPos, double yPos){
//	std::cout << xPos << " "<< yPos <<"\n";
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
//    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
//  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(resX, resY, "Bezier curve", NULL, NULL); // glfwGetPrimaryMonitor()

    if(window == NULL)
    {
        fprintf(stderr, "Failed to open GLFW window.\n");
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);
    glfwWindowHint(GLFW_RESIZABLE, false);
    
    // Keyboard settings
    glfwSetKeyCallback(window, keyboard_callback);
    
    // Set Mouse Button function
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetInputMode( window, GLFW_STICKY_MOUSE_BUTTONS, 1 );
	
	// Set Cursor position function
	glfwSetCursorPosCallback(window, cursor_position_callback);
	
	// Set window position
	glfwSetWindowPos(window, 0, 0);
	
	// Set cursor to center initailly
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	glfwSetCursorPos(window,width/2,height/2);
    
    return window;
}

void drawPixel(double xPos, double yPos, double red=1.0, double green=0.0,double blue=0.0, int pixel_size=1){
	glPointSize(pixel_size);  
	glColor3f(red, green,blue);
	glBegin(GL_POINTS);
		glVertex2f(xPos,yPos);
	glEnd();	
}


void drawCurve(){
	for(const Point2& point: point_buffer){
		drawPixel(point.x, point.y);
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
	    
	    for(const Point2& p: control_points){
	    	drawPixel(p.x, p.y, 1.0, 1.0, 0.0,2);
	    }
	    
	    deCasteljau((double)0.5);
		drawCurve();

    	glfwSwapBuffers(window);
	    glfwPollEvents();
    }
}

Point2 interpolate(const Point2& p1, const Point2& p2, double t){
	Point2 pt;
	pt.x = p1.x*t + p2.x*(1-t);
	pt.y = p1.y*t + p2.y*(1-t);
	return pt;
}

void deCasteljau(double t){
	point_buffer.clear();
	for(double t= (double)0.0; t<= (double)1.0; t += 0.0001){
	
		int size = control_points.size();
		if(size==0){
			return;	
		}
		if(size==1){
			point_buffer.push_back(control_points[0]);
			return;
		}
	
		std::vector<Point2> temp_points = control_points;
		std::vector<Point2> next_generation;
	
		while(temp_points.size()>1){
			next_generation.clear();
			for(int i=0;i<temp_points.size()-1;i++){
				Point2 intermediate = interpolate(temp_points[i], temp_points[i+1],t);
				next_generation.emplace_back(intermediate);
			}
			temp_points = next_generation;
		}
		point_buffer.push_back(temp_points[0]);
	}
}

	
/**
Main function
*/
int main(int argc, char** argv){

int a,b,c;
glfwGetVersion(&a,&b,&c);
std:: cout << a <<" " << b <<" "<<c;
    GLFWwindow* window = initWindow(1024, 620);

    if( window != NULL )
    {
        display( window );
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
