#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bool.h"
#include "structures.h"
#include "ui.h"

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
    return (val > 0)? 1: 2;
}

bool doIntersect(int p1x, int p1y, int q1x, int q1y, int p2x, int p2y, int q2x, int q2y)
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
	FILE *fr;
	int pointB,pointC,p3;
	char row[80];
	char orient;
	fr = fopen (filename, "rt");
	Line *line;
	int i = 0;
	while(fgets(row, 80, fr) != NULL)
	{
		sscanf (row, "%c %d, %d, %d", &orient, &pointB, &pointC, &p3);
		line  = malloc(sizeof(Line));
		if(orient == 'h')
			line->orientation=0;
		if(orient == 'v')
			line->orientation=1;
		line->pointA=pointB;
		line->pointB=pointC;
		line->pointC=p3;
		line->next = NULL;

		if(line->orientation ==0)
		{
			if(LineHorArray == NULL)
			{
				LineHorArray = line;
			}
			else
			{
				line->next = LineHorArray;
				LineHorArray = line;
			}
		}
		else
		{
			if(LineVertArray == NULL)
			{
				LineVertArray = line;
			}
			else
			{
				line->next = LineVertArray;
				LineVertArray = line;
			}
		}
	}
	///////build graph///////

	// create array of all vertex
	Edge *edge;
	Line *lineTmpH = malloc(sizeof(Line));
	Line *lineTmpV = malloc(sizeof(Line));
	Vertex *vertex;
	lineTmpH = LineHorArray;
int p = 0;
	while(lineTmpH != NULL)
	{
		lineTmpV = LineVertArray;
		while(lineTmpV != NULL)
		{
			if(doIntersect(lineTmpH->pointB, lineTmpH->pointA, lineTmpH->pointC, lineTmpH->pointA, lineTmpV->pointA, lineTmpV->pointB, lineTmpV->pointA, lineTmpV->pointC))
			{
				printf("%d\n", p++);
				vertex = malloc(sizeof(Vertex));
				vertex->a = lineTmpV;
				vertex->b = lineTmpH;
				vertex->X = lineTmpV->pointA;
				vertex->Y = lineTmpH->pointA;
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
