#ifndef ALSAMI_PURE_X11_WINDOW_HEADER
#define ALSAMI_PURE_X11_WINDOW_HEADER

#include "ihdr.h"
#include <X11/Xlib.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>

/*
 *	This is a pure Xlib  window header, I really don't have a use for this now
 *	This is meant to be a (sort of) C dialog control header.
 *
 * 	Let's say that a game wants to display dialog box with a button and some text saying that they can contribute source code to the game
 * 	As to not obstruct the view of the game, the game designers decide not to put the text in the actual window becuase it would not only be extremely difficult to create a button that magically appears and has event compaibility, but also that they don't want to deal with X11.
 * 	This header is designed for those kinds of people
 * */


typedef struct WINDOW_INFO_STRUCT{
	const char* WindowTitle;
	Display* dpy;
	XEvent xev;
	int screen;
	Window app_win, root_win;
	XSetWindowAttributes winattr;
	unsigned int depth;
	//XVisualInfo vis_inf;
} gm_wininf_T;

gm_wininf_T* gmwinf_init(const char* wintitle){
	gm_wininf_T* wininf_i = (gm_wininf_T*)calloc(1, sizeof(gm_wininf_T));
	wininf_i->WindowTitle=wintitle;
}

uint8_t gm_makewindow(gm_wininf_T* gmwin_i){
	gmwin_i->dpy=XOpenDisplay(NULL);
	if(gmwin_i->dpy==NULL){return 1;}

	gmwin_i->screen=DefaultScreen(gmwin_i->dpy);
	gmwin_i->depth=DefaultDepth(gmwin_i->dpy, gmwin_i->screen);
	gmwin_i->root_win=RootWindow(gmwin_i->dpy, gmwin_i->screen);

}





#endif
