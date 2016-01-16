/* compiles with command line  gcc xlibdemo.c -lX11 -lm -L/usr/X11R6/lib */
//#include <X11/Xlib.h>
//#include <X11/Xutil.h>
//#include <X11/Xos.h>
//#include <X11/Xatom.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <memory.h>

#define RAD 6

void MST(int n, int p[][2], int e[][2]); /* function prototype */

//Display *display_ptr;
//Screen *screen_ptr;
//int screen_num;
//char *display_name = NULL;
//unsigned int display_width, display_height;
//
//Window win;
//int border_width;
//unsigned int win_width, win_height;
//int win_x, win_y;
//
//XWMHints *wm_hints;
//XClassHint *class_hints;
//XSizeHints *size_hints;
//XTextProperty win_name, icon_name;
//char *win_name_string = "Homework 3: Minimum Spanning Tree";
//char *icon_name_string = "HW3: MST";
//
//XEvent report;
//
//GC gc, gc_yellow, gc_red, gc_grey;
//unsigned long valuemask = 0;
//XGCValues gc_values, gc_yellow_values, gc_red_values, gc_grey_values;
//Colormap color_map;
//XColor tmp_color1, tmp_color2;


int main(int argc, char **argv)
{ int points[1000][2];
  int edges[1000][2];
  int number_of_points;
  FILE *fp;
  if( argc < 2)
  {  printf(" needs input file name as command line argument\n");
     exit(-1);
  }
  if( (fp = fopen( argv[1], "r"))==NULL )
  {  printf(" could not open input file %s\n", argv[1]);
     exit(-1);
  }
  number_of_points =0;
  while( ( fscanf(fp, "%d %d\n", 
           &(points[number_of_points][0]),
           &(points[number_of_points][1]) ) ==2 )
          && (number_of_points < 999 ) )
  {  number_of_points +=1;}
  if( number_of_points == 0 )
  {  printf(" did not find any points in file\n", argv[1]);
     exit(-1);
  }
  else if (number_of_points >= 999 )
  {  printf(" too many points in file\n", argv[1]);
     exit(-1);
  }
  else
     printf(" found %d points\n", number_of_points);
 // /* opening display: basic connection to X Server */
 // if( (display_ptr = XOpenDisplay(display_name)) == NULL )
 //   { printf("Could not open display. \n"); exit(-1);}
 // printf("Connected to X server  %s\n", XDisplayName(display_name) );
 // screen_num = DefaultScreen( display_ptr );
 // screen_ptr = DefaultScreenOfDisplay( display_ptr );
 // color_map  = XDefaultColormap( display_ptr, screen_num );
 // display_width  = DisplayWidth( display_ptr, screen_num );
 // display_height = DisplayHeight( display_ptr, screen_num );

 // printf("Width %d, Height %d, Screen Number %d\n", 
 //          display_width, display_height, screen_num);
 // /* creating the window */
 // border_width = 10;
 // win_x = 0; win_y = 0;
 // win_width = display_width/2;
 // win_height = win_width; /*square window*/
 // 
 // win= XCreateSimpleWindow( display_ptr, RootWindow( display_ptr, screen_num),
 //                           win_x, win_y, win_width, win_height, border_width,
 //                           BlackPixel(display_ptr, screen_num),
 //                           WhitePixel(display_ptr, screen_num) );
 // /* now try to put it on screen, this needs cooperation of window manager */
 // size_hints = XAllocSizeHints();
 // wm_hints = XAllocWMHints();
 // class_hints = XAllocClassHint();
 // if( size_hints == NULL || wm_hints == NULL || class_hints == NULL )
 //   { printf("Error allocating memory for hints. \n"); exit(-1);}

 // size_hints -> flags = PPosition | PSize | PMinSize  ;
 // size_hints -> min_width = 60;
 // size_hints -> min_height = 60;

 // XStringListToTextProperty( &win_name_string,1,&win_name);
 // XStringListToTextProperty( &icon_name_string,1,&icon_name);
 // 
 // wm_hints -> flags = StateHint | InputHint ;
 // wm_hints -> initial_state = NormalState;
 // wm_hints -> input = False;

 // class_hints -> res_name = "x_use_example";
 // class_hints -> res_class = "examples";

 // XSetWMProperties( display_ptr, win, &win_name, &icon_name, argv, argc,
 //                   size_hints, wm_hints, class_hints );

 // /* what events do we want to receive */
 // XSelectInput( display_ptr, win, 
 //           ExposureMask | StructureNotifyMask | ButtonPressMask );
 // 
 // /* finally: put window on screen */
 // XMapWindow( display_ptr, win );

 // XFlush(display_ptr);

 // /* create graphics context, so that we may draw in this window */
 // gc = XCreateGC( display_ptr, win, valuemask, &gc_values);
 // XSetForeground( display_ptr, gc, BlackPixel( display_ptr, screen_num ) );
 // XSetLineAttributes( display_ptr, gc, 4, LineSolid, CapRound, JoinRound);
 // /* and three other graphics contexts, to draw in yellow and red and grey*/
 // gc_yellow = XCreateGC( display_ptr, win, valuemask, &gc_yellow_values);
 // XSetLineAttributes(display_ptr, gc_yellow, 6, LineSolid,CapRound, JoinRound);
 // if( XAllocNamedColor( display_ptr, color_map, "yellow", 
	//		&tmp_color1, &tmp_color2 ) == 0 )
 //   {printf("failed to get color yellow\n"); exit(-1);} 
 // else
 //   XSetForeground( display_ptr, gc_yellow, tmp_color1.pixel );
 // gc_red = XCreateGC( display_ptr, win, valuemask, &gc_red_values);
 // XSetLineAttributes( display_ptr, gc_red, 4, LineSolid, CapRound, JoinRound);
 // if( XAllocNamedColor( display_ptr, color_map, "red", 
	//		&tmp_color1, &tmp_color2 ) == 0 )
 //   {printf("failed to get color red\n"); exit(-1);} 
 // else
 //   XSetForeground( display_ptr, gc_red, tmp_color1.pixel );
 // gc_grey = XCreateGC( display_ptr, win, valuemask, &gc_grey_values);
 // if( XAllocNamedColor( display_ptr, color_map, "light grey", 
	//		&tmp_color1, &tmp_color2 ) == 0 )
 //   {printf("failed to get color grey\n"); exit(-1);} 
 // else
 //   XSetForeground( display_ptr, gc_grey, tmp_color1.pixel );

 // /* and now it starts: the event loop */
 // while(1)
 // {  int i;
 //    int MST_computed = 0;
 //    XNextEvent( display_ptr, &report );
 //    switch( report.type )
 //    {
	//case Expose:
 //         /* (re-)draw the figure. This event happens
 //            each time some part ofthe window gets exposed (becomes visible) */
	//  if( MST_computed )
 //         {  /* if the MST is known, draw the edges first */
 //            for( i=0; i < number_of_points-1; i++ )
 //            {
 //                  XDrawLine(display_ptr, win, gc_red, 
 //                  (points[edges[i][0]][0]* win_width)/500, 
 //                  (points[edges[i][0]][1]* win_height)/500, 
 //                  (points[edges[i][1]][0]* win_width)/500, 
 //                  (points[edges[i][1]][1]* win_height)/500 );
 //            } 
 //         }
 //         /* now draw the points */
 //         for( i=0; i < number_of_points; i++ )
 //         {
 //            XFillArc(display_ptr, win, gc, 
 //            (points[i][0]* win_width)/500 - RAD, 
 //            (points[i][1]* win_height)/500 - RAD,
 //            2*RAD, 2*RAD, 0, 360*64 );
 //         } 
 //         break; /* end of redrawing the figure */
 //       case ConfigureNotify:
 //         /* This event happens when the user changes the size of the window*/
 //         win_width = report.xconfigure.width;
 //         win_height = report.xconfigure.height;
 //         break;
 //       case ButtonPress:
 //         /* This event happens when the user pushes a mouse button. */
 //         /* clear MST */
 //         for( i = 0; i< number_of_points -1; i++ )
 //         { edges[i][0] = edges[i][1] = 0;
 //         }
 //         MST_computed = 0;
 //         /* compute MST */
 //         printf("calling MST with %d points\n", number_of_points); 
 //         fflush(stdout);
 //         MST( number_of_points, points, edges );
 //         printf("finished MST\n"); fflush(stdout);
 //         MST_computed = 1;
 //         /* draw MST */
 //         for( i=0; i < number_of_points-1; i++ )
 //         {
 //            XDrawLine(display_ptr, win, gc_red, 
 //               (points[edges[i][0]][0]* win_width)/500, 
 //               (points[edges[i][0]][1]* win_height)/500, 
 //               (points[edges[i][1]][0]* win_width)/500, 
 //               (points[edges[i][1]][1]* win_height)/500 );
 //         } 
 //         for( i=0; i < number_of_points; i++ )
 //         {
 //            XFillArc(display_ptr, win, gc, 
 //               (points[i][0]* win_width)/500 - RAD, 
 //               (points[i][1]* win_height)/500 -RAD,
 //               2*RAD, 2*RAD, 0, 360*64 );
 //         } 
 //         break;
 //       default:
	//  /* this is a catch-all for other events; it does not do anything.
 //            One could look at the report type to see what the event was */ 
 //         break;
 //    }

 // }
  MST(number_of_points, points, edges);
  exit(0);
}

