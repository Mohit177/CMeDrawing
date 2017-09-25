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
#define ll long long int
#define uint unsigned int
using namespace std;
double angle=0,length=0;
int main()
{

	/*Exact copy of main.cpp used for execution time analysis: Generates
	data.txt of the form
	<n,time for generateString(),time for generatePset()>
	*/
	Context context;
	context.initialize();
	char name[]="My window";
	context.createWindow(1200,700,name);
	Primitive p = Primitive(&context);
	ifstream ins;
	srand(time(NULL));
	ins.open("dInstr.txt");
	ofstream ofil;
	ofil.open("data.txt",ios_base::out);
	int t;
	ins>>t;
	int it=1;
	while(it<=t)
	{
		int n;
		string axiom;
		ins>>n>>axiom;
		ins.get();
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
		int iter,angle,length,thickness;
		ins>>iter>>angle>>length>>thickness;
		point<double> sp,lb,ub;
		ins>>sp.x>>sp.y;
		length = length/iter;
		clock_t c1 = clock();
		LSystem2 lst = LSystem2(&p);
		lst.setRules(rule);
		lst.setAngle(angle);
		lst.setLength(length);
		lst.setIThick(thickness);
		lst.generateString(iter,axiom);
		clock_t c2 = clock();
		lst.generatePset(sp);
		clock_t c3 = clock();
		ofil<<it<<", "<<c2-c1<<", "<<c3-c2<<"\n";
		cout<<it<<", "<<c2-c1<<", "<<c3-c2<<endl;
		int type;
		ins>>type;
		if(type==1)
		{
			ins>>lb.x>>lb.y>>ub.x>>ub.y;
			lst.confineToViewPort(lb,ub);
		}
		it++;
	}
	ins.close();
	ofil.close();
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