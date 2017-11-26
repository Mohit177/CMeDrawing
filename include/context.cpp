#include "context.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#define ll long long int
// defining functions of Context class


//Initializing object with default constructor
Context::Context()
{
	window = NULL;
	w_width=0;
	w_height=0;
}


// To initialize glfw
void Context::initialize()
{
	if(!glfwInit())
	{
		std::cerr<<"Failed to initialize"<<std::endl;
		exit(-1);
	}
}

// Creating window and frame buffer of required dimensions
void Context::createWindow(int width,int height,char *wname)
{
	window = glfwCreateWindow(width,height,wname,NULL,NULL);
	glfwMakeContextCurrent(window);
	glClear(GL_COLOR_BUFFER_BIT);
	int i,j,k;
	w_width = width;
	w_height = height;
	if(window==NULL)
	{
		terminate();
		std::cout<<"Eorrrorororo"<<std::endl;
		exit(-1);
	}
}

// returns reference to window object
GLFWwindow* Context::getWindow()
{
	return window;
}

// returns window dimensions
unsigned int Context::getWindowHeight()
{
	return w_height;
}

unsigned int Context::getWindowWidth()
{
	return w_width;
}

//To close the window
void Context::terminate()
{
	glfwTerminate();
}