#ifndef __WGRAPH_H_INC__
#define __WGRAPH_H_INC__
#include "triangle.h"

#define	MAXV		3002		/* maximum number of vertices */
#define MAXDEGREE	(MAXV - 1)	/* maximum outdegree of a vertex */

typedef struct {
	point p1;
	point p2;
} cut;

typedef struct {
	int endpoint_index;    /* point index the edge points to */
	double weight;			/* edge weight */
} edge;

typedef struct {
	point points[MAXV];						/* verticies */
	edge edges[MAXV][MAXDEGREE];	/* adjacency info */
	int degree[MAXV];				/* outdegree of each vertex */
	int nvertices;					/* number of vertices in the graph */
} graph;

typedef struct {
	int points[MAXV];			/* path vertex indicies */
	int pointNumber;
} path;

void build_graph(
	graph * g,
	const point src,
	const point dst,
	const triangleList *triangles);

void build_path(
	const graph *g,
	const int start,
	const int end,
	path *_path);

#endif // __WGRAPH_H_INC__

