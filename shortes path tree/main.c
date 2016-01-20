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
	scanf("%s", filename);
	readInputLines(filename, &LineHorArray, & LineVertArray);
	printf("Input file is read\n");

	Edge * approximation1 = buildLowerBoundApproximationPart(LineHorArray, LineVertArray);
	Edge * approximation2 = buildLowerBoundApproximationPart(LineVertArray, LineHorArray);
	
	printf("Approximation is built\n");

	OutSpanningTree  spanning_tree = buildSpanningTree(LineHorArray, LineVertArray);
	printf("Spanning tree is built\n");

	displayResults(LineHorArray, LineVertArray, approximation1, approximation2, spanning_tree);

	return 0;
}
