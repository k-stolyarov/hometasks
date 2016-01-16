#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <float.h>

#include "UI.h"
#include "Types.h"

#define MAX_HELD_KARP_POINTS 8
typedef struct {
	int points[MAX_HELD_KARP_POINTS];
	int size;
} Path;

typedef struct {
	float distances[MAX_HELD_KARP_POINTS][MAX_HELD_KARP_POINTS];
} Graph;

// Obtain amount of non zero bits in the given input number @i
unsigned int one_bits_count(unsigned int i)
{
	unsigned int res = 0;
	while (i > 0)
	{
		res += i & 1;
		i = i >> 1;
	}
	return res;
}

// check if bit @bit_index is set to 1 in mask @mask.
int is_bit_set(const int mask, const unsigned int bit_index)
{
	return 0 != (mask & (1 << bit_index));
}

// allocate and fill-in graph distances.
Graph * construct_graph(const Point *points, const unsigned int points_count)
{
	Graph * res = calloc(1, sizeof(Graph));
	unsigned int i = 0;
	unsigned int j = 0;
	for (i = 0; i < points_count; ++i)
	{
		for (j = 1; j < points_count; ++j)
		{
			res->distances[i][j] = res->distances[j][i] = distance(points[i], points[j]);
		}
	}
	return res;
}

// Deallocate graph.
void destroy_graph(Graph * graph)
{
	free(graph);
}

#define MAX_COMBINATIONS_COUNT (1 << (MAX_HELD_KARP_POINTS))
Path build_held_karp_path(const Point *points, const unsigned int points_count)
{
	Graph *graph = NULL;

	Path res;
	// encode subset of original verticies as bits in first index: i-th bit == 1 => point i is in subset.
	float C[MAX_COMBINATIONS_COUNT][MAX_HELD_KARP_POINTS];
	short best_points[MAX_COMBINATIONS_COUNT][MAX_HELD_KARP_POINTS];
	unsigned int set_size = 0;

	if (points_count <= 1)	{
		res.points[0] = 0;
		return res;
	}
	graph = construct_graph(points, points_count);

	C[1][0] = 0;

	for (set_size = 1; set_size < points_count; ++set_size) {
		unsigned int shifted_subset = 0;
		for (shifted_subset = 1; shifted_subset < (1 << (points_count - 1)); ++shifted_subset) {
			int end_point_index = 0;
			const int subset = (shifted_subset << 1) | 1;
			if (one_bits_count(shifted_subset) !=  set_size) {
				continue;
			}
			C[subset][0] = FLT_MAX;
			for (end_point_index = 1; end_point_index < points_count; ++end_point_index) {
				if (is_bit_set(subset, end_point_index)) {
					const int subset_without_endpoint = subset & (~(1 << end_point_index));
					int i = 0;
					C[subset][end_point_index] = FLT_MAX;
					for (i = 0; i < points_count; ++i) {
						if (is_bit_set(subset, i) && i != end_point_index) {
							const float curr_cost = C[subset_without_endpoint][i] + graph->distances[i][end_point_index];
							if (C[subset][end_point_index] > curr_cost) {
								C[subset][end_point_index] = curr_cost;
								best_points[subset][end_point_index] = i;
							}
						}
					}
				}
			}
		}
	}
	{
		// select last edge for making a loop
		const int all_subset = (0xFFFFFFFF >> (32 - points_count));
		
		int i = 0;
		C[all_subset][0] = FLT_MAX;
		best_points[all_subset][0] = -1;

		for (i = 1; i < points_count; ++i) {
			const float curr_cost = C[all_subset][i] + graph->distances[i][0];
			if (C[all_subset][0] > curr_cost) {
				C[all_subset][0] = curr_cost;
				best_points[all_subset][0] = i;
			}
		}
	}

	{
		// traverse back best points matrix to restore full path
		int current_subset = (0xFFFFFFFF >> (32 - points_count));
		int curr_traverse_point = 0;
		int path_point = 0;

		res.points[path_point] = best_points[current_subset][0];
		curr_traverse_point = res.points[path_point];
		
		for (path_point = 1; path_point < points_count; ++path_point) {
			res.points[path_point] = best_points[current_subset][curr_traverse_point];

			current_subset = current_subset & (~(1 << curr_traverse_point));
			curr_traverse_point = res.points[path_point];
		}
	}
	
	destroy_graph(graph);
	res.size = points_count;
	return res;
}

#define BUFFER_SIZE 1024

void read_points_from_file(const char * file_name, AllPoints *all_points)
{
	FILE *fp;
	char buffer[BUFFER_SIZE];

	if ((fp = fopen(file_name, "r")) == NULL)
	{
		printf(" could not open input file %s\n", file_name);
		exit(-1);
	}

	while (fgets(buffer, BUFFER_SIZE, fp))
	{
		// read input point coordinates
		int x = 0;
		int y = 0;
		sscanf(buffer, "%d %d", &x, &y);
		append_point(all_points, x, y);
	}
	fclose(fp);

	if (all_points->number_of_points >= MAX_POINTS)
	{
		printf(" too many points in file\n", file_name);
		exit(-1);
	}
}


