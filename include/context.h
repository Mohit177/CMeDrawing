#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#ifndef CONTEXT_H
#define CONTEXT_H
#define ll long long int

// Class for creating window and frame buffer

/*Data Structure to represent color in RGB values*/
//Color must be of the form value(0,255)*256*256*256 with GLuint type, which is unsigned int
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
		color_t* buffer; //The buffer that will be updated by drawing operations and flushed to the window
		int w_height; //width of context
		int w_width; //height of context

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