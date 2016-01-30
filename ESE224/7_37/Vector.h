/*
* File:   vector.h
* Author: ilham
*
* Created on August 30, 2015, 3:42 AM
*/

/*Filename: Vector.h */

#ifndef __VECTOR_H_INCLUDED__
#define __VECTOR_H_INCLUDED__

#include "Point.h"
#include <iostream>
using namespace std;

// class Point forward declaration.
class Point;

// Vector in 2D space. Used to specify direction.
class Vector
{
private:
	// Data member attributes
	double xCoord;
	double yCoord;

public:
	//default constructor. Constructs zero vector.
	Vector();
	//parameterized constructor
	Vector(double x, double  y);
	//construct a vector that is directed from point @c start to point @c end.
	Vector(const Point &start, const Point & end);

	//Overloaded operators
	bool operator ==(const Vector& rhs) const;

	//Accessors Methods
	double getX() const;
	double getY() const;
	// obtain length of the vector.
	double getLength() const;
	// Construct new vector with length == 1.
	Vector constructNormalizedVector() const;

	//Mutator Methods
	void setX(double newX);
	void setY(double newY);
};

istream& operator >> (istream & is, Vector &p);

#endif // #define __VECTOR_H_INCLUDED__