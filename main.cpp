#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
#include <cstdlib>
#include "include/primitives.cpp"
#define ll long long int
#define uint unsigned int
using namespace std;
unsigned int prod=256*256*256;
int main()
{
	Context context;
	context.initialize();
	char name[]="My window";
	context.createWindow(600,600,name);
	
	color_t* buffer = context.getFrameBuffer();
	glDrawPixels(context.getWindowWidth(),context.getWindowHeight(),GL_RGB,GL_UNSIGNED_INT,buffer);
	Primitive p = Primitive(&context);
	point<uint> p1,p2;
	cin>>p1.x>>p1.y>>p2.x>>p2.y;

	color_t c;
	c.r = 255*prod;
	c.g = 255*prod;
	c.b = 0;
	p.drawPixel(p1,c);
	p.drawPixel(p2,c);
	p.drawLine(p1,p2,c);
	glfwSwapBuffers(context.getWindow());
	glfwPollEvents();
	while(!glfwWindowShouldClose(context.getWindow()))
	{
		glDrawPixels(context.getWindowWidth(),context.getWindowHeight(),GL_RGB,GL_UNSIGNED_INT,buffer);
		glfwSwapBuffers(context.getWindow());
		glfwPollEvents();
	}
	context.terminate();
	return 0;
}