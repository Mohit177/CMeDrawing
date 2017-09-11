#include "context.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#define ll long long int

// defining functions of Context class


Context::Context()
{
	window = NULL;
}


// To initialize glfw
void Context::initialize()
{
	if(!glfwInit())
	{
		std::cerr<<"Failed to initialize"<<std::endl;
		exit(-1);
	}
	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

// Creating window of required dimensions
void Context::createWindow(int width,int height,char *wname)
{
	window = glfwCreateWindow(width,height,wname,NULL,NULL);
	if(!window)
	{
		terminate();
		exit(-1);
	}
}

// returns reference to window object
GLFWwindow* Context::getWindow()
{
	return window;
}

void Context::terminate()
{
	glfwTerminate();
}

