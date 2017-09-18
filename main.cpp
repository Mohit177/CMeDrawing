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

double angle=0,length=0;
template<typename T>
struct coords
{
	point<T> first;
	point<T> second;
	color_t color;
};

template<typename T>
struct seg
{
	int dir;
	point<T> base;
	vector<pair<point<T>,point<T> > >plist;
};

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
int main()
{
	Context context;
	context.initialize();
	char name[]="My window";
	context.createWindow(600,600,name);
	char axiom = 'F';
	map<char,string> rule;
	int iter;
	cin>>iter;
	rule['F']="X+[F]X-[F]F";
	rule['X']="XX";
	rule['[']="[";
	rule[']']="]";
	rule['+']="+";
	rule['-']="-";
	string draw = stringGenerator(iter,rule,'F');
	Primitive p = Primitive(&context);
	point<double> sp;
	cin>>sp.x>>sp.y;
	cin>>angle>>length;
	cout<<draw<<endl;
	stack<seg<double> > st;
	color_t c;
	c.r = 255*prod;
	c.g = 255*prod;
	c.b = 0;
	seg<double> temp;
	ll size = draw.length();
	ll i,j;
	int ldir=0;
	for(i=0;i<size;i++)
	{
		cout<<sp.x<<" "<<sp.y<<endl;
		if(draw[i]=='+')
		{
			ldir = 1;
		}
		else if(draw[i]=='-')
		{
			ldir = 2;
		}
		else if(draw[i]=='[')
		{
			temp.dir = ldir;
			st.top().base = sp;
			temp.base = sp;
			temp.plist.clear();
			st.push(temp);
		}
		else if(draw[i]==']')
		{
			vector<pair<point<double>,point<double> > > v;
			ll ls = st.top().plist.size();
			seg<double> top = st.top();
			st.pop();
			point<double> base = st.top().base;
			for(j=0;j<ls;j++)
			{
				if(top.dir==1)
				{
					top.plist[j].first = p.translate(top.plist[j].first,-1*base.x,-1*base.y);
					top.plist[j].second = p.translate(top.plist[j].second,-1*base.x,-1*base.y);
					top.plist[j].first = p.rotate(top.plist[j].first,angle);
					top.plist[j].second = p.rotate(top.plist[j].second,angle);
					top.plist[j].first = p.translate(top.plist[j].first,base.x,base.y);
					top.plist[j].second = p.translate(top.plist[j].second,base.x,base.y);
				}
				else if(top.dir==2)
				{
					top.plist[j].first = p.translate(top.plist[j].first,-1*base.x,-1*base.y);
					top.plist[j].second = p.translate(top.plist[j].second,-1*base.x,-1*base.y);
					top.plist[j].first = p.rotate(top.plist[j].first,-1*angle);
					top.plist[j].second = p.rotate(top.plist[j].second,-1*angle);
					top.plist[j].first = p.translate(top.plist[j].first,base.x,base.y);
					top.plist[j].second = p.translate(top.plist[j].second,base.x,base.y);	
				}
				v.push_back(top.plist[j]);		
			}
			sp = st.top().base;
			st.top().plist.insert(st.top().plist.end(),v.begin(),v.end());
		}
		else
		{
			point<double> p1 = sp;
			point<double> p2 = p.makePoint(sp.x,sp.y+length);
			if(st.empty())
			{
				temp.dir=ldir;
				temp.base = sp;
				temp.plist.clear();
				st.push(temp);
			}
			st.top().plist.push_back(make_pair(p1,p2));
			sp=p2;
		}
	}
	//cout<<st.top().plist.size()<<endl;
	size = st.top().plist.size();
	for(i=0;i<size;i++)
	{
		cout<<st.top().plist[i].first.x<<" "<<st.top().plist[i].first.y<<" "<<st.top().plist[i].second.x<<" "<<st.top().plist[i].second.y<<endl;
		p.drawLine(st.top().plist[i].first,st.top().plist[i].second,c);
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