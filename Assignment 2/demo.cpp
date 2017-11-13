/**	\file demo.cpp
Test file containing main function.
*/
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <iostream>
#include "Scene.h"
#include "Camera.h"
#include "Utility.h"

Camera cam;
int zoom_level= 1.0f;
GLfloat field_of_view = 45.0f;

GLfloat xPrev = SCREEN_WIDTH/2;
GLfloat yPrev  = SCREEN_HEIGHT/2;
GLfloat xNew  = xPrev, yNew = yPrev;
GLfloat YAW = -90.0f, PITCH = 0.0f;
bool static_view = false;
double animation_speed = 1.0f;


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
	//	button : GLFW_MOUSE_BUTTON_LEFT or GLFW_MOUSE_BUTTON_RIGHT
	//	action : GLFW_PRESS or GLFW_RELEASE
	
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && zoom_level<3){
    	if(cam.slide(0,0,-30))		// If camera can slide forward, do it and increase zoom level
			zoom_level++;
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS && zoom_level>0){
    	if(cam.slide(0,0,30))		// If camera can slide backward, do it and decrease zoom level
			zoom_level--;
    }
}


void cursor_position_callback(GLFWwindow* window, double xPos, double yPos){

	if (!static_view){
		YAW = (xPrev-xPos)/20.0f;
		PITCH = (yPrev-yPos)/20.0f;
	
		if(PITCH > 89.0f)
			PITCH = 89.0f;
		else if (PITCH < -89.0f)
			PITCH = -89.0f;
		cam.yaw(-YAW);
		cam.pitch(-PITCH);
		xPrev = xPos;
		yPrev = yPos;
	}
}

/*
void cursor_enter_callback(GLFWwindow* window, int entered){
	glfwSetCursorPos(window,SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
}
*/

void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(action == GLFW_RELEASE)
		return;
    if(key == GLFW_KEY_ESCAPE){
		glfwSetWindowShouldClose(window, GL_TRUE);
		return;
	}
	else if(key == GLFW_KEY_L){
		static_view = !(static_view);
		return;
	}
//	std::cout << GLFW_MOD_SHIFT <<"\n";
	
	if(mods == GLFW_MOD_SHIFT){
		switch(key){
			case GLFW_KEY_Y:		cam.yaw(-1.0); break;
			case GLFW_KEY_P:		cam.pitch(-1.0); break;
			case GLFW_KEY_R:		cam.roll(-1.0); break;
			case GLFW_KEY_MINUS:	animation_speed = max(animation_speed-2,1.0); break;
			case GLFW_KEY_EQUAL:	animation_speed = min(animation_speed+2,9.0); break;
			default:			return;
		}
	}
	else{
		switch(key){
			case GLFW_KEY_Y:	cam.yaw(1.0); break;
			case GLFW_KEY_P:	cam.pitch(1.0); break;
			case GLFW_KEY_R:	cam.roll(1.0); break;
			
			case GLFW_KEY_W:    
			case GLFW_KEY_UP:		cam.slide(0,0,-2); break;	// Move Backward
		
			case GLFW_KEY_S:    
			case GLFW_KEY_DOWN:		cam.slide(0,0,2); break;	// Move Forward
		
			case GLFW_KEY_A:   
			case GLFW_KEY_LEFT:		cam.slide(-1,0,0); break;	// Move Left

			case GLFW_KEY_D:      
			case GLFW_KEY_RIGHT:      	cam.slide(1,0,0); break;	// Move Right

			case GLFW_KEY_Q:    	cam.slide(0,1,0); break;	// Move Up	
			case GLFW_KEY_Z:    	cam.slide(0,-1,0); break;			// Move Down
			default: return;

		}
		return;
	}

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
    GLFWwindow* window = glfwCreateWindow(resX, resY, "Childeren's Park", glfwGetPrimaryMonitor(), NULL);

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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
    // Get info of GPU and supported OpenGL version
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("OpenGL version supported %s\n", glGetString(GL_VERSION));

    glEnable(GL_DEPTH_TEST); // Depth Testing
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    return window;
}


void display( GLFWwindow* window )
{
	static GLfloat merry_alpha = 0.0f;
    while(!glfwWindowShouldClose(window))
    {
        // Scale to window size
        GLint windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        glViewport(0, 0, windowWidth, windowHeight);

        // Draw stuff
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

/*		glMatrixMode(GL_PROJECTION_MATRIX);
        glLoadIdentity();
        gluPerspective( 45.0f, (double)windowWidth / (double)windowHeight, 0.1, 3000 );

        glMatrixMode(GL_MODELVIEW_MATRIX);
*/
    glPushMatrix();
		drawBoundary();
		
		glPushMatrix();
			glTranslatef(-40,0,-40);			// Monkey bar
	        drawMonkeyBars();
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(-40,0,-10);			// Slide
	        drawSlide();
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(10,0,-25);				// Jungle Gym
	        drawJungleGym();
		glPopMatrix();
		
		
		glPushMatrix();
			glTranslatef(10,0,10);
			merry_alpha += animation_speed;		// Merry-go-round
			glRotatef(merry_alpha,0,1,0);
			drawMerryGoRound();
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(15,0,-15);
			drawSeeSaw();						// See-saw 1
			glTranslatef(17,0,0);
			drawSeeSaw();						// See-saw 2
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(0,0,0);
			drawBench(160.0/255,82.0/255,45.0/255);
		glPopMatrix();

//	    drawSwings();

		

    glPopMatrix();
        // Update Screen
        glfwSwapBuffers(window);

        // Check for any input, or window movement
        glfwPollEvents();
    }
}

int main(int argc, char** argv)
{
    GLFWwindow* window = initWindow(1024, 620);
	cam.set(Point3(0,5,0),Point3(0,5,-20),Vector3(0,1,0));
	cam.setShape(80.0f, SCREEN_WIDTH/SCREEN_HEIGHT, 0.01, 1000.0);
    
    if( NULL != window )
    {
        display( window );
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
