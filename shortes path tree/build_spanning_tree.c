#include "build_spanning_tree.h"
#include "structures.h"
#include <memory.h>
#include <stdlib.h>
#include <math.h>
#include "approximation.h"

typedef struct SpanningTreeEdgeStruct SpanningTreeEdge;
struct SpanningTreeEdgeStruct
{
	const Line * l1;
	int l1_index;
	const Line * l2;
	int l2_index;
	Point cross;

	int weight;
};

int compareEdges (const void * a, const void * b)
{
	return ((SpanningTreeEdge*)a)->weight - ((SpanningTreeEdge*)b)->weight;
}

int distance(const int x1, const int y1, const int x2, const int y2)
{
	const int diffx = x1 - x2;
	const int diffy = y1 - y2;
	return (int)(sqrt(diffx * diffx + diffy * diffy));
}

int distanceBetweenPoints(const Point p1, const Point p2)
{
	return distance(p1.x, p1.y, p2.x, p2.y);
}

void constructEdgeGeometry(SpanningTreeEdge * edge, const Line * h, const Line * v)
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

// append point to the line. New line contains previous line and apppnded point.
Line * appendPointIntoLine(const Line * line, const Point p)
{
	Line *extended = malloc(sizeof(Line));
	*extended = * line;
	extended->p1.x = min(extended->p1.x, p.x);
	extended->p1.x = min(extended->p2.x, extended->p1.x);
	extended->p1.y = min(extended->p1.y, p.y);
	extended->p1.y = min(extended->p2.y, extended->p1.y);
	extended->p2.x = max(extended->p2.x, p.x);
	extended->p2.x = max(extended->p2.x, extended->p1.x);
	extended->p2.y = max(extended->p2.y, p.y);
	extended->p2.y = max(extended->p2.y, extended->p1.y);
	return extended;
}

void mergeConnectedComponents(int * connected_components, const int verticies_count, const int index1, const int index2)
{
	const int l1 = connected_components[index1];
	const int l2 = connected_components[index2];
	if (l1 != l2)
	{
		int j = 0;

		for(j = 0; j < verticies_count; ++j)
		{
			if (connected_components[j] == l1) {
				connected_components[j] = l2;
			}
		}
	}
}

bool process_line_connecting_components(
	int i,
	const int verticies_count,
	bool * are_directly_connected,
	int * directly_connected_components,
	const Line* * extended_lines,
	OutSpanningTreeEdge * spanning_tree,
	int *output_edge,
	int *weight)
{
	int min_edge_j = -1;
	int min_edge_k = -1;
	int min_edge_length = 0xFFFFFFFF;
	Line min_edge_line;

	int j = 0;
	for (j = 0; j < verticies_count; ++j)
	{
		if (are_directly_connected[j] && doIntersect(extended_lines[i], extended_lines[j]))
		{
			// line 'i' intersect some line 'j' from some tree.
			const Point p_j = getCrossPoint(extended_lines[j], extended_lines[i]);
			int k = 0;
			for (k = 0; k < verticies_count; ++k)
			{
				if (are_directly_connected[k] &&
					directly_connected_components[j] != directly_connected_components[k] &&
					doIntersect(extended_lines[i], extended_lines[k]))
				{
					// line 'i' intersect some line 'k' from another tree.
					const Point p_k = getCrossPoint(extended_lines[k], extended_lines[i]);
					const int edge_length = distanceBetweenPoints(p_k, p_j);

					if (edge_length < min_edge_length)
					{
						min_edge_j = j;
						min_edge_k = k;
						min_edge_length = edge_length;
						min_edge_line.p1 = p_j;
						min_edge_line.p1 = p_k;
					}
				}
			}
		}
	}
	if (min_edge_j != -1)
	{
		//Connect i and j components.
		//mark components as equal
		mergeConnectedComponents(directly_connected_components, verticies_count, min_edge_j, i);
		mergeConnectedComponents(directly_connected_components, verticies_count, min_edge_k, i);

		// to perform connection with one line two edges required: ij and ik
		Line * clipped_i_line = calloc(1, sizeof(Line));
		*clipped_i_line = min_edge_line;

		spanning_tree[*output_edge].l1 = extended_lines[min_edge_j];
		spanning_tree[*output_edge].l2 = clipped_i_line;
		spanning_tree[*output_edge].cross = min_edge_line.p1;
		++(*output_edge);

		spanning_tree[*output_edge].l1 = extended_lines[min_edge_k];
		spanning_tree[*output_edge].l2 = clipped_i_line;
		spanning_tree[*output_edge].cross = min_edge_line.p2;
		++(*output_edge);

		*weight += min_edge_length;
		// possibly needed to add some more edge from the original one.
		return true;
	}
	return false;
}

