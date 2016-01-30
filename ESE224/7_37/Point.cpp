/* 
 * File:   main7_37.cpp
 * Author: ilham
 *
 * Created on May 9, 2015, 5:50 AM
 */
/*-------------------------------------------------------*/

/*-------------------------------------------------------*/
#include<iostream> //Required for cin, cout, cerr.
#include"Point.h" //Required for Point.

//Parameterized constructor
Point::Point(double x, double y)
	: xCoord(x)
	, yCoord(y)
{
}

Point::Point()
	: xCoord(0.0)
	, yCoord(0.0)
{
}

bool Point::operator ==(const Point& rhs) const
{
	return (rhs.xCoord == xCoord &&
		rhs.yCoord == yCoord);
}


double Point::getX() const
{
	return xCoord;
}

double Point::getY() const
{
	return yCoord;
}

void Point::setX(double xVal) 
{
  xCoord = xVal;
}

void Point::setY(double yVal)
{
   yCoord = yVal;
}  

void Point::move(const Vector &direction, const double distance)
{
	const Vector normalized_direction = direction.constructNormalizedVector();
	xCoord += normalized_direction.getX() * distance;
	yCoord += normalized_direction.getY() * distance;
}

istream& operator >> (istream& in, Point & p)
{
   double x, y;
   in >> x >> y;
   p.setX(x);
   p.setY(y);

   return in;
}

ostream & operator << (ostream & os, const Point & p)
{
	os << "(" << p.getX() << ", " << p.getY() << ")";
	return os;
}