struct Edge
{
	int start_point_index;
	int end_point_index;
	int square_length;
};

struct Component
{
	int size;
	int * verticies;
};

// joint two components and update all internal data structures
void join_components(
	int vertex_component[],
	struct Component * components,
	const int vertex_index_1,
	const int vertex_index_2)
{
	const int component_1 = vertex_component[vertex_index_1];
	const int component_2 = vertex_component[vertex_index_2];
	// for each vertex in component 2 set that now it belongs to component 1.
	for (int i = 0; i < components[component_2].size; ++i)
	{
		vertex_component[components[component_2].verticies[i]] = component_1;
	}	
	const int joined_component_size = components[component_1].size + components[component_2].size;
	// merge vertices for component 1 and component 2
	int * joined_component = calloc(joined_component_size, sizeof(int));
	memcpy(joined_component, components[component_1].verticies, sizeof(int)* components[component_1].size);
	memcpy(joined_component + components[component_1].size, components[component_2].verticies, sizeof(int)* components[component_2].size);

	free(components[component_1].verticies);
	components[component_1].verticies = NULL;
	components[component_1].size = 0;
	free(components[component_2].verticies);
	components[component_2].verticies = NULL;
	components[component_2].size = 0;

	components[component_1].verticies = joined_component;
	components[component_1].size = joined_component_size;
}


