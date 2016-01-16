/* compiles with command line  gcc xlibdemo.c -lX11 -lm -L/usr/X11R6/lib */
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "bool.h"
#include "wgraph.h"
#include "triangle.h"

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

initializeWindow(int argc, char **argv, int xBound, int yBound)
{
	/* opening display: basic connection to X Server */
	  if( (display_ptr = XOpenDisplay(display_name)) == NULL )
	    { printf("Could not open display. \n"); exit(-1);}
	  printf("Connected to X server  %s\n", XDisplayName(display_name) );
	  screen_num = DefaultScreen( display_ptr );
	  screen_ptr = DefaultScreenOfDisplay( display_ptr );
	  color_map  = XDefaultColormap( display_ptr, screen_num );
	  display_width  = DisplayWidth( display_ptr, screen_num );
	  display_height = DisplayHeight( display_ptr, screen_num );

	  printf("Width %d, Height %d, Screen Number %d\n",
	           display_width/2, display_height/2, screen_num);
	  /* creating the window */
	  border_width = 10;
	  win_x = 0; win_y = 0;
	  win_width = xBound;
	  win_height = yBound;

	  win= XCreateSimpleWindow( display_ptr, RootWindow( display_ptr, screen_num),
	                            win_x, win_y, win_width, win_height, border_width,
	                            BlackPixel(display_ptr, screen_num),
	                            WhitePixel(display_ptr, screen_num) );
	  /* now try to put it on screen, this needs cooperation of window manager */
	  size_hints = XAllocSizeHints();
	  wm_hints = XAllocWMHints();
	  class_hints = XAllocClassHint();
	  if( size_hints == NULL || wm_hints == NULL || class_hints == NULL )
	    { printf("Error allocating memory for hints. \n"); exit(-1);}

	  size_hints -> flags = PPosition | PSize | PMinSize  ;
	  size_hints -> min_width = 60;
	  size_hints -> min_height = 60;

	  XStringListToTextProperty( &win_name_string,1,&win_name);
	  XStringListToTextProperty( &icon_name_string,1,&icon_name);

	  wm_hints -> flags = StateHint | InputHint ;
	  wm_hints -> initial_state = NormalState;
	  wm_hints -> input = False;

	  class_hints -> res_name = "x_use_example";
	  class_hints -> res_class = "examples";

	  XSetWMProperties( display_ptr, win, &win_name, &icon_name, argv, argc,
	                    size_hints, wm_hints, class_hints );

	  /* what events do we want to receive */
	  XSelectInput( display_ptr, win,
	            ExposureMask | StructureNotifyMask | ButtonPressMask );

	  /* finally: put window on screen */
	  XMapWindow( display_ptr, win );

	  XFlush(display_ptr);

	  /* create graphics context, so that we may draw in this window */
	  gc = XCreateGC( display_ptr, win, valuemask, &gc_values);
	  XSetForeground( display_ptr, gc, BlackPixel( display_ptr, screen_num ) );
	  XSetLineAttributes( display_ptr, gc, 1, LineSolid, CapRound, JoinRound);
	  /* and three other graphics contexts, to draw in yellow and red and grey*/
	  gc_yellow = XCreateGC( display_ptr, win, valuemask, &gc_yellow_values);
	  XSetLineAttributes(display_ptr, gc_yellow, 2, LineSolid,CapRound, JoinRound);
	  if( XAllocNamedColor( display_ptr, color_map, "yellow",
				&tmp_color1, &tmp_color2 ) == 0 )
	    {printf("failed to get color yellow\n"); exit(-1);}
	  else
	    XSetForeground( display_ptr, gc_yellow, tmp_color1.pixel );
	  gc_red = XCreateGC( display_ptr, win, valuemask, &gc_red_values);
	  XSetLineAttributes( display_ptr, gc_red, 6, LineSolid, CapRound, JoinRound);
	  if( XAllocNamedColor( display_ptr, color_map, "red",
				&tmp_color1, &tmp_color2 ) == 0 )
	    {printf("failed to get color red\n"); exit(-1);}
	  else
	    XSetForeground( display_ptr, gc_red, tmp_color1.pixel );
	  gc_grey = XCreateGC( display_ptr, win, valuemask, &gc_grey_values);
	  if( XAllocNamedColor( display_ptr, color_map, "light grey",
				&tmp_color1, &tmp_color2 ) == 0 )
	    {printf("failed to get color grey\n"); exit(-1);}
	  else
	    XSetForeground( display_ptr, gc_grey, tmp_color1.pixel );
}

drawTriangles(const triangleList *triangles)
{
	int i;
	for (i = 0; i < triangles->numTriangles; i++)
	{
		XDrawLine(display_ptr, win, gc,
			triangles->triangles[i].points[0].x, triangles->triangles[i].points[0].y,
			triangles->triangles[i].points[1].x, triangles->triangles[i].points[1].y);
		XDrawLine(display_ptr, win, gc,
			triangles->triangles[i].points[0].x, triangles->triangles[i].points[0].y,
			triangles->triangles[i].points[2].x, triangles->triangles[i].points[2].y);
		XDrawLine(display_ptr, win, gc,
			triangles->triangles[i].points[1].x, triangles->triangles[i].points[1].y,
			triangles->triangles[i].points[2].x, triangles->triangles[i].points[2].y);
	}
}

