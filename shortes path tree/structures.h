#ifndef __STRUCTURES_H_INCLUDED__
#define __STRUCTURES_H_INCLUDED__
#include "bool.h"

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

typedef struct LineStruct Line;
typedef struct OutSpanningTreeEdgeStruct OutSpanningTreeEdge;
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
bool onSegment(int px, int py, int qx, int qy, int rx, int ry);
int linesCount(const Line * l);

struct OutSpanningTreeEdgeStruct
{
	Line *l1;
	Line *l2;
	Point cross;
	int weight;
	OutSpanningTreeEdge * next;
};

struct VertexStruct
{
    Line *b;
    Edge *edges;
    int edgeCount;
	bool isInAnyMST;
	Vertex *next;
};

// calculate distance between two verticies.
int getDistance(const Vertex * const v1, const Vertex * const v2);


struct EdgeStruct
{
    Vertex *dst;
    Vertex *src;
	Line * cut;
    Edge *next;
    int weight;
    int included;
};

Edge * joinEdgesLists(Edge * list1, Edge * list2);

#endif // #ifndef __STRUCTURES_H_INCLUDED__
