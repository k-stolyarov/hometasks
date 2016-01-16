#include "build_spanning_tree.h"
#include "structures.h"
#include <memory.h>
#include <stdlib.h>
#include <math.h>
#include "approximation.h"

typedef struct SpanningTreeEdgeStruct SpanningTreeEdge;
struct SpanningTreeEdgeStruct
{
	Line * l1;
	int l1_index;
	Line * l2;
	int l2_index;
	Point cross;

	int weight;
};

int compareEdges (const void * a, const void * b)
{
	return ((SpanningTreeEdge*)a)->weight - ((SpanningTreeEdge*)b)->weight;
}

static int distance(const int x1, const int y1, const int x2, const int y2)
{
	const int diffx = x1 - x2;
	const int diffy = y1 - y2;
	return (int)(sqrt(diffx * diffx + diffy * diffy));
}


void constructEdgeGeometry(SpanningTreeEdge * edge, Line * h, Line * v)
{
	const Point p = getCrossPoint(h, v);
	int length = 0;
	if (onSegment(h->p1.x, h->p1.y, p.x, p.y, h->p2.x, h->p2.y)) {
		length +=  distance(h->p1.x, h->p1.y, h->p2.x, h->p2.y);
	} else {
		const int d1 = distance(h->p1.x, h->p1.y, p.x, p.y);
		const int d2 = distance(h->p2.x, h->p2.y, p.x, p.y);
		length += max(d1, d2);
	}

	if (onSegment(v->p1.x, v->p1.y, p.x, p.y, v->p2.x, v->p2.y)) {
		length +=  distance(v->p1.x, v->p1.y, v->p2.x, v->p2.y);
	} else {
		const int d1 = distance(v->p1.x, v->p1.y, p.x, p.y);
		const int d2 = distance(v->p2.x, v->p2.y, p.x, p.y);
		length += max(d1, d2);
	}
	edge->l1 = h;
	edge->l2 = v;
	edge->cross = p;
	edge->weight = length;
}

Line * deduplicate(const Line * lines)
{
	Line * deduplicated = NULL;
	const Line * l = lines;
	while(l != NULL)
	{
		Line * existing = deduplicated;
		while(existing != NULL)
		{
			if ((existing->p1.x == existing->p2.x && existing->p1.x == l->p1.x) ||
				(existing->p1.y == existing->p2.y && existing->p1.y == l->p1.y))
			{
				break;
			}
			existing = existing->next;
		}
		if (NULL != existing)
		{
			existing->p1.x = min(existing->p1.x, l->p1.x);
			existing->p1.x = min(existing->p1.x, l->p2.x);
			existing->p1.y = min(existing->p1.y, l->p1.y);
			existing->p1.y = min(existing->p1.y, l->p2.y);

			existing->p2.x = max(existing->p2.x, l->p1.x);
			existing->p2.x = max(existing->p2.x, l->p2.x);
			existing->p2.y = max(existing->p2.y, l->p1.y);
			existing->p2.y = max(existing->p2.y, l->p2.y);
		}
		else
		{
			// no element to update with ddpllcated coordinate. Append new one
			existing = malloc(sizeof(Line));
			existing->next = deduplicated;
			deduplicated = existing;
			existing->p1.x = min(l->p1.x, l->p2.x);
			existing->p1.y = min(l->p1.y, l->p2.y);
			existing->p2.x = max(l->p1.x, l->p2.x);
			existing->p2.y = max(l->p1.y, l->p2.y);
		}

		l = l->next;
	}
	return deduplicated;
}

OutSpanningTree buildSpanningTree(const Line * in_horizontal, const Line * in_vertical)
{
	// remove linecuts that are on the same line.
	Line * horizontal = deduplicate(in_horizontal);
	Line * vertical = deduplicate(in_vertical);

	Line *h = horizontal;

	// for every pair of linecuts append an edge that connect most distant edges of them.
	const int v_size = linesCount(vertical);
	const int h_size = linesCount(horizontal);
	const int verticies_count = h_size + v_size;

	SpanningTreeEdge * edges = calloc(h_size * v_size, sizeof(SpanningTreeEdge));
	int current_edge = 0;

	int h_index = 0;
	while (h != NULL) {
		Line *v = vertical;
		int v_index = 0;
		while (v != NULL) {
			constructEdgeGeometry(edges + current_edge, h, v);
			edges[current_edge].l1_index = h_index;
			edges[current_edge].l2_index = h_size + v_index;
			++current_edge;
			++v_index;
			v = v->next;
		}
		h = h->next;
		++h_index;
	}
	// sort edges by weight
	qsort(edges, current_edge, sizeof(SpanningTreeEdge), &compareEdges);

	// calculate lines lenths
	int i = 0 ;
	int * line_length = calloc(verticies_count, sizeof(int));
	{
		h = horizontal;
		while (h != NULL) {
			line_length[i]	 = distance(h->p1.x, h->p1.y, h->p2.x, h->p2.y);
			h = h->next;
			++i;
		}
		Line *v = vertical;

		while (v != NULL) {
			line_length[i]	 = distance(v->p1.x, v->p1.y, v->p2.x, v->p2.y);
			++i;
			v = v->next;
		}
	}

	// initially place every linecut in a separate connectivity component

	int * connected_components = calloc(verticies_count, sizeof(int));
	int * lines_usage = calloc(verticies_count, sizeof(int));

	for(i =0 ; i < h_size + v_size; ++i)
	{
		connected_components[i] = i;
	}

	// for every edge add this to a result if linecuts are in differeet components and merge this components.
	OutSpanningTreeEdge * spanning_tree = calloc(verticies_count - 1, sizeof(OutSpanningTreeEdge));
	int weight = 0;
	int output_edge = 0;
	for(i = 0 ; i< current_edge; ++i)
	{
		const int l1 = connected_components[edges[i].l1_index];
		const int l2 = connected_components[edges[i].l2_index];
		if (l1 != l2)
		{
			int j = 0;

			for(j = 0; j < h_size + v_size; ++j)
			{
				if (connected_components[j] == l1) {
					connected_components[j] = l2;
				}
			}
			++lines_usage[edges[i].l1_index];
			++lines_usage[edges[i].l2_index];
			spanning_tree[output_edge].l1 = edges[i].l1;
			spanning_tree[output_edge].l2 = edges[i].l2;
			spanning_tree[output_edge].cross = edges[i].cross;
			weight += edges[i].weight;

			++output_edge;
		}
	}
	// substract edges leegth that are counted several times
	{
		for(i = 0 ; i < verticies_count; ++i)
		{
			if(lines_usage[i] > 1)
			{
				weight -= (lines_usage[i]-1) * line_length[i];
			}
		}
	}
	OutSpanningTree result;
	result.edges = spanning_tree;
	result.edges_count = verticies_count - 1;
	result.weight = weight;

	return result;
}
