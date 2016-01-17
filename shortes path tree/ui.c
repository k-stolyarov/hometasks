#include "ui.h"

#if 0
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>

#include "structures.h"
#include "approximation.h"
#include <stdlib.h>
#include <stdio.h>

Display *display_ptr;
Screen *screen_ptr;
int screen_num;
char *display_name = NULL;
unsigned int display_width, display_height;
Window win;
int border_width;
unsigned int win_width, win_height;
int win_x, win_y;
XWMHints *wm_hints;
XClassHint *class_hints;
XSizeHints *size_hints;
XTextProperty win_name, icon_name;
char *win_name_string = "MST";
char *icon_name_string = "Icon for Example Window";
XEvent report;
GC gc_black, gc_blue, gc_red, gc_green;
unsigned long valuemask = 0;
XGCValues gc_values, gc_blue_values, gc_red_values, gc_green_values;
Colormap color_map;
XColor tmp_color1, tmp_color2;
XFontStruct *fontInfo;

void initializeWindow(int argc, char **argv, int xBound, int yBound)
{
	/* opening display: basic connection to X Server */
	if ((display_ptr = XOpenDisplay(display_name)) == NULL)
	{
		printf("Could not open display. \n"); exit(-1);
	}
	printf("Connected to X server  %s\n", XDisplayName(display_name));
	screen_num = DefaultScreen(display_ptr);
	screen_ptr = DefaultScreenOfDisplay(display_ptr);
	color_map = XDefaultColormap(display_ptr, screen_num);
	display_width = DisplayWidth(display_ptr, screen_num);
	display_height = DisplayHeight(display_ptr, screen_num);

	printf("Width %d, Height %d, Screen Number %d\n",
		display_width / 2, display_height / 2, screen_num);
	/* creating the window */
	border_width = 10;
	win_x = 0; win_y = 0;
	win_width = xBound;
	win_height = yBound;

	win = XCreateSimpleWindow(display_ptr, RootWindow(display_ptr, screen_num),
		win_x, win_y, win_width, win_height, border_width,
		BlackPixel(display_ptr, screen_num),
		WhitePixel(display_ptr, screen_num));
	/* now try to put it on screen, this needs cooperation of window manager */
	size_hints = XAllocSizeHints();
	wm_hints = XAllocWMHints();
	class_hints = XAllocClassHint();
	if (size_hints == NULL || wm_hints == NULL || class_hints == NULL)
	{
		printf("Error allocating memory for hints. \n"); exit(-1);
	}

	size_hints->flags = PPosition | PSize | PMinSize;
	size_hints->min_width = 60;
	size_hints->min_height = 60;

	XStringListToTextProperty(&win_name_string, 1, &win_name);
	XStringListToTextProperty(&icon_name_string, 1, &icon_name);

	wm_hints->flags = StateHint | InputHint;
	wm_hints->initial_state = NormalState;
	wm_hints->input = False;

	class_hints->res_name = "x_use_example";
	class_hints->res_class = "examples";

	XSetWMProperties(display_ptr, win, &win_name, &icon_name, argv, argc,
		size_hints, wm_hints, class_hints);

	/* what events do we want to receive */
	XSelectInput(display_ptr, win,
		ExposureMask | StructureNotifyMask | ButtonPressMask);

	/* finally: put window on screen */
	XMapWindow(display_ptr, win);

	XFlush(display_ptr);

	/* create graphics context, so that we may draw in this window */
	gc_black = XCreateGC(display_ptr, win, valuemask, &gc_values);
	XSetForeground(display_ptr, gc_black, BlackPixel(display_ptr, screen_num));
	XSetLineAttributes(display_ptr, gc_black, 5, LineSolid, CapRound, JoinRound);
	/* and three other graphics contexts, to draw in yellow and red and grey*/
	gc_blue = XCreateGC(display_ptr, win, valuemask, &gc_blue_values);
	XSetLineAttributes(display_ptr, gc_blue, 1
					   , LineSolid, CapRound, JoinRound);
	if (XAllocNamedColor(display_ptr, color_map, "blue",
		&tmp_color1, &tmp_color2) == 0)
	{
		printf("failed to get color blue\n"); exit(-1);
	}
	else
		XSetForeground(display_ptr, gc_blue, tmp_color1.pixel);
	gc_red = XCreateGC(display_ptr, win, valuemask, &gc_red_values);
	XSetLineAttributes(display_ptr, gc_red, 3, LineSolid, CapRound, JoinRound);
	if (XAllocNamedColor(display_ptr, color_map, "red",
		&tmp_color1, &tmp_color2) == 0)
	{
		printf("failed to get color red\n"); exit(-1);
	}
	else
		XSetForeground(display_ptr, gc_red, tmp_color1.pixel);
	gc_green = XCreateGC(display_ptr, win, valuemask, &gc_green_values);
	if (XAllocNamedColor(display_ptr, color_map, "green",
		&tmp_color1, &tmp_color2) == 0)
	{
		printf("failed to get color green\n"); exit(-1);
	}
	else
		XSetForeground(display_ptr, gc_green, tmp_color1.pixel);

	if ( (fontInfo =  XLoadQueryFont(display_ptr, "*-courier-*" )) == NULL){
	  printf("Font not found!\n");
	  exit(1);
	}
	XSetFont (display_ptr, gc_black, fontInfo->fid);
}

