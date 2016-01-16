#ifndef __TRINAGLES_H_INCLUDED__
#define __TRINAGLES_H_INCLUDED__
#include "bool.h"

#define MAXTRIANGLES 1001

typedef struct {
	int x;				/* x position */
	int y;				/* y position */
} point;

typedef struct {
	point points[3];
} triangle;

typedef struct {
	triangle triangles[MAXTRIANGLES];
	int numTriangles;
} triangleList;

void read_triangles(triangleList *triangleList, const char *filename);

int sign(const int x);

bool is_inside_triangle(const point p, const triangle triangle);

#endif // __TRINAGLES_H_INCLUDED__