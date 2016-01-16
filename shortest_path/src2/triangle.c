#include "wgraph.h"
#include "triangle.h"
#include <stdlib.h>
#include <stdio.h>

void add_to_list(triangleList *triangleList, triangle triangle)
{
	triangleList->triangles[triangleList->numTriangles] = triangle;
	triangleList->numTriangles++;
}

void read_triangles(triangleList *triangleList, const char *filename)
{
	triangleList->numTriangles = 0;
	FILE *fr;

	char line[1024];
	fr = fopen(filename, "rt");
	if (fr != NULL)
	{
		while (fgets(line, sizeof(line) / sizeof(char), fr) != NULL)
		{
			point p1;
			point p2;
			point p3;
			triangle triangle;
			sscanf(line, "T (%d, %d) (%d, %d) (%d, %d)", &p1.x, &p1.y, &p2.x, &p2.y, &p3.x, &p3.y);

			triangle.points[0] = p1;
			triangle.points[1] = p2;
			triangle.points[2] = p3;
			add_to_list(triangleList, triangle);
		}
		fclose(fr);
	}
}

// verify if point is in "positive" or "negative" halfplane
int classify_point(const point p, const point half_plane_point1, const point half_plane_point2)
{
	int A1 = half_plane_point2.y - half_plane_point1.y;
	int B1 = half_plane_point1.x - half_plane_point2.x;
	int C1 = -A1 * half_plane_point1.x - B1 * half_plane_point1.y;

	const int f1 = A1 * p.x + B1 * p.y + C1;
	return sign(f1);
}

bool is_inside_triangle(const point p, const triangle _triangle)
{
	const int sum =
		classify_point(p, _triangle.points[0], _triangle.points[1])
		+ classify_point(p, _triangle.points[1], _triangle.points[2])
		+ classify_point(p, _triangle.points[2], _triangle.points[0]);
	if (3 == sum || -3 == sum)
	{
		return TRUE;
	}
	return FALSE;
}
