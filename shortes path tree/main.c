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

	{
		Line * l = LineHorArray;
		int minx = 1000000;
		int maxx = -100000;
		int miny = 1000000;
		int maxy = -100000;

		while(l != NULL)
		{
			minx = min(minx, l->p1.x);
			minx = min(minx, l->p2.x);

			maxx = max(maxx, l->p1.x);
			maxx = max(maxx, l->p2.x);

			miny = min(miny, l->p2.y);
			maxy = max(maxy, l->p2.y);
			l = l->next;
		}

		l = LineVertArray;

		while(l != NULL)
		{
			miny = min(miny, l->p1.y);
			miny = min(miny, l->p2.y);

			maxy = max(maxy, l->p1.y);
			maxy = max(maxy, l->p2.y);

			minx = min(minx, l->p2.x);
			maxx = max(maxx, l->p2.x);
			l = l->next;
		}

		l = LineHorArray;
		while(l != NULL)
		{
			l->p1.x = minx;
			l->p2.x = maxx;
			l = l->next;
		}
		l = LineVertArray;
		while(l != NULL)
		{
			l->p1.y = miny;
			l->p2.y = maxy;
			l = l->next;
		}
	}


	Edge * approximation1 = buildLowerBoundApproximationPart(LineHorArray, LineVertArray);
	Edge * approximation2 = buildLowerBoundApproximationPart(LineVertArray, LineHorArray);

	OutSpanningTreeEdge * spanning_tree = NULL;// = buildSpanningTree(LineHorArray, LineVertArray);

	displayResults(LineHorArray, LineVertArray, approximation1, approximation2, spanning_tree);
	return 0;
}