OutSpanningTree buildSpanningTree(const Line * horizontal, const Line * vertical)
{
	const Line *h = horizontal;

	// for every pair of linecuts append an edge that connect most distant edges of them.
	const int v_size = linesCount(vertical);
	const int h_size = linesCount(horizontal);
	const int verticies_count = h_size + v_size;

	SpanningTreeEdge * edges = calloc(h_size * v_size, sizeof(SpanningTreeEdge));
	int current_edge = 0;

	int h_index = 0;
	while (h != NULL) {
		const Line *v = vertical;
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
	const Line* * extended_lines = calloc(verticies_count, sizeof(const Line*));
	{
		const Line * h = horizontal;
		while (h != NULL) {
			line_length[i]	 = distanceBetweenPoints(h->p1, h->p2);
			extended_lines[i] = h;
			h = h->next;
			++i;
		}
		const Line *v = vertical;

		while (v != NULL) {
			line_length[i]	 = distanceBetweenPoints(v->p1, v->p2);
			extended_lines[i] = v;
			++i;
			v = v->next;
		}
	}

	// initially place every linecut in a separate connectivity component

	int * connected_components = calloc(verticies_count, sizeof(int));
	int * directly_connected_components = calloc(verticies_count, sizeof(int));
	bool * are_directly_connected = calloc(verticies_count, sizeof(bool));
	int * lines_usage = calloc(verticies_count, sizeof(int));

	for(i =0 ; i < verticies_count; ++i)
	{
		connected_components[i] = i;
		directly_connected_components[i] = i;
		are_directly_connected[i] = false;
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
			mergeConnectedComponents(connected_components, verticies_count, edges[i].l1_index, edges[i].l2_index);
			mergeConnectedComponents(directly_connected_components, verticies_count, edges[i].l1_index, edges[i].l2_index);
			are_directly_connected[edges[i].l1_index] = true;
			are_directly_connected[edges[i].l2_index] = true;
			++lines_usage[edges[i].l1_index];
			++lines_usage[edges[i].l2_index];
			{
				// for each of existing lines if it intersects with the extended one -> merge connected components
				Line *extended = appendPointIntoLine(edges[i].l1, edges[i].cross);
				int k =0 ;
				for(k =0 ; k < verticies_count;++k)
				{
					if (connected_components[k] != connected_components[edges[i].l1_index] && doIntersect(extended, extended_lines[k]))
					{
						mergeConnectedComponents(connected_components, verticies_count, edges[i].l1_index, k);
					}
					if (are_directly_connected[k] &&
						directly_connected_components[k] != directly_connected_components[edges[i].l1_index] &&
						doIntersect(extended, extended_lines[k]))
					{
						mergeConnectedComponents(directly_connected_components, verticies_count, edges[i].l1_index, k);
					}
				}
				extended_lines[edges[i].l1_index] = extended;

				extended = appendPointIntoLine(edges[i].l2, edges[i].cross);

				for(k =0 ; k < verticies_count;++k)
				{
					if (connected_components[k] != connected_components[edges[i].l2_index] && doIntersect(extended, extended_lines[k]))
					{
						mergeConnectedComponents(connected_components, verticies_count, edges[i].l2_index, k);
					}
					if (are_directly_connected[k] &&
						directly_connected_components[k] != directly_connected_components[edges[i].l2_index] &&
						doIntersect(extended, extended_lines[k]))
					{
						mergeConnectedComponents(directly_connected_components, verticies_count, edges[i].l2_index, k);
					}
				}
				extended_lines[edges[i].l2_index] = extended;
			}
			spanning_tree[output_edge].l1 = edges[i].l1;
			spanning_tree[output_edge].l2 = edges[i].l2;
			spanning_tree[output_edge].cross = edges[i].cross;
			weight += edges[i].weight;

			++output_edge;
		}
	}

	// substract edges length that are counted several times
	{
		for (i = 0; i < verticies_count; ++i)
		{
			if (lines_usage[i] > 1)
			{
				weight -= (lines_usage[i] - 1) * line_length[i];
			}
		}
	}

	// Now we have batch of trees that are indireclty connected. Connect them.
	// for each pair of trees exists an original line that connect them.

	for(i = 0 ; i < verticies_count; ++i)
	{
		if (are_directly_connected[i])
		{
			 // this line already present in some tree.
			continue;
		}
		while (process_line_connecting_components(i, verticies_count, are_directly_connected, directly_connected_components, extended_lines,spanning_tree, &output_edge, &weight))
		{
		}
	}

	OutSpanningTree result;
	result.edges = spanning_tree;
	result.edges_count = output_edge;
	result.weight = weight;

	return result;
}
