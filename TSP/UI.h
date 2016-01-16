#pragma once

//#define DRAW_RESULT
#ifdef DRAW_RESULT
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>

#include "Types.h"

int initializeWindow(int argc, char **argv, int xBound, int yBound);
void read_from_screen(AllPoints *points);
void display_results(const AllPoints *points, const EdgesPath *path);

#endif // #ifdef DRAW_RESULT

