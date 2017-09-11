#include <GLFW/glfw3.h>
#include <cmath>
#ifndef CONTEXT_H
#define CONTEXT_H
#define ll long long int

class Context
{
	private:
		GLFWwindow* window;

	public:
		Context();
		void initialize();
		void createWindow(int width,int height,char* wname);
		void terminate();
		GLFWwindow* getWindow();
};


#endif