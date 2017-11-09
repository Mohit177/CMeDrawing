#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <iostream>
        #include <chrono>
		#include <thread>
#include "Scene.h"
#include "Camera.h"
#include "Utility.h"

Camera cam;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
	/*
		button : GLFW_MOUSE_BUTTON_LEFT or GLFW_MOUSE_BUTTON_RIGHT
		action : GLFW_PRESS or GLFW_RELEASE
	*/
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
    	cam.slide(0,0,50);		// slide camera forward to zoom in
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
    	cam.slide(0,0,-50);		// slide camera backward to zoom out
    }
}


void cursor_position_callback(GLFWwindow* window, double xpos, double ypos){
	std::cout << xpos <<" "<<ypos << "\n";
}

void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(action == GLFW_RELEASE)
		return;
    if(key == GLFW_KEY_ESCAPE){
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
    switch(key){
		case GLFW_KEY_W:    cam.slide(0,0,-2); break; // slide camera forward
		case GLFW_KEY_S:    cam.slide(0,0,2); break; // slide camera backward

		case GLFW_KEY_A:      cam.yaw(-1.0); break;		// See left
		case GLFW_KEY_D:      cam.yaw(1.0); break;		// See left
		case GLFW_KEY_Z:    cam.pitch(-1.0); break;
		case GLFW_KEY_Q:    cam.pitch(1.0); break;


		// add roll controls
/*		case 'r':      cam.roll(1.0); break;
		case 'R': cam.roll(-1.0); break;
		case '!': d[0]-=100; break;
		case '1': d[0]+=100; break;
		case '@': d[1]-=100; break;
		case '2': d[1]+=100; break;
		case '#': d[2]-=100; break;
		case '3': d[2]+=100; break;
		case '$': d[3]-=100; break;
		case '4': d[3]+=100; break;
		case 'b': bl+=0.1; break;
		case 'B': if(bl>0.1) bl-=0.1; break;
*/
		default: return;
	}
	//glutPostRedisplay();
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
    GLFWwindow* window = glfwCreateWindow(resX, resY, "Childeren's Park", NULL, NULL);

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
    

    // Get info of GPU and supported OpenGL version
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("OpenGL version supported %s\n", glGetString(GL_VERSION));

    glEnable(GL_DEPTH_TEST); // Depth Testing
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
	glMatrixMode(GL_PROJECTION_MATRIX);
	glLoadIdentity();
	gluPerspective( 45.0f, SCREEN_WIDTH/SCREEN_HEIGHT, 25, 300 );

	glMatrixMode(GL_MODELVIEW_MATRIX);

	glTranslatef(0,-25,-100);
    return window;
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

/*        glMatrixMode(GL_PROJECTION_MATRIX);
        glLoadIdentity();
        gluPerspective( FOV, (double)windowWidth / (double)windowHeight, 25, 300 );

        glMatrixMode(GL_MODELVIEW_MATRIX);

        
*/
		glPushMatrix();
		
		glTranslatef(0,0,-200);
		drawBoundary();
        drawSeeSaw();
        drawJungleGym();
        drawMonkeyBars();
        drawSlide();

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
	cam.set(Point3(0,0,-5),Point3(0,0,-20),Vector3(0,1,0));
	cam.setShape(80.0f, SCREEN_WIDTH/SCREEN_HEIGHT, 100.0, 1000.0);
    
    if( NULL != window )
    {
        display( window );
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
