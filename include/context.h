#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#ifndef CONTEXT_H
#define CONTEXT_H
#define ll long long int

// Class for creating window and frame buffer
struct color_t
{
	GLuint r;
	GLuint g;
	GLuint b;
};

class Context
{
	private:
		GLFWwindow* window;
		color_t* buffer;
		int w_height;
		int w_width;

	public:
		Context();
		~Context();
		void initialize();
		void createWindow(int width,int height,char* wname);
		unsigned int getWindowHeight();
		unsigned int getWindowWidth();
		color_t* getFrameBuffer();
		void terminate();
		GLFWwindow* getWindow();
};


#endif