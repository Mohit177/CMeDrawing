#include "primitives.h"
#define PI 3.1415926535898
#include <type_traits>


//Defining functions of Primitive class
Primitive::Primitive(Context* context)
{
	if(context->getWindow()==NULL || context->getFrameBuffer()==NULL || context->getWindowWidth()<=0 || context->getWindowHeight()<=0)
	{
		std::cerr<<"Window not created"<<std::endl;
		exit(-1);
	}
	this->window = context->getWindow();
	this->buffer = context->getFrameBuffer();
	this->width = context->getWindowWidth();
	this->height = context->getWindowHeight();
}

void Primitive::flushBuffer()
{
	glfwSwapBuffers(this->window);
	glfwPollEvents();
}

template<typename T>
point<T> Primitive::makePoint(T x, T y)
{
	point<T> temp;
	temp.x = x;
	temp.y = y;
	return temp;
}
// Draw a single pixel.
/* Precondition: The point parameter can be of type unsigned int, float, or double only
and must be a positive value in case of float or double*/

template<typename T>
void Primitive::drawPixel(point<T> p,color_t color)
{
	if(std::is_same<unsigned int,T>::value || std::is_same<int,T>::value)
	{
		unsigned int temp = p.y*this->width+p.x;
		if(temp>=0 && temp<((this->width)*(this->height)))
		{
			this->buffer[temp] = color;
		}
	}
}

// Line drawing
template<typename T1>
void Primitive::drawLine(point<T1> p1, point<T1> p2, color_t color)
{
	if(std::is_same<float,T1>::value || std::is_same<double,T1>::value)
	{
		point<unsigned int> pf1,pf2;
		pf1.x = floor(p1.x+0.5);
		pf1.y = floor(p1.y+0.5);
		pf2.x = floor(p2.x+0.5);
		pf2.y = floor(p2.y+0.5);
		drawLine(pf1,pf2,color);
	}
	if(std::is_same<unsigned int, T1>::value)
	{
		point<T1> temp;
		if(p1.x>p2.x)
		{
			point<T1> as = p1;
			p1 = p2;
			p2 = as;
		}
		int a = p2.y - p1.y;
		int b = p1.x - p2.x;
		int xi = 1;
		int yi = 1;
		int xp = p1.x;
		int yp = p1.y;
		int xf = p2.x;
		int yf = p2.y;
		temp.x=xp;
		temp.y=yp;
		drawPixel(temp,color);
		double m = abs((a)*1.00000)/(abs(b)*1.000000);
		//std::cout<<m<<std::endl;
		if(a<0)
		{
			yi=-1;
		}
		if(m<=1)
		{
			int d = (2*a*xi+yi*b);
			int incrS = 2*a*xi;
			int incrD = 2*a*xi + 2*b*yi;
			while(xp!=xf)
			{
				if(d*yi<=0)
				{
					d+=incrS;
				}
				else
				{
					d+=incrD;
					yp+=yi;
				}
				xp+=xi;
				temp.x=xp;
				temp.y=yp;
				drawPixel(temp,color);
			}
		}
		else
		{
			int d = (a*xi+2*yi*b);
			int incrS = 2*yi*b;
			int incrD = 2*xi*a + 2*yi*b;
			while(yp!=yf)
			{
				if(d*yi>0)
				{
					d+=incrS;
				}
				else
				{
					d+=incrD;
					xp+=xi;
				}
				yp+=yi;
				temp.x=xp;
				temp.y=yp;
				drawPixel(temp,color);
			}
		}
		//flushBuffer();
	}
}

template<typename T1>
void Primitive::drawLine(point<T1> p1, point<T1> p2, color_t color,int thick)
{
	if(std::is_same<float,T1>::value || std::is_same<double,T1>::value)
	{
		point<unsigned int> pf1,pf2;
		pf1.x = floor(p1.x+0.5);
		pf1.y = floor(p1.y+0.5);
		pf2.x = floor(p2.x+0.5);
		pf2.y = floor(p2.y+0.5);
		drawLine(pf1,pf2,color,thick);
	}
	if(std::is_same<unsigned int, T1>::value)
	{
		point<T1> temp;
		if(p1.x>p2.x)
		{
			point<T1> as = p1;
			p1 = p2;
			p2 = as;
		}
		int a = p2.y - p1.y;
		int b = p1.x - p2.x;
		int xi = 1;
		int yi = 1;
		int xp = p1.x;
		int yp = p1.y;
		int xf = p2.x;
		int yf = p2.y;
		int jj;
		temp.x=xp;
		temp.y=yp;
		drawPixel(temp,color);
		double m = abs((a)*1.00000)/(abs(b)*1.000000);
		//std::cout<<m<<std::endl;
		if(a<0)
		{
			yi=-1;
		}
		if(m<=1)
		{
			int d = (2*a*xi+yi*b);
			int incrS = 2*a*xi;
			int incrD = 2*a*xi + 2*b*yi;
			while(xp!=xf)
			{
				if(d*yi<=0)
				{
					d+=incrS;
				}
				else
				{
					d+=incrD;
					yp+=yi;
				}
				xp+=xi;
				temp.x=xp;
				temp.y=yp;
				drawPixel(temp,color);
				for(jj=1;jj<=thick;jj++)
				{
					drawPixel(makePoint(temp.x,temp.y+jj),color);
					drawPixel(makePoint(temp.x,temp.y-jj),color);
				}
			}
		}
		else
		{
			int d = (a*xi+2*yi*b);
			int incrS = 2*yi*b;
			int incrD = 2*xi*a + 2*yi*b;
			while(yp!=yf)
			{
				if(d*yi>0)
				{
					d+=incrS;
				}
				else
				{
					d+=incrD;
					xp+=xi;
				}
				yp+=yi;
				temp.x=xp;
				temp.y=yp;
				drawPixel(temp,color);
				for(jj=1;jj<=thick;jj++)
				{
					drawPixel(makePoint(temp.x+jj,temp.y),color);
					drawPixel(makePoint(temp.x-jj,temp.y),color);
				}
			}
		}
		//flushBuffer();
	}
}

