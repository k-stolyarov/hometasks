#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include "structures.h"

void initializeWindow(int argc, char **argv, int xBound, int yBound);
void displayResults(Line * const LineHorArray, Line * const LineVertArray, Edge * const approximation1, Edge * const approximation2);

#endif // UI_H_INCLUDED