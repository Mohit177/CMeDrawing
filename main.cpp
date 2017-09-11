#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
#include <GLFW/glfw3.h>
#include "include/context.cpp"
#define ll long long int

int main()
{
	Context context;
	context.initialize();
	context.createWindow(640,480,"My window");
	glfwMakeContextCurrent(context.getWindow());
	while(!glfwWindowShouldClose(context.getWindow()))
	{
		glfwSwapBuffers(context.getWindow());
		glfwPollEvents();
	}
	context.terminate();
	return 0;
}