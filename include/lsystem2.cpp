#include "lsystem2.h"
#include <type_traits>
#define ll long long int

LSystem2::LSystem2(Primitive* p)
{
	this->p = p;
	angle=0;
	length=0;
	iter=0;
	exp="";
	i_thick = 0;
	prod=255*255*255;
	this->wi.x = DBL_MAX;
	this->wi.y = DBL_MAX;
	this->wf.x = DBL_MIN;
	this->wf.y = DBL_MIN;
}

void LSystem2::generateString(int no_of_it,char axiom)
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
		ans=temp;
	}
	this->exp = ans;
	std::cout<<this->exp<<std::endl;
}

void LSystem2::generateString(int no_of_it, std::string axiom)
{
	this->iter = no_of_it;
	int i,j,k=axiom.length();
	std::string ans="";
	for(int q=0; q<k; q++)
	{
		ans= ans+rule[axiom[q]];
	}
	for(i=1;i<no_of_it;i++)
	{
		std::string temp="";
		for(j=0;j<ans.length();j++)
		{
			std::string value = rule[ans[j]];
			temp+=value;
		}
		ans=temp;
	}
	this->exp = ans;
	std::cout<<this->exp<<std::endl;
}

void LSystem2::setRules(std::map<char,std::string> rule)
{
	this->rule = rule;
}

void LSystem2::setLength(int length)
{
	this->length = length;
}

void LSystem2::setAngle(int angle)
{
	this->angle = angle;
}

void LSystem2::setIter(int iter)
{
	this->iter = iter;
}

void LSystem2::setIThick(int thick)
{
	this->i_thick = thick;
}

template<typename T>
void LSystem2::generatePset(point<T> sp)
{
	this->pset.clear();
	std::stack<bkp<double> > st;
	color_t c;
	c.r = 255*prod;
	c.g = 255*prod;
	c.b = 255*prod;
	ll i;
	ll size = exp.length();
	int langle=0;
	int lthick = i_thick;
	bkp<double> temp;
	coords<double> tt;
	for(i=0;i<size;i++)
	{
		if(exp[i]=='+')
		{
			langle+=angle;
		}
		else if(exp[i]=='-')
		{
			langle-=angle;
		}
		else if(exp[i]=='[')
		{
			temp.base = sp;
			temp.angle = langle;
			temp.thick = lthick;
			st.push(temp);
			if(lthick>0)
			{
				lthick--;
			}
		}
		else if(exp[i]==']')
		{
			langle = st.top().angle;
			sp = st.top().base;
			lthick = st.top().thick;
			st.pop();
		}
		else
		{
			std::cout<<lthick<<std::endl;
			point<double> p1 = sp;
			point<double> p2 = p->makePoint(sp.x,sp.y+length);
			p2 = p->translate(p2,-1*p1.x,-1*p1.y);
			p2 = p->rotate(p2,langle);
			p2 = p->translate(p2,p1.x,p1.y);
			tt.first = p1;
			tt.second = p2;
			if(exp[i]=='R')
			{
				c.r = 255*prod;
				c.g=0;
				c.b=0;
			}
			else if(exp[i]=='G')
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
			tt.color = c;
			tt.thick = lthick;
			pset.push_back(tt);
			sp = p2;
		}
	}
}

template<typename T>
void LSystem2::confineToViewPort(point<T> lb, point<T> ub)
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