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
#include "include/primitives.cpp"
#define ll long long int
#define uint unsigned int
using namespace std;

unsigned int prod=256*256*256;
string stringGenerator(int no_of_it, map<char,string> rule,char axiom)
{
	int i,j,k;
	string ans=rule[axiom];
	int vs = rule.size();
	for(i=1;i<no_of_it;i++)
	{
		string temp="";
		for(j=0;j<ans.length();j++)
		{
			string value = rule[ans[j]];
			temp+=value;
		}
		rule[axiom]=temp;
		ans=rule[axiom];
	}
	return ans;
}
void drawString(string s,int angle)
{
	int i;
	stack<int> st;

}
int main()
{
	Context context;
	context.initialize();
	char name[]="My window";
	context.createWindow(600,600,name);
	/*char axiom = 'F';
	map<char,string> rule;
	int iter;
	cin>>iter;
	rule['F']="X+[F]X-[F]F";
	rule['X']="XX";
	rule['[']="[";
	rule[']']="]";
	rule['+']="+";
	rule['-']="-";

	cout<<stringGenerator(iter,rule,'F');*/
	color_t* buffer = context.getFrameBuffer();
	//glDrawPixels(context.getWindowWidth(),context.getWindowHeight(),GL_RGB,GL_UNSIGNED_INT,buffer);
	Primitive p = Primitive(&context);
	point<double> p1,p2;
	cin>>p1.x>>p1.y>>p2.x>>p2.y;
	color_t c;
	c.r = 255*prod;
	c.g = 255*prod;
	c.b = 0;
	p.drawLine(p1,p2,c);
	p.flushBuffer();
	point<double> tt = p1;
	p1 = p.translate(p1,-1*p1.x,-1*p1.y);
	p2 = p.translate(p2,-1*tt.x,-1*tt.y);
	p1 = p.rotate(p1,45);
	p2 = p.rotate(p2,45);
	p1 = p.translate(p1,tt.x,tt.y);
	p2 = p.translate(p2,tt.x,tt.y);
	p.drawLine(p1,p2,c);
	//sleep(5);
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