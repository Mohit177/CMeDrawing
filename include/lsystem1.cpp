#include "lsystem1.h"
#include <type_traits>
#define ll long long int

LSystem1::LSystem1(Primitive* p)
{
	this->p = p;
	angle=0;
	length=0;
	iter=0;
	exp="";
	prod=255*255*255;
	this->wi.x = DBL_MAX;
	this->wi.y = DBL_MAX;
	this->wf.x = DBL_MIN;
	this->wf.y = DBL_MIN;
}

void LSystem1::generateString(int no_of_it,char axiom)
{
	this->iter = no_of_it;
	int i,j,k;
	std::string ans=rule[axiom];
	int vs = rule.size();
	for(i=1;i<no_of_it;i++)
	{
		std::string temp="";
		for(j=0;j<ans.length();j++)
		{
			std::string value = rule[ans[j]];
			temp+=value;
		}
		rule[axiom]=temp;
		ans=rule[axiom];
	}
	this->exp = ans;
	std::cout<<this->exp<<std::endl;
}

void LSystem1::setRules(std::map<char,std::string> rule)
{
	this->rule = rule;
}

void LSystem1::setLength(int length)
{
	this->length = length;
}

void LSystem1::setAngle(int angle)
{
	this->angle = angle;
}

void LSystem1::setIter(int iter)
{
	this->iter = iter;
}

template<typename T>
void LSystem1::generatePset(point<T> sp)
{
	this->pset.clear();
	std::stack<seg<double> > st;
	color_t c;
	c.r = 255*prod;
	c.g = 255*prod;
	c.b = 0;
	seg<double> temp;
	ll size = exp.length();
	ll i,j;
	int ldir=0;
	for(i=0;i<size;i++)
	{
		//cout<<sp.x<<" "<<sp.y<<endl;
		if(exp[i]=='+')
		{
			ldir = 1;
		}
		else if(exp[i]=='-')
		{
			ldir = 2;
		}
		else if(exp[i]=='[')
		{
			temp.dir = ldir;
			st.top().base = sp;
			temp.base = sp;
			temp.plist.clear();
			st.push(temp);
		}
		else if(exp[i]==']')
		{
			std::vector<coords<double> > v;
			ll ls = st.top().plist.size();
			seg<double> top = st.top();
			st.pop();
			point<double> base = st.top().base;
			for(j=0;j<ls;j++)
			{
				if(top.dir==1)
				{
					top.plist[j].first = p->translate(top.plist[j].first,-1*base.x,-1*base.y);
					top.plist[j].second = p->translate(top.plist[j].second,-1*base.x,-1*base.y);
					top.plist[j].first = p->rotate(top.plist[j].first,angle);
					top.plist[j].second = p->rotate(top.plist[j].second,angle);
					top.plist[j].first = p->translate(top.plist[j].first,base.x,base.y);
					top.plist[j].second = p->translate(top.plist[j].second,base.x,base.y);
				}
				else if(top.dir==2)
				{
					top.plist[j].first = p->translate(top.plist[j].first,-1*base.x,-1*base.y);
					top.plist[j].second = p->translate(top.plist[j].second,-1*base.x,-1*base.y);
					top.plist[j].first = p->rotate(top.plist[j].first,-1*angle);
					top.plist[j].second = p->rotate(top.plist[j].second,-1*angle);
					top.plist[j].first = p->translate(top.plist[j].first,base.x,base.y);
					top.plist[j].second = p->translate(top.plist[j].second,base.x,base.y);	
				}
				v.push_back(top.plist[j]);		
			}
			sp = st.top().base;
			st.top().plist.insert(st.top().plist.end(),v.begin(),v.end());
		}
		else
		{
			point<double> p1 = sp;
			point<double> p2 = p->makePoint(sp.x,sp.y+length);
			if(st.empty())
			{
				temp.dir=ldir;
				temp.base = sp;
				temp.plist.clear();
				st.push(temp);
			}
			if(exp[i]=='R')
			{
				c.r = 255*prod;
				c.g=0;
				c.b=0;
			}
			else if(exp[i]=='F')
			{
				c.r=0;
				c.g=255*prod;
				c.b=0;
			}
			else if(exp[i]=='B')
			{
				c.r=0;
				c.g=0;
				c.b=255*prod;
			}
			else
			{
				c.r=255*prod;
				c.g=255*prod;
				c.b=0;
			}
			coords<double> kk;
			kk.first=p1;
			kk.second=p2;
			kk.color=c;
			st.top().plist.push_back(kk);
			sp=p2;
		}
	}
	size = st.top().plist.size();
	for(i=0;i<size;i++)
	{
		pset.push_back(st.top().plist[i]);
	}
	while(!st.empty())
	{
		st.pop();
	}
}

template<typename T>
void LSystem1::confineToViewPort(point<T> lb, point<T> ub)
{
	ll size = pset.size();
	ll i;
	wi.x = DBL_MAX;
	wi.y = DBL_MAX;
	wf.x = DBL_MIN;
	wf.y = DBL_MIN;
	for(i=0;i<size;i++)
	{
		wi.x = std::min(wi.x,std::min(pset[i].first.x,pset[i].second.x));
		wi.y = std::min(wi.y,std::min(pset[i].first.y,pset[i].second.y));
		wf.x = std::max(wf.x,std::max(pset[i].first.x,pset[i].second.x));
		wf.y = std::max(wf.y,std::max(pset[i].first.y,pset[i].second.y));
	}
	point<double> s,t;
	s.x = (ub.x*1.000 - lb.x*1.000)/(wf.x*1.000 - wi.x*1.0000);
	s.y = (ub.y*1.000 - lb.y*1.000)/(wf.y*1.000 - wi.y*1.0000);
	t.x = (wf.x*lb.x*1.000 - wi.x*ub.x*1.000)/(wf.x*1.000 - wi.x*1.000);
	t.y = (wf.y*lb.y*1.000 - wi.y*ub.y*1.000)/(wf.y*1.000 - wi.y*1.000);
	for(i=0;i<size;i++)
	{
		pset[i].first.x = t.x + s.x*pset[i].first.x;
		pset[i].second.x = t.x + s.x*pset[i].second.x;
		pset[i].first.y = t.y + s.y*pset[i].first.y;
		pset[i].second.y = t.y + s.y*pset[i].second.y;
	}
}
