#include "structures.h"
#include "bool.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void append_line_to_list(Line * const line_to_add, Line ** const list_head)
{
	line_to_add->next = (*list_head);
	*list_head = line_to_add;
}

bool onSegment(int px, int py, int qx, int qy, int rx, int ry)
{
	if (qx <= max(px, rx) && qx >= min(px, rx) && qy <= max(py, ry) && qy >= min(py, ry))
		return true;
	return false;
}

int orientation(int px, int py, int qx, int qy, int rx, int ry)
{
	int val = (qy - py) * (rx - qx) - (qx - px) * (ry - qy);
	if (val == 0) return 0;
	return (val > 0) ? 1 : 2;
}

bool doIntersectCoords(int p1x, int p1y, int q1x, int q1y, int p2x, int p2y, int q2x, int q2y)
{
	int o1 = orientation(p1x, p1y, q1x, q1y, p2x, p2y);
	int o2 = orientation(p1x, p1y, q1x, q1y, q2x, q2y);
	int o3 = orientation(p2x, p2y, q2x, q2y, p1x, p1y);
	int o4 = orientation(p2x, p2y, q2x, q2y, q1x, q1y);
	if (o1 != o2 && o3 != o4)
		return true;
	if (o1 == 0 && onSegment(p1x, p1y, p2x, p2y, q1x, q1y)) return true;
	if (o2 == 0 && onSegment(p1x, p1y, q2x, q2y, q1x, q1y)) return true;
	if (o3 == 0 && onSegment(p2x, p2y, p1x, p1y, q2x, q2y)) return true;
	if (o4 == 0 && onSegment(p2x, p2y, q1x, q1y, q2x, q2y)) return true;
	return false;
}

bool doIntersect(const Line * const l1, const Line * const l2)
{
	return doIntersectCoords(l1->p1.x, l1->p1.y, l1->p2.x, l1->p2.y, l2->p1.x, l2->p1.y, l2->p2.x, l2->p2.y);
}

void readInputLines(const char * const filename, Line ** const horizontal_lines, Line ** const vertical_lines)
{
	FILE *fr = fopen(filename, "rt");
	char row[80];

	while (fgets(row, 80, fr) != NULL)
	{
		Line *line;
		char orient;
		int a, b, c;
		sscanf(row, "%c %d, %d, %d", &orient, &a, &b, &c);
		line = calloc(1, sizeof(Line));
		line->next = NULL;
		if (orient == 'h') {
			line->p1.x = b;
			line->p1.y = a;
			line->p2.x = c;
			line->p2.y = a;

			append_line_to_list(line, horizontal_lines);
		}
		else {
			line->p1.x = a;
			line->p1.y = b;
			line->p2.x = a;
			line->p2.y = c;

			append_line_to_list(line, vertical_lines);
		}
	}
}

bool are_verticies_equal(const Vertex * const v1, const Vertex * const v2)
{
	return (v1->a == v2->a && v1->b == v2->b) || (v1->a == v2->b && v1->b == v2->a);
}

float getDistance(const Vertex * const v1, const Vertex * const v2)
{
	int diffx = v1->X - v2->X;
	int diffy = v1->Y - v2->Y;
	return (float)(sqrt(diffx * diffx + diffy * diffy));
}

bool are_edges_equal(const Edge * const e1, const Edge * const e2)
{
	return e1->src == e2->src && e1->dst == e2->dst;
}