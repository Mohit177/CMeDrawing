#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include "primitives.cpp"
#define ll long long int
#ifndef LSYSTEM_1_H
#define LSYSTEM_1_H

//Data structure to represent a pair of points. Used to call drawLine with color and thickness
template<typename T>
struct coords
{
	point<T> first;
	point<T> second;
	color_t color;
	int thick;
};

//Data structure to represent 
template<typename T>
struct seg
{
	int dir;
	point<T> base;
	std::vector<coords<T> > plist;
};

template<typename T>
struct bkp
{
	point<T> base;
	int angle;
	int thick;
};

//Simple branching and recursion L-Systems
class LSystem1
{
	private:
		std::map<char,std::string> rule;  // To specify grammar rules
		std::string exp; // string to be drawn
		/*Drawing parameters*/
		int angle;
		int length;
		int iter;
		point<double> wi;
		point<double> wf;

	public:
		Primitive* p;
		LSystem1(Primitive* p);
		unsigned int prod;
		std::vector<coords<double> >pset;
		void generateString(int no_of_it, char axiom);
		void setRules(std::map<char,std::string> rule);
		void setIter(int no_of_it);
		void setAngle(int angle);
		void setLength(int length);
		template<typename T>
		void generatePset(point<T> sp);
		template<typename T>
		void confineToViewPort(point<T> lb, point<T> ub);
};

//Turtle drawing L-System
class LSystem2
{
	private:
		std::map<char,std::vector<std::string> > rule; //stored as vector of string, if X:XX and X:X both are given, one of them is chosen randomly
		std::string exp; // string to be drawn
		/*Drawing parameters*/
		int angle;
		int length;
		int iter;
		int i_thick;
		point<double> wi;
		point<double> wf;

	public:
		Primitive* p;
		LSystem2(Primitive* p);
		unsigned int prod;
		std::vector<coords<double> >pset;
		color_t getColor(char ch);
		void generateString(int no_of_it, char axiom);
		void generateString(int no_of_it, std::string axiom);
		void setRules(std::map<char,std::vector<std::string> > rule);
		void setIter(int iter);
		void setAngle(int angle);
		void setLength(int length);
		void setIThick(int thick);
		template<typename T>
		void generatePset(point<T> sp);
		template<typename T>
		void confineToViewPort(point<T> lb,point<T> ub);
};

#endif