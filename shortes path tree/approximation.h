#ifndef __APPROXIMATION_H_INCLUDED__
#define __APPROXIMATION_H_INCLUDED__
#include "structures.h"

Point getCrossPoint(const Line * l1, const Line * l2);

Edge * buildLowerBoundApproximationPart(Line * lines_verticies_form, Line * lines_intersects_verticies_lines);

#endif // #ifndef __APPROXIMATION_H_INCLUDED__
