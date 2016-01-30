#include "Line.h"

Line::Line()
	: length(0)
{
}

Line::Line(Point & first, Point & second)
	: firstPoint(first)
	, secondPoint(second)
	, length(Vector(first, second).getLength())
{
}

void Line::translate(Vector & direction, double distance)
{
	firstPoint.move(direction, distance);
	secondPoint.move(direction, distance);
}

void Line::resize(double scale)
{
	firstPoint.setX(firstPoint.getX() * scale);
	firstPoint.setY(firstPoint.getY() * scale);
	
	secondPoint.setX(secondPoint.getX() * scale);
	secondPoint.setY(secondPoint.getY() * scale);
	length *= scale;
}

double Line::getLength() const
{
	return length;
}

const Point & Line::getFirstPoint() const
{
	return firstPoint;
}

const Point & Line::getSecondPoint() const
{
	return secondPoint;
}

void Line::setFirstPoint(const Point &p)
{
	firstPoint = p;
	length = Vector(firstPoint, secondPoint).getLength();
}

void Line::setSecondPoint(const Point &p)
{
	secondPoint = p;
	length = Vector(firstPoint, secondPoint).getLength();
}

ostream & operator << (ostream & os, const Line & l)
{
	os << "Line with length " << l.getLength() << " that connects point " << l.getFirstPoint() << " and " << l.getSecondPoint();
	return os;
}