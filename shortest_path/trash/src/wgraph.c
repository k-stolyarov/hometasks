#include "bool.h"
#include "wgraph.h"
#include "triangle.h"
#include <math.h>

#include <stdio.h>

initialize_graph(graph *g)
{
	int i;
	g -> nvertices = 0;

	for (i=0; i<=MAXV; i++) g->degree[i] = 0;
}

int sqr(const int x)
{
	return x * x;
}

double get_distance(const point src, const point dst)
{
	return sqrt((double)(sqr(src.x - dst.x) + sqr(src.y - dst.y)));
}

int sign(const int x)
{
	return x > 0 ? 1 : (0 == x ? 0 : -1);
}

bool check_intersection(const cut a, const cut b)
{
	int A1 = a.p2.y - a.p1.y;
	int B1 = a.p1.x - a.p2.x;
	int C1 = -A1 * a.p1.x - B1 * a.p1.y;

	int A2 = b.p2.y - b.p1.y;
	int B2 = b.p1.x - b.p2.x;
	int C2 = -A2 * b.p1.x - B2 * b.p1.y;

	int f1 = A1 * b.p1.x + B1 * b.p1.y + C1;
	int f2 = A1 * b.p2.x + B1 * b.p2.y + C1;
	int f3 = A2 * a.p1.x + B2 * a.p1.y + C2;
	int f4 = A2 * a.p2.x + B2 * a.p2.y + C2;

	if (sign(f1) * sign(f2) < 0 && sign(f3) * sign(f4) < 0)
	{
		return TRUE;
	}

	return FALSE;
}

bool intersects(const point p1, const point p2, const triangleList * triangles)
{
	int n;
	cut cut_to_check;
	cut_to_check.p1 = p1;
	cut_to_check.p2 = p2;

	for (n = 0; n < triangles->numTriangles; n++)
	{
		{
			cut triangle_cut;
			triangle_cut.p1 = triangles->triangles[n].points[0];
			triangle_cut.p2 = triangles->triangles[n].points[1];
			if (check_intersection(cut_to_check, triangle_cut) == TRUE)
			{
				return TRUE;
			}
		}
		{
			cut triangle_cut;
			triangle_cut.p1 = triangles->triangles[n].points[0];
			triangle_cut.p2 = triangles->triangles[n].points[2];
			if (check_intersection(cut_to_check, triangle_cut) == TRUE)
			{
				return TRUE;
			}
		}
		{
			cut triangle_cut;
			triangle_cut.p1 = triangles->triangles[n].points[1];
			triangle_cut.p2 = triangles->triangles[n].points[2];

			if (check_intersection(cut_to_check, triangle_cut) == TRUE)
			{
				return TRUE;
			}
		}
		{
			// \todo possibly if section is inside a triangle then forbid such edges.
			// if we are here we do not have any crosses with triangles.
			// But according to the task if section is inside a triangle then this path edge is not allowed.
		}
	}
	return FALSE;
}

void insert_edge(
	graph * const g,
	const int p1,		// edge start point
	const int p2,		// edge end point
	const double w)		// edge weight
{
	if (g->degree[p1] > MAXDEGREE)
	{
		printf("\nWarning: insertion(%d,%d) exceeds degree bound\n", p1, p2);
	}
	else
	{
		g->edges[p1][g->degree[p1]].weight = w;
		g->edges[p1][g->degree[p1]].endpoint_index = p2;
		++g->degree[p1];
	}
}

void build_graph(
	graph * g,                               /* graph to initialize */
	const point src,
	const point dst,
	const triangleList * triangles)
{
	int i = 0;
	int j = 0;

	initialize_graph(g);

	g->nvertices = triangles->numTriangles * 3 + 2;

	// add start end end points
	{
		g->points[j] = src;
		++j;
	}
	{
		g->points[j] = dst;
		++j;
	}

	// add traingle points
	for (i = 0; i < triangles->numTriangles; i++)
	{
		int k = 0;
		for (k = 0; k < 3; ++k)
		{
			g->points[j] = triangles->triangles[i].points[k];
			++j;
		}
	}
	
	// connect all points with edges
	for (i = 0; i < g->nvertices; ++i)
	{
		for (j = i + 1; j < g->nvertices; ++j)
		{
			if (FALSE == intersects(g->points[i], g->points[j], triangles))
			{
				const double distance = get_distance(g->points[i], g->points[j]);
				insert_edge(g, i, j, distance);
				insert_edge(g, j, i, distance);
			}			
		}
	}
}

print_graph(const graph *g)
{
	int i,j;							/* counters */

	for (i = 0; i < g->nvertices; ++i) {
		printf("\n%d: ",i);
		for (j = 0; j < g->degree[i]; ++j)
			printf(" %d", g->edges[i][j].endpoint_index);
		printf("\n");
	}
}





