#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "context.cpp"
#include <map>
#include <string>
#ifndef PRIMITIVES_H
#define PRIMITIVES_H
#define ll long long int

template<typename T>
struct point
{
	T x;
	T y;
};

class Primitive
{
	public:
		GLFWwindow* window;
		color_t* buffer;
		unsigned int width;
		unsigned int height;
		Primitive(Context* context);
		template<typename T>
		point<T> translate(point<T> pi,T xd, T yd);
		template<typename T>
		point<T> rotate(point<T> pi,int deg);
		template<typename T>
		void drawPixel(point<T> p,color_t color);
		template<typename T1>
		void drawLine(point<T1> p1,point<T1> p2,color_t color);
		template<typename T1>
		void drawCircle(point<T1> center,T1 radius,color_t color);
		void flushBuffer();
};

#endif