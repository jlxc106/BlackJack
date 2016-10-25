/*
Name: Jay Lim
*/
#include <X11/Xlib.h>
#include "BlackJack.cpp"
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>

int main(void)
{
	BlackJack *bj = new BlackJack(2);
	
	Display *dpy;
	int screen;
	Window win;
	Window childwin;
	Window StopButton;
	Window NewGameButton;
	XEvent event;
	srand(time(NULL));	//rng is seeded//

	int x, y;
	Window root_win;
	Colormap colormap;
	XColor button_color;
	XColor lightgray_color, darkgray_color;
	XGCValues gcv_lightgray, gcv_darkgray;
	GC gc_lightgray, gc_darkgray;
	unsigned int border_width;
	unsigned int depth;
	unsigned int width, height;
	

	XFontStruct *font;
	XTextItem ti[1];
	
	XFontStruct *font2;
	XTextItem ti2[1];
		
	XFontStruct *font3;
	XTextItem ti3[1];

	dpy = XOpenDisplay(NULL);
	
	if(dpy == NULL)
	{
		fprintf(stderr, "Cannot open display\n");
		exit(1);
	}

	screen = DefaultScreen(dpy);

/* parent window*/
	win = XCreateSimpleWindow(dpy, RootWindow(dpy, screen),
	100, 100, 1000, 700, 1,
	BlackPixel(dpy, screen), WhitePixel(dpy, screen));
	
	XSelectInput(dpy, win, ExposureMask | KeyPressMask);

	XMapWindow(dpy, win);

/* child window*/

	colormap = DefaultColormap(dpy, screen);
	XParseColor(dpy, colormap, "rgb:cc/cc/cc", &button_color);
	XAllocColor(dpy, colormap, &button_color);

	XParseColor(dpy, colormap, "rgb:ee/ee/ee", &lightgray_color);
	XAllocColor(dpy, colormap, &lightgray_color);
	gcv_lightgray.foreground = lightgray_color.pixel;
	gcv_lightgray.background = button_color.pixel;
	gc_lightgray = XCreateGC(dpy, RootWindow(dpy, screen), 
		GCForeground | GCBackground, &gcv_lightgray);
	

	XParseColor(dpy, colormap, "rgb:88/88/88", &darkgray_color);
	XAllocColor(dpy, colormap, &darkgray_color);
	gcv_darkgray.foreground = darkgray_color.pixel;
	gcv_darkgray.background = button_color.pixel;
	gc_darkgray = XCreateGC(dpy, RootWindow(dpy, screen),
		 GCForeground | GCBackground, &gcv_darkgray);



	childwin = XCreateSimpleWindow(dpy, win,
	100, 550, 200, 100, 1,
	BlackPixel(dpy, screen),button_color.pixel);
	
	
	StopButton = XCreateSimpleWindow(dpy, win, 
	400, 550, 200, 100, 1, 
	BlackPixel(dpy, screen), button_color.pixel);
	
	NewGameButton = XCreateSimpleWindow(dpy, win,
	700, 550, 200, 100, 1,
	BlackPixel(dpy, screen),button_color.pixel);

	XSelectInput(dpy, childwin, ExposureMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask);

	XSelectInput(dpy, StopButton, ExposureMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask);	
	
	XSelectInput(dpy, NewGameButton, ExposureMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask);	

	XMapWindow(dpy, childwin);
	
	XMapWindow(dpy, StopButton);	
	
	XMapWindow(dpy, NewGameButton);
		
	XGetGeometry(dpy, childwin, &root_win, &x, &y, &width, &height, &border_width, &depth);	

	XGetGeometry(dpy, StopButton, &root_win, &x, &y, &width, &height, &border_width, &depth);	

	XGetGeometry(dpy, NewGameButton, &root_win, &x, &y, &width, &height, &border_width, &depth);	
	
	while(1)
	{
		XNextEvent(dpy, &event);
		if(event.xany.window == NewGameButton)
		{
			if(event.type == Expose)
			{
				font3 = XLoadQueryFont(dpy, "7x14");
				ti3[0].chars = (char *)"New Game!";
				ti3[0].nchars = 9;
				ti3[0].delta = 5;
				ti3[0].font = font3->fid;
				XDrawText(dpy, NewGameButton, DefaultGC(dpy, screen),
					 (width-XTextWidth(font3, ti3[0].chars, ti3[0].nchars))/2,
					(height-(font3->ascent+font3->descent))/2+font3->ascent,
					ti3, 1);
				XUnloadFont(dpy, font3->fid);
			}
			if(event.type == ButtonPress)
			{
				if(bj->GameOn==true){
					char reset;
					cout << "Do you want to create a new game? Press Y/N: ";
					cin >> reset;
					if(reset == 'Y' || reset == 'y'){
						cout << "reset" << endl;
						delete bj;
						bj = new BlackJack(2);
						bj->setup(2);
					}
				}
				else{
					cout << "reset" << endl;
					delete bj;
					bj = new BlackJack(2);
					bj->setup(2);
				}
			}
		}
		if(event.xany.window == StopButton)
		{	
			if(event.type == Expose)
			{	
				bj->setup(2);
				bj->bustPercentage();
				font2 = XLoadQueryFont(dpy, "7x14");
				ti2[0].chars = (char *)"Stay!";
				ti2[0].nchars = 5;
				ti2[0].delta = 0;
				ti2[0].font = font2->fid;
				XDrawText(dpy, StopButton, DefaultGC(dpy, screen),
					 (width-XTextWidth(font2, ti2[0].chars, ti2[0].nchars))/2,
					(height-(font2->ascent+font2->descent))/2+font2->ascent,
					ti2, 1);
				XUnloadFont(dpy, font2->fid);
			}
			if(bj->GameOn==true){
				if(event.type==ButtonPress)
				{
					//at this point, dealer has decision to make: hit or not hit.
					while(bj->DealerValue < bj->PlayerValue)
						bj->DealwithIt(2);
					bj->soWhoWins();
				}
			}
			else{
				if(event.type==ButtonPress){
					cout << "start a new game" << endl;
				}
			}
		}
		if(event.xany.window == childwin)
		{
			if(event.type == Expose)
			{
				//"press button to hit"
				//XDrawLine(dpy, childwin,DefaultGC(dpy, screen), 10, 10, 60, 60);
				font = XLoadQueryFont(dpy, "7x14");
				ti[0].chars = (char *)"Hit Me!";
				ti[0].nchars = 7;
				ti[0].delta = 0;
				ti[0].font = font->fid;
				XDrawText(dpy, childwin, DefaultGC(dpy, screen),
					 (width-XTextWidth(font, ti[0].chars, ti[0].nchars))/2,
					(height-(font->ascent+font->descent))/2+font->ascent,
					ti, 1);
				XUnloadFont(dpy, font->fid);
			}
			if(event.type == ButtonPress)
			{
				if(event.xbutton.button == 1)
				{
					XDrawLine(dpy, childwin, gc_darkgray, 0, 0, width-1, 0);
					XDrawLine(dpy, childwin, gc_darkgray, 0, 0, 0, height-1);
					XDrawLine(dpy, childwin, gc_lightgray, width-1, 0, width-1, height-1);
					XDrawLine(dpy, childwin, gc_lightgray, 0, height-1, width-1, height-1);
					
					bj->DealwithIt(1);
					bj->bustPercentage();
					//cout << "Button Pressed!" << endl;
				}
			}
			if(event.type == ButtonRelease)
			{
				if(event.xbutton.button == 1)
				{
					XDrawLine(dpy, childwin, gc_lightgray, 0, 0, width-1, 0);
					XDrawLine(dpy, childwin, gc_lightgray, 0, 0, 0, height-1);
					XDrawLine(dpy, childwin, gc_darkgray, width-1, 0, width-1, height-1);
					XDrawLine(dpy, childwin, gc_darkgray, 0, height-1, width-1, height-1);
				}
			}
			//if game is over: new game button should appear
		}
	}
	return 0;
}
