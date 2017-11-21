#include "Point2.h"

Point2::Point2()
{
	this->x = 0;
	this->y = 0;
}

Point2::Point2(double x,double y)
{
	this->x = x;
	this->y = y;
}

void Point2::setCords(double x, double y)
{
	this->x = x;
	this->y = y;
}
