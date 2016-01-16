#include <stdlib.h>
#include <stdio.h>
#include "approximation.h"
#include "primMST.h"

void appendEdge(Vertex * from, Vertex * to)
{
	Edge *edge = malloc(sizeof(Edge));
	edge->dst = to;
	edge->src = from;
	edge->weight = getDistance(from, to);
	edge->included = false;

	edge->next = from->edges;
	from->edges = edge;
}

void fillEqualCoordinate(Point * rv, const Line * l)
{
	if (l->p1.x == l->p2.x)
	{
		rv->x = l->p1.x;
	}
	if (l->p1.y == l->p2.y)
	{
		rv->y = l->p1.y;
	}
}

Point getCrossPoint(const Line * l1, const Line * l2)
{
	Point p;
	fillEqualCoordinate(&p, l1);
	fillEqualCoordinate(&p, l2);
	return p;
}

Edge * buildLowerBoundApproximationPart(Line * lines_verticies_form, Line * lines_intersects_verticies_lines)
{
	///////build graph///////

	// create array of all vertex
	
	const int verticies_count = linesCount(lines_verticies_form);
	Vertex* VertexArray = calloc(verticies_count, sizeof(Vertex));
	{
		// create verticies
		Line * l = lines_verticies_form;
		int i = 0;
		while (l != NULL) {
			VertexArray[i].b = l;
			VertexArray[i].edges = NULL;
			if (i + 1 < verticies_count) {
				VertexArray[i].next = VertexArray + i + 1;
			}
			++i;
			l = l->next;
		}
	}
	{
		// create edges
		int i = 0;
		int j = 0;
		for (i = 0; i < verticies_count; ++i)
		{
			for (j = i + 1; j < verticies_count; ++j)
			{
				Line *cross_line = lines_intersects_verticies_lines;
				while (cross_line != NULL) {
					if (doIntersect(cross_line, VertexArray[i].b) && doIntersect(cross_line, VertexArray[j].b)) {
						appendEdge(VertexArray + i, VertexArray + j);
						appendEdge(VertexArray + j, VertexArray + i);
					}
					cross_line = cross_line->next;
				}
			}
		}
	}

	Edge *mst = primMSF(VertexArray);
	return mst;
}
