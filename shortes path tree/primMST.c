#include "bool.h"
#include <limits.h>
#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include "primMST.h"

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
	Edge *edge = NULL;

	while(edges != NULL)
	{
		// check minimum and not already in mst
		if(!edges->included && (NULL == edge || edges->weight < edge->weight))
		{
			if( !any(mst, edges->dst) )
			{
				edge = edges;
			}
		}
		edges = edges->next;
	}

	return edge;
}

Edge* primMST(Vertex *graph, Edge* current_forest_part)
{
	Edge *edgesToCheck = NULL;
	Edge* mst = current_forest_part;
	Vertex *graphTmp = graph;

	int k = 0;
	while(graphTmp != NULL)
	{
		if (graphTmp->isInAnyMST) {
			printf("VErtex already in som MST. Something is wrong");
			exit(-1);
		}
		graphTmp->isInAnyMST = true;
		//add edges to edgesToCheck
		Edge *edgeToAdd;
		Edge *edge = graphTmp->edges;

		while(edge != NULL)
		{
			Edge *tmpEdge;
			tmpEdge = (Edge *)malloc(sizeof(Edge));
			tmpEdge->dst = edge->dst;
			tmpEdge->weight = edge->weight;
			tmpEdge->src = edge->src;
			tmpEdge->included = edge->included;
			tmpEdge->next = edgesToCheck;
			edgesToCheck = tmpEdge;
			
			edge = edge->next;
		}

		//find min weight edge src edgesToCheck
		edgeToAdd = minWeightEdge(edgesToCheck, mst);

		if(edgeToAdd == NULL)
		{
			// no more edges to add
			break;
		}

		// add min weight edge to mst
		edgeToAdd->included = true;

		Edge *mstTemp = malloc(sizeof(Edge));
		mstTemp->dst = edgeToAdd->dst;
		mstTemp->weight = edgeToAdd->weight;
		mstTemp->src = edgeToAdd->src;
		mstTemp->included = true;
		mstTemp->next = mst;

		mst = mstTemp;
		graphTmp = edgeToAdd->dst;
	}
	return mst;
}

Edge* primMSF(Vertex *graph)
{
	Edge* current_forest_part = NULL;
	{
		Vertex *v = graph;
		while(v != NULL)
		{
			v->isInAnyMST = false;
			v = v->next;
		}
	}
	{
		Vertex *v = graph;
		while(v != NULL)
		{
			current_forest_part = primMST(v, current_forest_part);
			// find next vertex that does not belong to any MST and start
			// construction of next tree in the forest with this vertex as start one.
			while(v != NULL && v->isInAnyMST)
			{
				v = v->next;
			}
		}
	}
	return current_forest_part;

}
