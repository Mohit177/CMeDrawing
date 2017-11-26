/**	\file main.cpp
Test file containing main function, callback functions, and de casteljau algorithm.
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

#include "Polymesh.h"

using namespace std;
bool mouse_drag = false;	//!< bool value, true if mouse is being dragged, false otherwise
int drag_index = -1;		//!< Index of control point being dragged 

std::vector<Point2> point_buffer;	//!< Vector of pixels on the curve
std::vector<Point2> control_points;		//!< Vector of control points of the curve.

// function definitions
void drawPixel(double xPos, double yPos, double red, double green, double blue, int pixel_size);
void deCasteljau();
int indexOf_NearestControlPoint(double xPos, double yPos);

/**
Mouse Button callback function to handle mouse click. \n
Left clicking on the scrren adds a control point.	\n
Right clicking on a control point deletes the point.
Left clikcing a control point and dragging it changes its position
*/
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
	double xPos=0.0, yPos = 0.0;
	glfwGetCursorPos(window, &xPos,&yPos);
	
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
    	
		int near_index = indexOf_NearestControlPoint(xPos, yPos);
		if(near_index >=0 && near_index <= control_points.size()){
			mouse_drag = true;
			drag_index = near_index;
    		return;
		}
		
		control_points.push_back(Point2(xPos,yPos));
		return;
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
        
        if(mouse_drag && drag_index>=0 && drag_index < control_points.size()){
        	control_points[drag_index].x = xPos;
        	control_points[drag_index].y = yPos;
	    	mouse_drag = false;
	    	drag_index = -1;
        }
    	return;
    }
    else if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
    
		int near_index = indexOf_NearestControlPoint(xPos, yPos);
		if(near_index >=0 && near_index <= control_points.size()){
			control_points.erase(control_points.begin()+near_index);
		}
		return;
	}
}


/**
Function to find the index of nearest control point to the current cursor position, if the cursor is in its vicinity.
@param xPos : x-coordinate of cursor
@param yPos : y-coordinate of cursor
*/
int indexOf_NearestControlPoint(double xPos, double yPos){
	int ctrl_size = control_points.size();
    int i;
    for(i=0;i<ctrl_size;i++){
    	if(abs(control_points[i].x - xPos)<=3 && abs(control_points[i].y - yPos)<=3)
    	{
    		return i;
    	}
    }
    return -1;
}

/**
Cursor postion callback to handle cursor position update.
It updates the control point being dragged, if any.
*/
void cursor_position_callback(GLFWwindow* window, double xPos, double yPos){
	if(mouse_drag){
		control_points[drag_index].x = xPos;
		control_points[drag_index].y = yPos;
	}
}


/**
Keyboard callback to handle key press events.
<b> Ctrl+Z :</b> Remove the recently added control point. \n
<b> Esc :</b> Close the window. \n
<b> C :</b> Clear the window \n
<b> G :</b> Generate the Polymesh in test.off file

*/
void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if(action == GLFW_RELEASE)
		return;

	if(mods == GLFW_MOD_CONTROL && key == GLFW_KEY_Z && action == GLFW_PRESS){
		control_points.pop_back();
		return;
	}	
	
	switch(key){
	case GLFW_KEY_ESCAPE:	glfwSetWindowShouldClose(window, GL_TRUE); return;
	case GLFW_KEY_C:		control_points.clear(); point_buffer.clear(); return;
	case GLFW_KEY_G:		Polymesh mesh;
							mesh.generateMesh(point_buffer, 144);
							mesh.writeToFile("test.off");
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
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
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
	glfwSetCursorPos(window,SCREEN_WIDTH/2.0,SCREEN_HEIGHT/2.0);
    
    return window;
}

/**
Function to draw a pixel on the screen.
@param xPos: x position of pixel
@param yPos: y position of pixel
@param red : Red component of color (Default value is 1.0)
@param green : green component of color (Default value is 0.0)
@param blue : blue component of color (Default value is 0.0)
@param pixel_size: Size of pixel (Default value is 1)
@return void
*/
void drawPixel(double xPos, double yPos, double red=1.0, double green=0.0,double blue=0.0, int pixel_size=1){
	glPointSize(pixel_size);  
	glColor3f(red, green,blue);
	glBegin(GL_POINTS);
		glVertex2f(xPos,yPos);
	glEnd();	
}

/**
Function to draw the curve (plot pixels from the buffer)
@param : void
@return void
*/
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
	    
	    for(int i=0; i<control_points.size();i++){
	    	if(mouse_drag && drag_index ==i)
		    	drawPixel(control_points[i].x, control_points[i].y, 0.0, 0.0, 1.0, 3);
	    	else
		    	drawPixel(control_points[i].x, control_points[i].y, 1.0, 1.0, 0.0, 2);
	    }
	    

	    glBegin(GL_LINES);
	    glPointSize(1); 
	    glColor3f(1.0,1.0,1.0);
	    glVertex2f(SCREEN_WIDTH/2.0, 0);
	    glVertex2f(SCREEN_WIDTH/2.0, SCREEN_HEIGHT);
	    glEnd();
	    
	    deCasteljau();
		drawCurve();

    	glfwSwapBuffers(window);
	    glfwPollEvents();
    }
}

/**
Function to interpolate between two points, with the given parameter t.
@param p1: First Point
@param p2: Second Point
@param t: Value of parameter t
@return : Interpolated point
*/
Point2 interpolate(const Point2& p1, const Point2& p2, double t){
	Point2 pt;
	pt.x = p1.x*t + p2.x*(1-t);
	pt.y = p1.y*t + p2.y*(1-t);
	return pt;
}

/**
Function to find the points on the curve defined by the control points. 
The value of t varies from 0 to 1, with fixed increments of 0.0001.
@return void
*/
void deCasteljau()
{
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