#ifndef __STRUCTURES_H_INCLUDED__
#define __STRUCTURES_H_INCLUDED__
#include "bool.h"

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

typedef struct LineStruct Line;
typedef struct VertexStruct Vertex;
typedef struct EdgeStruct Edge;

typedef struct
{
	int x;
	int y;
} Point;

struct LineStruct
{
	Point p1;
	Point p2;

    Line* next;
};

void readInputLines(const char * const filename, Line ** const horizontal_lines, Line ** const vertical_lines);
void append_line_to_list( Line * const line_to_add, Line ** const list_head);
bool doIntersect(const Line * const l1, const Line * const l2);

struct VertexStruct
{
    Line *a;
    Line *b;
    int X;
    int Y;
    Vertex *next;
    Edge *edges;
    int edgeCount;
};
bool are_verticies_equal(const Vertex * const v1, const Vertex * const v2);
// calculate distance between two verticies.
float getDistance(const Vertex * const v1, const Vertex * const v2);

struct EdgeStruct
{
    Vertex *dst;
    Vertex *src;
    Edge *next;
    float weight;
    int included;
};

bool are_edges_equal(const Edge * const e1, const Edge * const e2);

#endif // #ifndef __STRUCTURES_H_INCLUDED__