#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <climits>
#include <cstdlib>
#include <stack>
#include <unistd.h>
#include <ctime>
#include "../include/lsystem.cpp"

using namespace std;
unsigned int prod = 255*255*255;
class Point2
{
	public:
		double x,y;
		Point2();
		Point2(double x, double y);
		void setCords(double x, double y);
};

Point2::Point2()
{
	this->x = 0;
	this->y = 0;
}

Point2::Point2(double x,double y)
{
	this->x = x;
	this->y = y;
}

void Point2::setCords(double x, double y)
{
	this->x = x;
	this->y = y;
}

int main()
{
	Context context; //Creating an OpenGL context
	context.initialize(); // initializing context
	char name[]="My window";
	context.createWindow(1200,700,name); // window of dimension 1200x700 pixels
	Primitive p = Primitive(&context);
	int i;
	double x1 = 50;
	double y1 = 50;
	color_t color;
	color.r = 255*prod;
	color.g = 255*prod;
	color.b=0;
	for(i=0;i<100;i++)
	{
		p.drawPixel(p.makePoint<double>(x1+i,y1+i),color);
	}
	//p.drawPixel(p.makePoint<double>(x1+100,y1+20),color);
	color_t* buffer = context.getFrameBuffer();
	glfwSwapBuffers(context.getWindow());
	glfwPollEvents();
	//while the close button of window not pressed, the window keeps refreshing
	while(!glfwWindowShouldClose(context.getWindow()))
	{
		glDrawPixels(context.getWindowWidth(),context.getWindowHeight(),GL_RGB,GL_UNSIGNED_INT,buffer);
		glfwSwapBuffers(context.getWindow());
		glfwPollEvents();
	}
	context.terminate(); //destroys window
	return 0;
}