#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bool.h"
#include "structures.h"
#include "ui.h"
#include "approximation.h"

int main(int argc, char** argv)
{
	initializeWindow(argc, argv, 800, 800);

	Line *LineHorArray = NULL;
	Line *LineVertArray = NULL;

	char filename[255]="input";
	printf("Enter file name: \n");
	//scanf("%s", filename);
	readInputLines(filename, &LineHorArray, & LineVertArray);

	Edge * approximation1 = buildApproximation(LineHorArray, LineVertArray);
	Edge * approximation2 = buildApproximation(LineVertArray, LineHorArray);
	Edge * any_solution = NULL;

	displayResults(LineHorArray, LineVertArray, approximation1, approximation2, any_solution);
	return 0;
}
