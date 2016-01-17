#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bool.h"
#include "structures.h"
#include "ui.h"
#include "approximation.h"
#include "build_spanning_tree.h"

int main(int argc, char** argv)
{
	initializeWindow(argc, argv, 800, 800);

	Line *LineHorArray = NULL;
	Line *LineVertArray = NULL;

	char filename[255]="input";
	printf("Enter file name: \n");
	//scanf("%s", filename);
	readInputLines(filename, &LineHorArray, & LineVertArray);

	Edge * approximation1 = buildLowerBoundApproximationPart(LineHorArray, LineVertArray);
	Edge * approximation2 = buildLowerBoundApproximationPart(LineVertArray, LineHorArray);

	OutSpanningTree  spanning_tree = buildSpanningTree(LineHorArray, LineVertArray);

	displayResults(LineHorArray, LineVertArray, approximation1, approximation2, spanning_tree);
	return 0;
}
