#include "UI.h"

#ifdef DRAW_RESULT
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
char *win_name_string = "Example Window";
char *icon_name_string = "Icon for Example Window";

XEvent report;

GC gc, gc_yellow, gc_red, gc_grey;
unsigned long valuemask = 0;
XGCValues gc_values, gc_yellow_values, gc_red_values, gc_grey_values;
Colormap color_map;
XColor tmp_color1, tmp_color2;

int initializeWindow(int argc, char **argv, int xBound, int yBound)
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
	XSetLineAttributes(display_ptr, gc_yellow, 2, LineSolid, CapRound, JoinRound);
	if (XAllocNamedColor(display_ptr, color_map, "yellow",
		&tmp_color1, &tmp_color2) == 0)
	{
		printf("failed to get color yellow\n"); exit(-1);
	}
	else
		XSetForeground(display_ptr, gc_yellow, tmp_color1.pixel);
	gc_red = XCreateGC(display_ptr, win, valuemask, &gc_red_values);
	XSetLineAttributes(display_ptr, gc_red, 6, LineSolid, CapRound, JoinRound);
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

void draw_points(const AllPoints *all_points)
{
	int i = 0;
	const int radius = 7;

	for (i = 0; i < all_points->number_of_points; ++i)
	{
		const Point p = all_points->points[i];
		XFillArc(display_ptr, win, gc_red,
			p.x - radius / 2, p.y - radius / 2,
			radius, radius, 0, 360 * 64);
	}
}

void draw_path(const AllPoints *all_points, const EdgesPath *path)
{
	int i = 0;
	for (i = 0; i < path->size; i++)
	{
		const Point p1 = all_points->points[path->edges[i].start];
		const Point p2 = all_points->points[path->edges[i].end];
		XDrawLine(display_ptr, win, gc_yellow,
			p1.x, p1.y,
			p2.x, p2.y);
	}
}

void read_from_screen(AllPoints *all_points)
{
	while (1)
	{
		XNextEvent(display_ptr, &report);
		XClearWindow(display_ptr, win);
		switch (report.type)
		{
		case Expose:
			/* (re-)draw the example figure. This event happens
			each time some part ofthe window gets exposed (becomes visible) */
			draw_points(all_points);
			break;
		case ConfigureNotify:
			/* This event happens when the user changes the size of the window*/
			win_width = report.xconfigure.width;
			win_height = report.xconfigure.height;
			break;
		case ButtonPress:
			/* This event happens when the user pushes a mouse button. I draw
			a circle to show the point where it happened, but do not save
			the position; so when the next redraw event comes, these circles
			disappear again. */
			{
				if (report.xbutton.button == Button1)
				{
					return;
				}
				append_point(all_points, report.xbutton.x, report.xbutton.y);
				draw_points(all_points);
				break;
			}
		default:
			/* this is a catch-all for other events; it does not do anything.
			One could look at the report type to see what the event was */
			break;
		}
	}
}
void display_results(const AllPoints *all_points, const EdgesPath *path)
{
	while (1)
	{
		XNextEvent(display_ptr, &report);
		XClearWindow(display_ptr, win);
		switch (report.type)
		{
		case Expose:
			/* (re-)draw the example figure. This event happens
			each time some part ofthe window gets exposed (becomes visible) */
			draw_points(all_points);
			draw_path(all_points, path)
			break;
		case ConfigureNotify:
			/* This event happens when the user changes the size of the window*/
			win_width = report.xconfigure.width;
			win_height = report.xconfigure.height;
			break;
		case ButtonPress:
			/* This event happens when the user pushes a mouse button. I draw
			a circle to show the point where it happened, but do not save
			the position; so when the next redraw event comes, these circles
			disappear again. */
		{
			if (report.xbutton.button == Button1)
			{
				XDestroyWindow(display_ptr, win);
				exit(0);
			}
			draw_points(all_points);
			draw_path(all_points, path)
			break;
		}
		default:
			/* this is a catch-all for other events; it does not do anything.
			One could look at the report type to see what the event was */
			break;
		}
	}
}
#endif // #ifdef DRAW_RESULT