template<typename T1>
void Primitive::drawCircle(point<T1> center, T1 radius, color_t color)
{
	if(std::is_same<float,T1>::value || std::is_same<double,T1>::value)
	{
		point<unsigned int> ncenter;
		ncenter.x = floor(center.x+0.5);
		ncenter.y = floor(center.y+0.5);
		unsigned int nrad = floor(radius+0.5);
		drawCircle(ncenter,nrad,color);
	}
	if(std::is_same<unsigned int,T1>::value)
	{
		int xp = 0;
		int yp = radius;
		int d = 5/4 - radius;
		int deltaE = 3;
		int deltaSE = 5 - 2*radius;
		drawPixel(makePoint(center.x+xp,center.y+yp),color);
		drawPixel(makePoint(center.x+yp,center.y+xp),color);
		drawPixel(makePoint(center.x-yp,center.y+xp),color);
		drawPixel(makePoint(center.x+xp,center.y-yp),color);
		drawPixel(makePoint(center.x-xp,center.y-yp),color);
		drawPixel(makePoint(center.x-yp,center.y-xp),color);
		drawPixel(makePoint(center.x+yp,center.y-xp),color);
		drawPixel(makePoint(center.x-xp,center.y+yp),color);
		while(xp<=yp)
		{
			if(d<=0)
			{
				/* Mid point lies inside the circle, choose east pixel*/
				d+=deltaE;
				deltaE+=2;
				deltaSE+=2;
			}
			else
			{
				/*Mid point lies outside circle, choose south east pixel*/
				d+=deltaSE;
				deltaSE+=4;
				deltaE+=2;
				yp--;
			}
			xp++;
			drawPixel(makePoint(center.x+xp,center.y+yp),color);
			drawPixel(makePoint(center.x+yp,center.y+xp),color);
			drawPixel(makePoint(center.x-yp,center.y+xp),color);
			drawPixel(makePoint(center.x+xp,center.y-yp),color);
			drawPixel(makePoint(center.x-xp,center.y-yp),color);
			drawPixel(makePoint(center.x-yp,center.y-xp),color);
			drawPixel(makePoint(center.x+yp,center.y-xp),color);
			drawPixel(makePoint(center.x-xp,center.y+yp),color);
		}
		//flushBuffer();
	}
}

template<typename T>
point<T> Primitive::translate(point <T> pi, T xd, T  yd)
{
	point<T> pf;
	pf.x = pi.x+xd;
	pf.y = pi.y+yd;
	return pf;
}

template<typename T>
point<T> Primitive::rotate(point<T> pi, int deg)
{
	double rads = (PI*1.0000*deg)/180;
	double cosin = cos(rads);
	double sine = sin(rads);
	double xn = pi.x*cosin - pi.y*sine;
	double yn = pi.x*sine + pi.y*cosin;
	point<double> pf;
	pf.x = xn;
	pf.y = yn;
	return pf;
}

template<typename T>
point<double> Primitive::viewPortTransform(point<T> pi,point<T> lb, point<T> ub, point<T> wi, point<T> wf)
{
    point<double> ans;
	point<double> s,t;
	s.x = (ub.x*1.0000 - lb.x*1.000)/(wf.x*1.000 - wi.x*1.000);
	s.y = (ub.y*1.0000 - lb.y*1.000)/(wf.y*1.000 - wi.y*1.000);
	t.x = (wf.x*lb.x*1.000 - wi.x*ub.x*1.000)/(wf.x*1.000 - wi.x*1.000);
	t.y = (wf.y*lb.y*1.000 - wi.y*ub.y*1.000)/(wf.y*1.000 - wi.y*1.000);
	ans.x = t.x + s.x*pi.x;
	ans.y = t.y + s.y*pi.y;
	return ans;
}