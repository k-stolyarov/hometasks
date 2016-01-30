/* 
 * File:   Line.h
 * Author: ilham
 *
 * Created on August 30, 2015, 2:08 AM
 */

#ifndef LINE_H
#define	LINE_H
#include"Point.h"
#include<iostream>
#include<cmath>

// Class for a line cut representation.
class Line
{
private:
	Point firstPoint;
	Point secondPoint;
    double length;
     
public:
	Line();
	Line(Point & first, Point & second);
	
	// translate a line in given direction for a specified distance.
	void translate(Vector & direction, double distance);
	// Scale each point coordinate in @c scale times.
	void resize(double scale);

	// Accessors
	double getLength() const;
	const Point & getFirstPoint() const;
	const Point & getSecondPoint() const;

	void setFirstPoint(const Point &p);
	void setSecondPoint(const Point &p);
};
ostream & operator << (ostream & os, const Line & l);

#endif	/* LINE_H */

