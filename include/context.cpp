#include "context.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#define ll long long int
// defining functions of Context class


Context::Context()
{
	window = NULL;
	buffer = NULL;
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
	buffer = new color_t[width*height];
	for(i=0;i<width;i++)
	{
		for(j=0;j<height;j++)
		{
			buffer[j*width+i].r=0;
			buffer[j*width+i].g=0;
			buffer[j*width+i].b=0;
		}
	}
	w_width = width;
	w_height = height;
	if(window==NULL)
	{
		terminate();
		delete buffer;
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
color_t* Context::getFrameBuffer()
{
	return buffer;
}
//To close the window
void Context::terminate()
{
	glfwTerminate();
}

//Destructor to free memory consumed pointed by buffer
Context::~Context()
{
	int i,j;
	delete buffer;
}