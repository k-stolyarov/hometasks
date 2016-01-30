/*
 * File:   point.h
 * Author: ilham
 *
 * Created on August 29, 2015, 5:12 AM
 */

/*Filename: Point.h */
#ifndef __POINT_H_INCLUDED__
#define __POINT_H_INCLUDED__

#include "Vector.h"
#include <iostream>
using namespace std;

// class Vector forward declaration.
class Vector;
// Class for presentation a single point in 2D space. Used to specify position.
class Point
{
private:
	// Data member attributes
	double xCoord;
	double yCoord;

public:
	//Declaration statements for class methods
	//Constructors for Point class
	Point(); //default constructor
	Point(double x, double  y); //parameterized constructor

	//Overloaded operators
	bool operator ==(const Point& rhs) const;
	

	//Accessors Methods
	double getX() const;
	double getY() const;

	//Mutator Methods
	void setX(double newX);
	void setY(double newY);
	// Move point in given direction to specified distance 
	void move(const Vector &direction, double distance);
};

// IO operations
istream& operator >> (istream & is, Point &p);
ostream & operator << (ostream & os, const Point & p);

#endif // #define __POINT_H_INCLUDED__