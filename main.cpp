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
#include "include/lsystem.cpp"
#define ll long long int
#define uint unsigned int
using namespace std;
double angle=0,length=0;
int main()
{
	Context context;
	context.initialize();
	char name[]="My window";
	context.createWindow(1200,700,name);
	Primitive p = Primitive(&context);
	ifstream ins;
	ins.open("dInstr.txt");
	int t;
	ins>>t;
	//cout<<t<<endl;
	while(t>0)
	{
		int n;
		string axiom;
		ins>>n>>axiom;
		//cout<<n<<" "<<axiom<<endl;
		ins.get();
		map<char,string> rule;
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
			//cout<<str[0]<<" "<<temp<<endl;
			rule[str[0]]=temp;
			n--;
		}
		int iter,angle,length,thickness;
		ins>>iter>>angle>>length>>thickness;
		point<double> sp,lb,ub;
		ins>>sp.x>>sp.y;
		length = length/iter;
		LSystem2 lst = LSystem2(&p);
		lst.setRules(rule);
		lst.setAngle(angle);
		lst.setLength(length);
		lst.setIThick(thickness);
		lst.generateString(iter,axiom);
		lst.generatePset(sp);
		int type;
		ins>>type;
		if(type==1)
		{
			ins>>lb.x>>lb.y>>ub.x>>ub.y;
			lst.confineToViewPort(lb,ub);
		}
		long long int size = lst.pset.size();
		long long int i=0;
		for(i=0;i<size;i++)
		{
			p.drawLine(lst.pset[i].first,lst.pset[i].second,lst.pset[i].color,lst.pset[i].thick);
		}
		t--;
	}
	ins.close();
	/*string axiom = "F";
	map<char,string> rule;
	int iter;
	cin>>iter;
	rule['F']="X+[F]+[F]---[F]-[F]";
	rule['X']="XX";
	rule['B']="B";
	rule['G']="GG";
	rule['R']="R";
	rule['[']="[";
	rule[']']="]";
	rule['+']="+";
	rule['-']="-";
	point<double> sp;
	cin>>sp.x>>sp.y;
	cin>>angle>>length;
	length= length/iter;
	LSystem2 lst = LSystem2(&p);
	lst.setRules(rule);
	lst.setAngle(angle);
	lst.setLength(length);
	lst.setIThick(3);
	lst.generateString(iter,axiom);
	lst.generatePset(sp);
	ll i,size;
	//cout<<st.top().plist.size()<<endl;
	point<double> lb,ub;
	lb.x = 100;
	lb.y = 100;
	ub.x = 400;
	ub.y = 450;
	lst.confineToViewPort(lb,ub);
	size = lst.pset.size();
	for(i=0;i<size;i++)
	{
		//cout<<lst.pset[i].thick<<endl;
		p.drawLine(lst.pset[i].first,lst.pset[i].second,lst.pset[i].color,lst.pset[i].thick);
	}*/
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