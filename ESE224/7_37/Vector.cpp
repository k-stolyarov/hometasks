/*
* File:   main7_37.cpp
* Author: ilham
*
* Created on May 9, 2015, 5:50 AM
*/
/*-------------------------------------------------------*/

/*-------------------------------------------------------*/
#include<iostream> //Required for cin, cout, cerr.
#include"Vector.h"

//Parameterized constructor
Vector::Vector(double x, double y)
	: xCoord(x)
	, yCoord(y)
{
}

Vector::Vector(const Point &start, const Point & end)
	: xCoord(end.getX() - start.getX())
	, yCoord(end.getY() - start.getY())
{
}

Vector::Vector()
	: xCoord(0.0)
	, yCoord(0.0)
{
}

bool Vector::operator ==(const Vector& rhs) const
{
	return (rhs.xCoord == xCoord &&
		rhs.yCoord == yCoord);
}

double Vector::getX() const
{
	return xCoord;
}

double Vector::getY() const
{
	return yCoord;
}

double Vector::getLength() const
{
	return sqrt(xCoord * xCoord + yCoord * yCoord);
}

Vector Vector::constructNormalizedVector() const
{
	const double length = getLength();
	if (0.0 == length)
	{
		return Vector();
	}
	
	return Vector(xCoord / length, yCoord / length);
}

void Vector::setX(double xVal)
{
	xCoord = xVal;
}

void Vector::setY(double yVal)
{
	yCoord = yVal;
}

istream& operator >> (istream& in, Vector & p)
{
	double x, y;
	in >> x >> y;
	p.setX(x);
	p.setY(y);

	return in;
}




