
#if !defined(BCONIO_H_INCLUDED)
#define BCONIO_H_INCLUDED

#ifndef _BCONIO_C_
extern int _wscroll;
extern int directvideo;
#endif

bool initconsole(void);
void closeconsole(void);

void setCurrentBuffer(int n);
void displayBuffer(int n);

void CreateBuffer(int n);
void SetBufferProps(void);
void SetInputProps(void);



void putcar(char car);


int nbevenement(void);



void gotoxy(int x, int y);
int wherex(void);
int wherey(void);

#define _NOCURSOR      0
#define _NORMALCURSOR  1

typedef unsigned short      WORD;

void _setcursortype(int type);

void clrscr(void);

enum bCOLORS
{
    bBLACK,          /* dark colors */
    bBLUE,
    bGREEN,
    bCYAN,
    bRED,
    bMAGENTA,
    bBROWN,
    bLIGHTGRAY,
    bDARKGRAY,       /* light colors */
    bLIGHTBLUE,
    bLIGHTGREEN,
    bLIGHTCYAN,
    bLIGHTRED,
    bLIGHTMAGENTA,
    bYELLOW,
    bWHITE
};

void textbackground(int color_fond);
void textcolor(int color_fond);
char *copy_screen( void );
WORD *copy_screenAttrib(void);


void gettaille_ecran( int *xSize, int *ySize);

void taille_ecran( int xSize, int ySize);

//void window( int left, int top, int right, int bottom);

#endif // defined(BCONIO_H_INCLUDED)
