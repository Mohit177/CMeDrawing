#include <iostream>
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
#include "include/lsystem2.cpp"
#define ll long long int
#define uint unsigned int
using namespace std;
double angle=0,length=0;
int main()
{
	Context context;
	context.initialize();
	char name[]="My window";
	context.createWindow(600,600,name);
	string axiom = "FX";
	map<char,string> rule;
	int iter;
	cin>>iter;
	rule['F']="FF-[-F+F]+[+F-F]";
	rule['X']="FF+[+F]+[-F]";
	rule['B']="B";
	rule['G']="GG";
	rule['R']="R";
	rule['[']="[";
	rule[']']="]";
	rule['+']="+";
	rule['-']="-";
	Primitive p = Primitive(&context);
	point<double> sp;
	cin>>sp.x>>sp.y;
	cin>>angle>>length;
	length= length/iter;
	LSystem2 lst = LSystem2(&p);
	lst.setRules(rule);
	lst.setAngle(angle);
	lst.setLength(length);
	lst.generateString(iter,axiom);
	lst.generatePset(sp);
	ll i,size;
	//cout<<st.top().plist.size()<<endl;
	point<double> lb,ub;
	lb.x = 100;
	lb.y = 100;
	ub.x = 350;
	ub.y = 500;
	lst.confineToViewPort(lb,ub);
	size = lst.pset.size();
	for(i=0;i<size;i++)
	{
		p.drawLine(lst.pset[i].first,lst.pset[i].second,lst.pset[i].color,0);
	}
	color_t* buffer = context.getFrameBuffer();
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