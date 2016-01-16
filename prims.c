#include "bool.h"
#include <limits.h>
#include "structures.h"
#include <stdio.h>
#include <stdlib.h>

// function to check loops
bool any(Edge *mst, Vertex *vertex)
{
	Edge *mstTmp = mst;
	while(mstTmp != NULL)
	{
		if(mstTmp->src == vertex || mstTmp->dst == vertex)
			return true;
		mstTmp = mstTmp->next;
	}
	return false;
}

Edge* minWeightEdge(Edge *edges, Edge *mst)
{	//6.7.21.22.23.36.40.41.42.44.
	Edge *edge;
	edge = edges;
	Edge *tmp;
	bool changed = false;
	while(edges != NULL)
	{
		// check minimum and not already in mst
		if(edges->weight < edge->weight && !edges->included)
		{
			if(!any(mst, edges->src) || !any(mst, edges->dst))
			{
				edge = edges;
				tmp = edges;
				//changed = true;
			}
		}
		edges = edges->next;
	}
	if(changed)
	{
		tmp->included = true;
		edges = tmp;
	}
	edge->included = true;
	return edge;
}

Edge* primMST(Vertex *graph)
{
	Edge *edgesToCheck = NULL;
	Edge* mst = NULL;
	Vertex *graphTmp;
	graphTmp = graph;
	int d = 0;
	int k = 0;
	while(graphTmp != NULL)
	{
		//add edges to edgesToCheck
		Edge *edgeToAdd;
		Edge *edge = graphTmp->edges;
		//int i = graphTmp->edgeCount;

		while(edge != NULL)
		{
			Edge *tmpEdge;
			tmpEdge = (Edge *)malloc(sizeof(Edge));
			tmpEdge->dst = edge->dst;
			tmpEdge->weight = edge->weight;
			tmpEdge->src = edge->src;
			tmpEdge->included = edge->included;
			tmpEdge->next = NULL;

			if (edgesToCheck== NULL)
			{
				edgesToCheck = tmpEdge;
				edgesToCheck->next = NULL;
			}
			else
			{
				tmpEdge->next = edgesToCheck;
				edgesToCheck = tmpEdge;
			}

			edge = edge->next;
			//i--;
		}
		//find min weight edge src edgesToCheck
		edgeToAdd = minWeightEdge(edgesToCheck, mst);
		printf("%d | src(%d;%d) dst(%d;%d) weight = %f included = %d\n", d++, edgeToAdd->src->X, edgeToAdd->src->Y, edgeToAdd->dst->X, edgeToAdd->dst->Y, edgeToAdd->weight, edgeToAdd->included);

		// add min weight edge to mst
		if(edgeToAdd->included)
		{
			printf("! %d | src(%d;%d) dst(%d;%d) weight = %f included = %d\n", k++, edgeToAdd->src->X, edgeToAdd->src->Y, edgeToAdd->dst->X, edgeToAdd->dst->Y, edgeToAdd->weight, edgeToAdd->included);
			Edge *mstTemp = malloc(sizeof(Edge));
			mstTemp->dst = edgeToAdd->dst;
			mstTemp->weight = edgeToAdd->weight;
			mstTemp->src = edgeToAdd->src;
			mstTemp->included = true;
			//mstTemp->next = NULL;

			if (mst== NULL)
			{
				mst = mstTemp;
				mst->next = NULL;
			}
			else
			{
				mstTemp->next = mst;
				mst = mstTemp;
			}

		}
		graphTmp = graphTmp->next;
	}
	return mst;
}
