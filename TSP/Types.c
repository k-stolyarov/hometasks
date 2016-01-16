#include "Types.h"
#include <math.h>

void append_point(AllPoints *all_points, int x, int y)
{
	if (all_points->number_of_points >= MAX_POINTS)
	{
		return;
	}
	all_points->points[all_points->number_of_points].x = x;
	all_points->points[all_points->number_of_points].y = y;

	++all_points->number_of_points;
}

void append_edge(EdgesPath *path, int start, int end)
{
	path->edges[path->size].start = start;
	path->edges[path->size].end = end;
	path->size++;
}

int compare_points(const void * a, const void * b)
{
	int res = ((const Point*)a)->x - ((const Point*)b)->x;
	if (0 == res)
	{
		return ((const Point*)a)->y - ((const Point*)b)->y;
	}
	return res;
}

float sqr(const int x)
{
	return (float)(x * x);
}

float distance(const Point p1, const Point p2)
{
	return (float)sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y));
}