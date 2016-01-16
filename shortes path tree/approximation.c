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

bool containsEdge(Edge *edge, Vertex *vertexArray)
{
	Vertex *tmpVertex = vertexArray;
	while (tmpVertex != NULL) {
		Edge *currentEdge = tmpVertex->edges;
		while (currentEdge != NULL) {
			if (are_edges_equal(currentEdge, edge)) {
				return true;
			}
			currentEdge = currentEdge->next;
		}
		tmpVertex = tmpVertex->next;
	}
	return false;
}

void appendEdge(Vertex * from, Vertex * to)
{
	Edge *edge = malloc(sizeof(Edge));
	edge->dst = from;
	edge->src = to;
	edge->weight = getDistance(from, to);
	edge->next = NULL;
	edge->included = false;

	if (from->edges != NULL) {
		edge->next = from->edges;
	}
	from->edges = edge;
}

Edge * buildApproximation(Line * lines_verticies_form, Line * lines_intersects_verticies_lines)
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
				vertex->X = lineTmpIntersectsVertex->p1.x;
				vertex->Y = lineTmpVertexOn->p1.y;
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

				if (containsEdge(tmpVertex->edges, VertexArray) || containsEdge(tmpNextVertex->edges, VertexArray))
				{
					printf("Something went wrong: duplicate edge.");
					exit(-1);
				}
			}
			tmpNextVertex = tmpNextVertex->next;
		}
		tmpVertex = tmpVertex->next;
	}

	Edge *mst = primMST(VertexArray);
	return mst;
}