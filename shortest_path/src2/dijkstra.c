#include <stdlib.h>
#include "bool.h"
#include "wgraph.h"
#include "triangle.h"

void dijkstra(
	const graph *g,
	const int start,
	int last_edge_beginning[]) // last_edge_beginning
{
	int i;				/* counters */
	bool visited[MAXV];
	double distance_from_start[MAXV];
	const double MAX_WEIGHT = 1e100;
	
	for (i = 0; i < g->nvertices; ++i) {
		visited[i] = FALSE;
		distance_from_start[i] = MAX_WEIGHT;
		last_edge_beginning[i] = 0;
	}
	for (i = 0; i < g->degree[start]; ++i)
	{
		distance_from_start[g->edges[start][i].endpoint_index] = g->edges[start][i].weight;
	}

	distance_from_start[start] = 0;
	visited[start] = TRUE;

	while (1)
	{
		int min_index = -1;
		double min_weight = MAX_WEIGHT;
		for (i = 0; i < g->nvertices; ++i)
		{
			if (FALSE == visited[i] && min_weight > distance_from_start[i])
			{
				min_index = i;
				min_weight = distance_from_start[i];
			}
		}
		if (-1 == min_index)
		{
			// all verticies has been visited
			break;
		}
		visited[min_index] = TRUE;

		for ( i = 0; i < g->degree[min_index]; ++i)
		{
			const int edge_end = g->edges[min_index][i].endpoint_index;
			const double weight = g->edges[min_index][i].weight;
			if (visited[edge_end] == FALSE && distance_from_start[edge_end] >(distance_from_start[min_index] + weight))
			{
				distance_from_start[edge_end] = distance_from_start[min_index] + weight;
				last_edge_beginning[edge_end] = min_index;
			}
		}
	}
}


void initialize_path(path *_path)
{
	int i;
	_path->pointNumber = 0;
	for (i = 0; i < MAXV; i++)
	{
		_path->points[i] = -1;
	}
}

void add_to_path(path *_path, const int point_index)
{
	_path->points[_path->pointNumber] = point_index;
	++_path->pointNumber;
}

void build_path(
	const graph *g,
	const int start,
	const int end,
	path *_path)
{
	int last_edge_beginning[MAXV];
	dijkstra(g, start, last_edge_beginning);

	// traverse path to the selected vertex
	initialize_path(_path);
	int vertex = end;
	while (vertex != start)
	{
		add_to_path(_path, vertex);
		vertex = last_edge_beginning[vertex];
	}
	add_to_path(_path, start);
}


