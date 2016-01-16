#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include "structures.h"

void initializeWindow(int argc, char **argv, int xBound, int yBound);
void displayResults(Vertex * const VertexArray, Line * const LineHorArray, Line * const LineVertArray, Edge * const mst);

#endif // UI_H_INCLUDED