void processEvents()
{
	XNextEvent(display_ptr, &report);
	switch (report.type)
	{
	case Expose:
		break;
	case ConfigureNotify:
		win_width = report.xconfigure.width;
		win_height = report.xconfigure.height;
		break;
	case ButtonPress:
	{
						if (report.xbutton.button == Button1)
						{
							XDestroyWindow(display_ptr, win);
							exit(0);
						}
						else
						{
							printf("(%d;%d)\n", report.xbutton.x, report.xbutton.y);
						}
	}
		break;
	default:
		break;
	}
}

void displayLine(const GC desired_gc, Point p1, Point p2);

void drawLines(const GC desired_gc, Line * const LineHorArray)
{
	Line * line = LineHorArray;
	while (line != NULL)
	{
		displayLine(desired_gc, line->p1, line->p2);
		line = line->next;
	}
}

void drawEdge(const GC desired_gc, Edge * const edge)
{
	Point p1 = getCrossPoint(edge->dst->b, edge->cut);
	Point p2 = getCrossPoint(edge->src->b, edge->cut);
	displayLine(desired_gc, p1, p2);
}

void drawMST(const GC desired_gc, Edge * const MST)
{
	Edge * mst = MST;
	while (mst != NULL)
	{
		drawEdge(desired_gc, mst);
		mst = mst->next;
	}
}

float edgesLength(Edge * const edges)
{
	float result = 0;
	Edge * e = edges;
	while(NULL != e)
	{
		result += e->weight;
		e = e->next;
	}
	return result;
}

void disspayLowerBoundApproximationCost(Edge * const approximation1, Edge * const approximation2, const OutSpanningTree spanning_tree)
{
	const float lower_bound_length = edgesLength(approximation1) + edgesLength(approximation2);
	char buffer[512];
	sprintf(buffer, "Lower bound: %0.0f", lower_bound_length);
	XDrawString (display_ptr, win, gc_black, 10, 30, buffer, strlen (buffer) );
	sprintf(buffer, "SuboptimalSolution: %d", spanning_tree.weight);
	XDrawString (display_ptr, win, gc_black, 10, 60, buffer, strlen (buffer) );

}

void displayLine(const GC desired_gc, Point p1, Point p2)
{
	const int y_offset = 100;
	XDrawLine(display_ptr, win, desired_gc, p1.x, p1.y + y_offset, p2.x, p2.y + y_offset
			  );
}

void displaySpanningTreeEdge(const GC desired_gc, const OutSpanningTreeEdge * const edge)
{
	displayLine(desired_gc, edge->cross, edge->l1->p1);
	displayLine(desired_gc, edge->cross, edge->l1->p2);
	displayLine(desired_gc, edge->cross, edge->l2->p1);
	displayLine(desired_gc, edge->cross, edge->l2->p2);
}

void displaySpanningTree(const GC desired_gc, OutSpanningTree spanning_tree)
{
	int i = 0;
	for(i = 0; i < spanning_tree.edges_count; ++i)
	{
		displaySpanningTreeEdge(desired_gc, spanning_tree.edges + i);
	}
}

void displayResults(Line * const LineHorArray, Line * const LineVertArray, Edge * const approximation1, Edge * const approximation2, const OutSpanningTree spanning_tree)
{
	while (1)
	{
		disspayLowerBoundApproximationCost(approximation1, approximation2, spanning_tree);


		drawLines(gc_black, LineHorArray);
		drawLines(gc_black, LineVertArray);
		displaySpanningTree(gc_red, spanning_tree);
		drawMST(gc_green, approximation1);
		drawMST(gc_blue, approximation2);

		processEvents();
	}
}

#else
void initializeWindow(int argc, char **argv, int xBound, int yBound) {}
void displayResults(Line * const LineHorArray, Line * const LineVertArray, Edge * const approximation1, Edge * const approximation2, const OutSpanningTree spanning_tree) {}
#endif
