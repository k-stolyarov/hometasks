/* compiles with command line  gcc xlibdemo.c -lX11 -lm -L/usr/X11R6/lib */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <memory.h>

void top_sort(int n, int out[][4], int sequence[]); /* function prototype */

#define MAX_POINTS 1000
#define BUFFER_SIZE 1024
int main(int argc, char **argv)
{
	int outcoming_edges[MAX_POINTS][4];
	int sorted_verticies[MAX_POINTS];
	int number_of_points = 0;
	char buffer[BUFFER_SIZE];

	FILE *fp;
	if (argc < 2)
	{
		printf(" needs input file name as command line argument\n");
		exit(-1);
	}
	if ((fp = fopen(argv[1], "r")) == NULL)
	{
		printf(" could not open input file %s\n", argv[1]);
		exit(-1);
	}

	while (fgets(buffer, BUFFER_SIZE, fp) && (number_of_points < 999))
	{
		// read up to 4 outgoing edges
		int actual_edges_count = sscanf(buffer, "%d %d %d %d",
			&outcoming_edges[number_of_points][0],
			&outcoming_edges[number_of_points][1],
			&outcoming_edges[number_of_points][2],
			&outcoming_edges[number_of_points][3]);

		// fill all unread edges as absent
		for (; actual_edges_count < 4; ++actual_edges_count)
		{
			outcoming_edges[number_of_points][actual_edges_count] = -1;
		}
		number_of_points += 1;
	}
	if (number_of_points == 0)
	{
		printf(" did not find any points in file\n", argv[1]);
		exit(-1);
	}
	else if (number_of_points >= 999)
	{
		printf(" too many points in file\n", argv[1]);
		exit(-1);
	}
	else
		printf(" found %d points\n", number_of_points);

	top_sort(number_of_points, outcoming_edges, sorted_verticies);
	if (sorted_verticies[0] < 0)
	{
		printf("Impossible to sort the entered graph.");
	}
	else
	{
		int i = 0;
		printf("Topologically sorted verticies of the input graph:\n");
		for (i = 0; i < number_of_points; ++i)
		{
			printf("%d ", sorted_verticies[i]);
		}
	}
	exit(0);
}

#define NOT_VISITED_VERTEX 0
#define CHILDREN_VISIT_IN_PROGRESS 1
#define ALL_CHILDREN_VISITED 2

#define NO_CYCLE 0
#define HAS_CYCLE 1

int dfs(int vertex, int edges[][4], int colors[], int stack[], int* stack_size)
{
	if (colors[vertex] == CHILDREN_VISIT_IN_PROGRESS)
	{
		// While traversing graph using recursive dfs algorithm found a cycle.
		return HAS_CYCLE;
	}

	if (colors[vertex] == ALL_CHILDREN_VISITED)
	{
		// All children of this vertex was already visited and placed to output stack.
		// The only possible pass that leads here is from top_sort function.
		// No cycles. 
		return NO_CYCLE;
	}
	
	// Mark vertex as "visiting child is in process"
	colors[vertex] = CHILDREN_VISIT_IN_PROGRESS;

	{
		// Traverse all children recursively.
		int i = 0;
		for (i = 0; i < 4; i++)
		{
			if (edges[vertex][i] < 0)
			{
				continue;
			}

			// run deeper to the child
			if (HAS_CYCLE == dfs(edges[vertex][i], edges, colors, stack, stack_size))
			{
				return HAS_CYCLE;
			}
		}
	}
	
	{
		// all children were visited. Mark vertex as "black" and push it into stack.
		stack[*stack_size] = vertex;
		++(*stack_size);

		colors[vertex] = ALL_CHILDREN_VISITED;
	}

	return NO_CYCLE;
}

void top_sort(int n, int out[][4], int sequence[])
{
	int i = 0;
	int *colors = calloc(n, sizeof(int));
	int *stack = calloc(n, sizeof(int));
	int stack_size = 0;

	for (i = 0; i < n; ++i)
	{
		colors[i] = NOT_VISITED_VERTEX;
	}

	// traverse over all possible start verticies and build topological sort for 
	// all verticies that are reachable from current vertex. That is required 
	// because several connected components are allowed in the input graph.
	for (i = 0; i < n; ++i)
	{
		const int has_cycle = dfs(i, out, colors, stack, &stack_size);
		if (has_cycle == HAS_CYCLE)
		{
			sequence[0] = -1;
			free(colors);
			free(stack);
			return;
		}
	}

	// In stack verticies are listed in the reversed order.
	for (i = 0; i < n; ++i)
	{
		sequence[i] = stack[n - i - 1];
	}

	free(colors);
	free(stack);
}