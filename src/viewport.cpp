

#include <windows.h>


//#include "utils.h"
#include "bconio.h"
#include "wconio.h"

#include "viewport.h"

//#define USE_CONSOLE
#define USE_WINDOW

bool initViewPort(HWND hwnd, BOOL parentBackgroud /*if possible*/)
{
#ifdef USE_CONSOLE
	initconsole();
#endif
#ifdef USE_WINDOW
	initWindow(hwnd, parentBackgroud);
#endif

    return(true);
}


void closeViewPort(void)
{
#ifdef USE_CONSOLE
    closeconsole();
#endif
#ifdef USE_WINDOW
    closeWindow();
#endif
}



void SetCurrentViewportBuffer(int n)
{
#ifdef USE_CONSOLE
    setCurrentBuffer(n);
#endif
#ifdef USE_WINDOW
        setCurrentWindow(n);
#endif
}

void DisplayViewportBuffer(int n)
{
#ifdef USE_CONSOLE
    displayBuffer(n);
#endif
#ifdef USE_WINDOW
    DisplayWindow(n);
#endif
}


void CreateViewportBuffer(int n)
{
#ifdef USE_CONSOLE
    CreateBuffer(n);
#endif
#ifdef USE_WINDOW
#endif
}

void SetViewportBufferProps(void)
{
#ifdef USE_CONSOLE
    SetBufferProps();
#endif
#ifdef USE_WINDOW
#endif
}
void SetViewportInputProps(void)
{
#ifdef USE_CONSOLE
    SetInputProps();
#endif
#ifdef USE_WINDOW
#endif
}



void getviewport_size( int *xSize, int *ySize)
{
#ifdef USE_CONSOLE
    gettaille_ecran( xSize, ySize);
#endif
#ifdef USE_WINDOW
    gettaille_Window( xSize, ySize);
#endif
}

void clearviewport(void)
{
#ifdef USE_CONSOLE
    clrscr();
#endif
#ifdef USE_WINDOW
    clrWindow();
#endif
}

int getviewportnbevenement(void)
{
#ifdef USE_CONSOLE
    return(nbevenement());
#endif
#ifdef USE_WINDOW
    return(0);
#endif
}

void setviewportcursor(int x, int y)
{
#ifdef USE_CONSOLE
    gotoxy(x, y);
#endif
#ifdef USE_WINDOW
    setWindowcursor(x, y);
#endif
}
void setviewportcursorcolor(int color_txt)
{
#ifdef USE_CONSOLE
    textcolor(color_txt);
#endif
#ifdef USE_WINDOW
    setWindowTxtcolor(color_txt);
#endif
}

void outputviewport(char car)
{
#ifdef USE_CONSOLE
    putcar(car);
#endif
#ifdef USE_WINDOW
    outputWindowTxt(car);
#endif
}
