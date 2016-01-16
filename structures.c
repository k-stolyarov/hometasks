#include "structures.h"
#include "bool.h"
#include <stdlib.h>
#include <stdio.h>

void append_line_to_list(Line * const line_to_add, Line ** const list_head)
{
	if (*list_head != NULL)
	{
		(*list_head)->next = line_to_add;
	}
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
