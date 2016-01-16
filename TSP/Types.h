#pragma once

#define MAX_POINTS 500

typedef struct {
	int x;
	int y;
} Point;

typedef struct {
	Point points[MAX_POINTS];
	int number_of_points;
} AllPoints;

typedef struct {
	int start;
	int end;
} Edge;

typedef struct {
	Edge edges[MAX_POINTS];
	int size;
} EdgesPath;

void append_point(AllPoints *all_points, int x, int y);
void append_edge(EdgesPath *path, int start, int end);
int compare_points(const void * a, const void * b);
float distance(const Point p1, const Point p2);