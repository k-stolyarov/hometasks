#include "ui.h"

#if 0
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>

#include "structures.h"

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
GC gc, gc_yellow, gc_red, gc_grey;
unsigned long valuemask = 0;
XGCValues gc_values, gc_yellow_values, gc_red_values, gc_grey_values;
Colormap color_map;
XColor tmp_color1, tmp_color2;

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
	gc = XCreateGC(display_ptr, win, valuemask, &gc_values);
	XSetForeground(display_ptr, gc, BlackPixel(display_ptr, screen_num));
	XSetLineAttributes(display_ptr, gc, 1, LineSolid, CapRound, JoinRound);
	/* and three other graphics contexts, to draw in yellow and red and grey*/
	gc_yellow = XCreateGC(display_ptr, win, valuemask, &gc_yellow_values);
	XSetLineAttributes(display_ptr, gc_yellow, 4, LineSolid, CapRound, JoinRound);
	if (XAllocNamedColor(display_ptr, color_map, "yellow",
		&tmp_color1, &tmp_color2) == 0)
	{
		printf("failed to get color yellow\n"); exit(-1);
	}
	else
		XSetForeground(display_ptr, gc_yellow, tmp_color1.pixel);
	gc_red = XCreateGC(display_ptr, win, valuemask, &gc_red_values);
	XSetLineAttributes(display_ptr, gc_red, 2, LineSolid, CapRound, JoinRound);
	if (XAllocNamedColor(display_ptr, color_map, "red",
		&tmp_color1, &tmp_color2) == 0)
	{
		printf("failed to get color red\n"); exit(-1);
	}
	else
		XSetForeground(display_ptr, gc_red, tmp_color1.pixel);
	gc_grey = XCreateGC(display_ptr, win, valuemask, &gc_grey_values);
	if (XAllocNamedColor(display_ptr, color_map, "light grey",
		&tmp_color1, &tmp_color2) == 0)
	{
		printf("failed to get color grey\n"); exit(-1);
	}
	else
		XSetForeground(display_ptr, gc_grey, tmp_color1.pixel);
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

void drawLines(Line * const LineHorArray)
{
	Line * line = LineHorArray;
	while (line != NULL)
	{
		XDrawLine(display_ptr, win, gc, LineHorArray->pointB, LineHorArray->pointA, LineHorArray->pointC, LineHorArray->pointA);
		line = line->next;
	}
}

void drawMST(Edge * const MST)
{
	Edge * mst = MST;
	while (mst != NULL)
	{
		XDrawLine(display_ptr, win, gc_red, mst->src->X, mst->src->Y, mst->dst->X, mst->dst->Y);
		mst = mst->next;
	}
}

void displayResults(Line * const LineHorArray, Line * const LineVertArray, Edge * const approximation1, Edge * const approximation2)
{
	while (1)
	{
		drawLines(LineHorArray);
		drawLines(LineVertArray);
		drawMST(approximation1);
		drawMST(approximation2);

		processEvents();
	}
}

#else
void initializeWindow(int argc, char **argv, int xBound, int yBound) {}
void displayResults(Line * const LineHorArray, Line * const LineVertArray, Edge * const approximation1, Edge * const approximation2) {}
#endif