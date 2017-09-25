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
#include "include/lsystem.cpp" //including required headers
#define ll long long int
#define uint unsigned int
using namespace std;

double angle=0,length=0;
int main()
{
	Context context; //Creating an OpenGL context
	context.initialize(); // initializing context
	char name[]="My window";
	context.createWindow(1200,700,name); // window of dimension 1200x700 pixels
	Primitive p = Primitive(&context); // Creating Primitive class object, passing reference to context
	ifstream ins;
	srand(time(NULL));
	ins.open("dInstr.txt"); //dInstr.txt file contains drawing instructions with grammar rules and parameters like length, angle, thickeness
	int t;
	ins>>t;
	while(t>0)
	{
		int n;
		string axiom;
		ins>>n>>axiom;
		ins.get(); //to prevent /n from entering str
		map<char,vector<string> > rule;
		while(n>0)
		{
			string str;
			getline(ins,str);
			string temp="";
			int i;
			int size = str.length();
			for(i=2;i<size;i++)
			{
				temp+=str[i];
			}
			rule[str[0]].push_back(temp);
			n--;
		}
		/*Taking drawing parameters as input from file*/
		int iter,angle,length,thickness;
		ins>>iter>>angle>>length>>thickness;
		point<double> sp,lb,ub;
		ins>>sp.x>>sp.y;
		length = length/iter;
		// Creating object of LSystem2
		LSystem2 lst = LSystem2(&p);
		//Setting drawing parameters
		lst.setRules(rule);
		lst.setAngle(angle);
		lst.setLength(length);
		lst.setIThick(thickness);
		lst.generateString(iter,axiom); //generates string exp with rule, axiom for iter no.of iterations
		lst.generatePset(sp); //generates vector<coords<double> > pset : the list of pair of points
		int type;
		ins>>type; //if type is 0. No confining to viewPort
		if(type==1)
		{
			ins>>lb.x>>lb.y>>ub.x>>ub.y; //else confine the drawing to view port
			lst.confineToViewPort(lb,ub);
		}
		long long int size = lst.pset.size();
		long long int i=0;
		for(i=0;i<size;i++)
		{
			/*Take each pair from pset and call drawLine()*/
			p.drawLine(lst.pset[i].first,lst.pset[i].second,lst.pset[i].color,lst.pset[i].thick);
		}
		t--;
	}
	ins.close();
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