#include <iostream>
#include <cstdio>
#include <map>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include "primitives.cpp"
#define ll long long int
#ifndef LSYSTEM_2_H
#define LSYSTEM_2_H

template<typename T>
struct coords
{
	point<T> first;
	point<T> second;
	color_t color;
};

template<typename T>
struct bkp
{
	point<T> base;
	int angle;
};

class LSystem2
{
	private:
		std::map<char,std::string> rule;
		std::string exp;
		int angle;
		int length;
		int iter;
		point<double> wi;
		point<double> wf;

	public:
		Primitive* p;
		LSystem2(Primitive* p);
		unsigned int prod;
		std::vector<coords<double> >pset;
		void generateString(int no_of_it, char axiom);
		void generateString(int no_of_it, std::string axiom);
		void setRules(std::map<char,std::string> rule);
		void setIter(int iter);
		void setAngle(int angle);
		void setLength(int length);
		template<typename T>
		void generatePset(point<T> sp);
		template<typename T>
		void confineToViewPort(point<T> lb,point<T> ub);
};



#endif