int edges_compare(const void * a, const void * b)
{
	return ((const struct Edge*)a)->square_length - ((const struct Edge*)b)->square_length;
}

int sqr(const int a)
{
	return a*a;
}

void MST(int n, int p[][2], int e[][2])
{
	const int edges_count = n*(n - 1) / 2;
	struct Edge * all_edges = calloc(edges_count, sizeof(struct Edge));
	{
		int edge_index = 0;
		for (int start = 0; start < n; ++start)
		{
			// edges that starts in vertex "start" ends in vertices "j" from range [0...start] are equal to  edges that starts in "j" and ends in "start"
			for (int end = start + 1; end < n; ++end)
			{
				all_edges[edge_index].start_point_index = start;
				all_edges[edge_index].end_point_index = end;
				all_edges[edge_index].square_length = sqr(p[start][0] - p[end][0]) + sqr(p[start][1] - p[end][1]);
				++edge_index;
			}
		}

		qsort(all_edges, edges_count, sizeof(struct Edge), edges_compare);
	}
	// index of the component, the vertex belongs to.
	int * vertex_component = calloc(n, sizeof(int));
	// initially each  vertex belongs to different component
	for (int i = 0; i < n; ++i)
	{
		vertex_component[i] = i;
	}

	// array of components: verticies that are connected with MST part.
	struct Component *components = calloc(n, sizeof(struct Component));
	for (int i = 0; i < n; ++i)
	{
		// initially for each component belongs only one vertex.
		components[i].verticies = calloc(1, sizeof(int));
		components[i].verticies[0] = i;
		components[i].size = 1;
	}

	{
		int output_edge_index = 0;
		for (int i = 0; i < edges_count; ++i)
		{
			if (vertex_component[all_edges[i].end_point_index] != vertex_component[all_edges[i].start_point_index])
			{
				// points that forms and edge i belongs to different components.
				// Join that components and add edge to the output.
				join_components(vertex_component, components, all_edges[i].start_point_index, all_edges[i].end_point_index);

				e[output_edge_index][0] = all_edges[i].start_point_index;
				e[output_edge_index][1] = all_edges[i].end_point_index;
				++output_edge_index;
			}
		}
	}

	for (int i = 0; i < n; ++i)
	{
		free(components[i].verticies);
	}
	free(components);
	free(vertex_component);
	free(all_edges);
}