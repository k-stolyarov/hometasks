#include <stdlib.h>
#include <stdio.h>
#include "approximation.h"
#include "primMST.h"

bool containsVertex(Vertex *vertex, Vertex *vertexArray)
{
	Vertex *tmpVertex = vertexArray;
	while (tmpVertex != NULL) {
		if (are_verticies_equal(tmpVertex, vertex)) {
			return true;
		}
		tmpVertex = tmpVertex->next;
	}
	return false;
}

void appendEdge(Vertex * from, Vertex * to)
{
	Edge *edge = malloc(sizeof(Edge));
	edge->dst = to;
	edge->src = from;
	edge->weight = getDistance(from, to) + getDistanceToLine(from, from->a) + getDistanceToLine(to, to->a) ;
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
	Vertex* VertexArray = NULL;
	Line *lineTmpVertexOn = lines_verticies_form;
	Vertex *vertex;

	int p = 0;
	while (lineTmpVertexOn != NULL) {
		Line *lineTmpIntersectsVertex = lines_intersects_verticies_lines;
		while (lineTmpIntersectsVertex != NULL) {
			if (doIntersect(lineTmpVertexOn, lineTmpIntersectsVertex)) {
				printf("%d\n", p++);
				vertex = malloc(sizeof(Vertex));
				vertex->a = lineTmpIntersectsVertex;
				vertex->b = lineTmpVertexOn;
				Point p = getCrossPoint(lineTmpIntersectsVertex, lineTmpVertexOn);
				vertex->X = p.x;
				vertex->Y = p.y;
				vertex->next = NULL;
				vertex->edges = NULL;
				if (containsVertex(vertex, VertexArray)) {
					printf("Something went wrong: duplicate vertex");
					exit(-1);
				}
				if (VertexArray == NULL) {
					VertexArray = vertex;
				}
				else {
					vertex->next = VertexArray;
					VertexArray = vertex;
				}
			}
			lineTmpIntersectsVertex = lineTmpIntersectsVertex->next;
		}
		lineTmpVertexOn = lineTmpVertexOn->next;
	}

	// create edges
	Vertex *tmpVertex;
	tmpVertex = VertexArray;
	Vertex *tmpNextVertex;
	while (tmpVertex != NULL) {
		tmpNextVertex = tmpVertex->next;
		while (tmpNextVertex != NULL) {
			// check if we can move from one vertex to another
			if (tmpVertex->b == tmpNextVertex->b) {
				appendEdge(tmpVertex, tmpNextVertex);
				appendEdge(tmpNextVertex, tmpVertex);
			}
			tmpNextVertex = tmpNextVertex->next;
		}
		tmpVertex = tmpVertex->next;
	}

	Edge *mst = primMSF(VertexArray);
	return mst;
}