bool IsInsideTriangle(const point p, const triangleList *triangles)
{
	int i;

	for (i = 0; i < triangles->numTriangles; i++)
	{
		if (is_inside_triangle(p, triangles->triangles[i]))
		{
			return TRUE;
		}
	}
	return FALSE;
}

int doesFileExist(const char *filename) {
    struct stat st;
    int result = stat(filename, &st);
    return result == 0;
}
int getXBound(const triangleList *triangles)
{
	int xBound = 0;
	int tmpX;
	int i;

	for (i = 0; i < triangles->numTriangles; i++)
		{
			tmpX = triangles->triangles[i].points[0].x;
			if (tmpX > xBound)
				xBound = tmpX;
			tmpX = triangles->triangles[i].points[1].x;
			if (tmpX > xBound)
				xBound = tmpX;
			tmpX = triangles->triangles[i].points[2].x;
			if (tmpX > xBound)
				xBound = tmpX;
		}

	return xBound + xBound * 0.1;
}

int getYBound(const triangleList *triangles)
{
	int yBound = 0;
	int tmpY;
	int i;

	for (i = 0; i < triangles->numTriangles; i++)
		{
			tmpY = triangles->triangles[i].points[0].y;
			if (tmpY > yBound)
				yBound = tmpY;
			tmpY = triangles->triangles[i].points[1].y;
			if (tmpY > yBound)
				yBound = tmpY;
			tmpY = triangles->triangles[i].points[2].y;
			if (tmpY > yBound)
				yBound = tmpY;
		}

	return yBound + yBound * 0.1;
}

void draw(
	const graph * g,
	const triangleList *triangles,
	const bool draw_first_point,
	const bool draw_path,
	const point p1,
	const point p2,
	const path * _path)
{
	XClearWindow(display_ptr, win);
	drawTriangles(triangles);
	const int radius = win_height / 100;
	if (draw_first_point == TRUE)
	{
		XFillArc(display_ptr, win, gc_red,
			p1.x - radius / 2, p1.y - radius / 2,
			radius, radius, 0, 360 * 64);
	}
	if (draw_path == TRUE)
	{
		int i =0 ;
		XFillArc(display_ptr, win, gc_red,
			p2.x - radius / 2, p2.y - radius / 2,
			radius, radius, 0, 360 * 64);

		for (i = 0; i < _path->pointNumber - 1; i++)
		{
			point p1 = g->points[_path->points[i]];
			point p2 = g->points[_path->points[i + 1]];
			XDrawLine(display_ptr, win, gc_yellow,
				p1.x, p1.y,
				p2.x, p2.y);
		}
	}
}

void process_graph(
	const point src,
	const point dst,
	const triangleList *triangles,
	path* _path,
	graph *g)
{
	const int src_point_index = 0;
	const int dst_point_index = 1;
	build_graph(g, src, dst, triangles);
	build_path(g, src_point_index, dst_point_index, _path);
}
int main(int argc, char **argv)
{
	char filename[255]="points.txt";
	//printf("Enter file name: ");
	//scanf("%s", filename);

	//if(doesFileExist(filename)!=1)
	//{
	//	printf("Invalid file name");
	//	exit(0);
	//}

	triangleList triangles;
	read_triangles(&triangles, filename);

	int xBound = getXBound(&triangles);
	int yBound = getYBound(&triangles);

	initializeWindow(argc, argv, xBound, yBound);

	graph *g = (graph*)calloc(1, sizeof(graph));
	path _path;
	point p1;
	point p2;
	bool oneClick = TRUE;
	int i, j;
	bool draw_path = FALSE;
	bool draw_first_point = FALSE;

  /* and now it starts: the event loop */
	while (1)
	{
		XNextEvent(display_ptr, &report);
		switch (report.type)
		{
		case Expose:
			/* (re-)draw the example figure. This event happens
			   each time some part ofthe window gets exposed (becomes visible) */
			draw(g, &triangles, draw_first_point, draw_path,p1, p2, &_path);
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
			else
			{
				point temp;
				temp.x = report.xbutton.x;
				temp.y = report.xbutton.y;

				if (oneClick == TRUE)
				{
					if (!IsInsideTriangle(temp, &triangles) == TRUE)
					{
						p1 = temp;
						draw_first_point = TRUE;
						draw_path = FALSE;
						oneClick = FALSE;
					}
				}
				else if (oneClick == FALSE)
				{
					if (!IsInsideTriangle(temp, &triangles) == TRUE)
					{
						p2 = temp;

						process_graph(p1, p2, &triangles, &_path, g);
						draw_path = TRUE;
						oneClick = TRUE;
					}
				}
				draw(g, &triangles, draw_first_point, draw_path, p1, p2, &_path);
			}
			break;
		}			
		default:
			/* this is a catch-all for other events; it does not do anything.
				   One could look at the report type to see what the event was */
			break;
		}
	}

	free(g);
	exit(0);
}
