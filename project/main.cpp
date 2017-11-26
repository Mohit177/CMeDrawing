#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "context.cpp"
#define ll long long int

using namespace std;

int main()
{
	Context context; //Creating an OpenGL context
	context.initialize(); // initializing context
	char name[]="My window";
	context.createWindow(1200,700,name);
	glfwSwapBuffers(context.getWindow());
	glfwPollEvents();
	//while the close button of window not pressed, the window keeps refreshing
	while(!glfwWindowShouldClose(context.getWindow()))
	{
		//glDrawPixels(context.getWindowWidth(),context.getWindowHeight(),GL_RGB,GL_UNSIGNED_INT,buffer);
		glfwSwapBuffers(context.getWindow());
		glfwPollEvents();
	}
	context.terminate(); //destroys window
	return 0;
}