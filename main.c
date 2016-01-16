#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bool.h"
#include "structures.h"
#include "ui.h"

float getWeight(int x1, int y1, int x2, int y2)
{
    int diffx = x1 - x2;
    int diffy = y1 - y2;
    int diffx_sqr = pow(diffx,2);
    int diffy_sqr = pow(diffy, 2);
    float weight = sqrt(diffx_sqr + diffy_sqr);
    return weight;
}

bool containsVertex(Vertex *vertex, Vertex *vertexArray)
{
	Vertex *tmpVertex = vertexArray;
	while(tmpVertex != NULL)
	{
		if(tmpVertex == vertex)
			return true;

		tmpVertex = tmpVertex->next;
	}
	return false;
}

bool containsEdge(Edge *edge, Vertex *vertexArray)
{
	Vertex *tmpVertex = vertexArray;
	while(tmpVertex != NULL)
	{
		Edge *currentEdge = tmpVertex->edges;
		while(currentEdge != NULL)
		{
			if(currentEdge == edge)
				return true;

			currentEdge = currentEdge->next;
		}

		tmpVertex = tmpVertex->next;
	}
	return false;
}

int main(int argc, char** argv)
{
	initializeWindow(argc, argv, 800, 800);

	Vertex* VertexArray = NULL;
	Line *LineHorArray = NULL;
	Line *LineVertArray = NULL;

	char filename[255]="input";
	printf("Enter file name: \n");
	//scanf("%s", filename);
	readInputLines(filename, &LineHorArray, & LineVertArray);

	///////build graph///////

	// create array of all vertex
	Edge *edge;
	Line *lineTmpH = LineHorArray;
	Vertex *vertex;

	int p = 0;
	while(lineTmpH != NULL)
	{
		Line *lineTmpV = LineVertArray;
		while(lineTmpV != NULL)
		{
			if(doIntersect(lineTmpH, lineTmpV))
			{
				printf("%d\n", p++);
				vertex = malloc(sizeof(Vertex));
				vertex->a = lineTmpV;
				vertex->b = lineTmpH;
				vertex->X = lineTmpV->p1.x;
				vertex->Y = lineTmpH->p1.y;
				vertex->next = NULL;
				vertex->edges = NULL;
				if(!containsVertex(vertex, VertexArray))
				{
					if(VertexArray == NULL)
					{
						VertexArray = vertex;
					}
					else
					{
						vertex->next = VertexArray;
						VertexArray = vertex;
					}
				}
				else printf("duplicate vertex\n");
			}
			lineTmpV = lineTmpV->next;
		}
		lineTmpH = lineTmpH->next;
	}

	// create edges
	Vertex *tmpVertex;
	tmpVertex = VertexArray;
	Vertex *tmpNextVertex;
	while(tmpVertex != NULL)
	{
		tmpNextVertex = tmpVertex->next;
		while(tmpNextVertex != NULL)
		{
			// check if we can move from one vertex to another
			if(tmpVertex != tmpNextVertex)
			{
				if(tmpVertex->a == tmpNextVertex->a || tmpVertex->a == tmpNextVertex->b
				|| tmpVertex->b == tmpNextVertex->a || tmpVertex->b == tmpNextVertex->b)
				{
					edge = malloc(sizeof(Edge));
					edge->dst =  tmpNextVertex;
					edge->src = tmpVertex;
					edge->weight = getWeight(tmpVertex->X, tmpVertex->Y, tmpNextVertex->X, tmpNextVertex->Y);
					edge->next = NULL;
					edge->included = false;

					if(!containsEdge(edge, VertexArray))
					{
						if(tmpVertex->edges == NULL)
						{
							tmpVertex->edges = edge;
						}
						else
						{
							edge->next = tmpVertex->edges;
						}
					}
					else printf("duplicate edge\n");

					edge = malloc(sizeof(Edge));
					edge->dst = tmpVertex;
					edge->src = tmpNextVertex;
					edge->weight = getWeight(tmpNextVertex->X, tmpNextVertex->Y, tmpVertex->X, tmpVertex->Y);
					edge->next = NULL;
					edge->included = false;

					if(!containsEdge(edge, VertexArray))
					{
						if(tmpNextVertex->edges == NULL)
						{
							tmpNextVertex->edges = edge;
						}
						else
						{
							edge->next = tmpNextVertex->edges;
							tmpNextVertex->edges = edge;
						}
					}
					else printf("duplicate edge\n");
				}
			}
			tmpNextVertex = tmpNextVertex->next;
		}
		edge = tmpVertex->edges;
		/*tmpVertex->edgeCount = 0;
		while(edge != NULL)
		{
			tmpVertex->edgeCount++;
			edge = edge->next;
		}*/

		tmpVertex = tmpVertex->next;
	}


	//MST
	Edge *mst = NULL;
	mst = primMST(VertexArray);

	displayResults(VertexArray, LineHorArray, LineVertArray, mst);
	
	exit(0);
}