int main(int argc, char **argv)
{
	AllPoints all_points;
	EdgesPath path;
	all_points.number_of_points = 0;
	path.size = 0;
	
#ifdef DRAW_RESULT
	{
		const int xBound = 800;
		const int yBound = 600;

		initializeWindow(argc, argv, xBound, yBound);
	}
#endif // #ifdef DRAW_RESULT

	if (argc >= 2) {
		read_points_from_file(argv[1], &all_points);
	} else {
#ifdef DRAW_RESULT
		read_from_screen(&all_points);
#endif // #ifdef DRAW_RESULT
	}

	qsort(all_points.points, all_points.number_of_points, sizeof(Point), compare_points);
	
	{
		const int hk_subtasks_count = (all_points.number_of_points / MAX_HELD_KARP_POINTS) + (all_points.number_of_points % MAX_HELD_KARP_POINTS ? 1 : 0);
		Path *pathes = calloc(hk_subtasks_count, sizeof(Path));
		int start_point = 0;
		int current_hk_part_index = 0;
		for (current_hk_part_index = 0; current_hk_part_index < hk_subtasks_count; ++current_hk_part_index) {
			int size = MAX_HELD_KARP_POINTS;
			int i = 0;
			Path partial_path;
			if (current_hk_part_index + 2 == hk_subtasks_count) {
				size = (all_points.number_of_points - start_point) / 2;
			}
			if (current_hk_part_index + 1 == hk_subtasks_count) {
				size = all_points.number_of_points - start_point;
			}
			partial_path = build_held_karp_path(all_points.points + start_point, size);
			for (i = 0; i < size; ++i) {
				partial_path.points[i] += start_point;
			}

			pathes[current_hk_part_index] = partial_path;
			start_point += size;
		}

		// sub optimally join partial pathes
		{
			// in first path we do not have any edges that are forbidden for removal to join HK-loops. 
			int forbidden_endge_start = -1;
			for (current_hk_part_index = 1; current_hk_part_index < hk_subtasks_count; ++current_hk_part_index) {
				float best_cost = FLT_MAX;
				int prev = 0;
				
				int prev_loop_edge_start = -1;
				int curr_loop_edge_start = -1;
				Edge connecting_edge_1;
				Edge connecting_edge_2;
				// for each allowed edge from previous loop
				for (prev = 0; prev < pathes[current_hk_part_index - 1].size; ++prev) {
					int curr = 0;
					const int prev_start_index = pathes[current_hk_part_index - 1].points[prev];
					const int prev_end_index = pathes[current_hk_part_index - 1].points[(prev + 1) % pathes[current_hk_part_index - 1].size];
					const Point prev_start = all_points.points[prev_start_index];
					const Point prev_end = all_points.points[prev_end_index];

					if (forbidden_endge_start == prev) {
						continue;
					}
					 // for each edge from current loop
					for (curr = 0; curr < pathes[current_hk_part_index].size; ++curr) {
						// check if removing both edges and connecting loops in this points will get optimal result

						const int curr_start_index = pathes[current_hk_part_index].points[curr];
						const int curr_end_index = pathes[current_hk_part_index].points[(curr + 1) % pathes[current_hk_part_index].size];
						const Point curr_start = all_points.points[curr_start_index];
						const Point curr_end = all_points.points[curr_end_index];
						const float removal_cost = distance(prev_start, prev_end) + distance(curr_start, curr_end);
						const float start_start_connect_cost = distance(prev_start, curr_start) + distance(prev_end, curr_end);
						const float start_end_connect_cost = distance(prev_start, curr_end) + distance(prev_end, curr_start);
						if (best_cost > start_start_connect_cost - removal_cost) {
							best_cost = start_start_connect_cost - removal_cost;
							
							prev_loop_edge_start = prev;
							curr_loop_edge_start = curr;

							connecting_edge_1.start = prev_start_index;
							connecting_edge_1.end = curr_start_index;

							connecting_edge_2.start = prev_end_index;
							connecting_edge_2.end = curr_end_index;
						}
						if (best_cost > start_end_connect_cost - removal_cost) {
							best_cost = start_end_connect_cost - removal_cost;

							prev_loop_edge_start = prev;
							curr_loop_edge_start = curr;

							connecting_edge_1.start = prev_start_index;
							connecting_edge_1.end = curr_end_index;

							connecting_edge_2.start = prev_end_index;
							connecting_edge_2.end = curr_start_index;
						}
					}
				}
				
				for (prev = 0; prev < pathes[current_hk_part_index - 1].size; ++prev) {
					// append all edges from previous loop except forbidden and selected for removal
					const int prev_start_index = pathes[current_hk_part_index - 1].points[prev];
					const int prev_end_index = pathes[current_hk_part_index - 1].points[(prev + 1) % pathes[current_hk_part_index - 1].size];
					if (forbidden_endge_start == prev || prev_loop_edge_start == prev) {
						continue;
					}
					append_edge(&path, prev_start_index, prev_end_index);
				}
				
				{
					// append two extra edges added instead of removed ones
					append_edge(&path, connecting_edge_1.start, connecting_edge_1.end);
					append_edge(&path, connecting_edge_2.start, connecting_edge_2.end);
				}
				forbidden_endge_start = curr_loop_edge_start;
			}

			{
				int prev = 0;
				for (prev = 0; prev < pathes[hk_subtasks_count - 1].size; ++prev) {
					// append all edges from last loop except forbidden one
					const int prev_start_index = pathes[hk_subtasks_count - 1].points[prev];
					const int prev_end_index = pathes[hk_subtasks_count - 1].points[(prev + 1) % pathes[hk_subtasks_count - 1].size];
					if (forbidden_endge_start == prev) {
						continue;
					}
					append_edge(&path, prev_start_index, prev_end_index);
				}
			}
		}

		free(pathes);
	}

#ifdef DRAW_RESULT
	// run message loop with displaying points and found path
	display_results(&all_points, &path);
#endif // #ifdef DRAW_RESULT
}