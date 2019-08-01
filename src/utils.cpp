
#define _CRT_SECURE_NO_WARNINGS

#define _CRT_RAND_S // pour rand_s()
#include <stdlib.h>
#include <stdio.h>

#include "utils.h"

void initrandom(int seed)
{
    srand(seed);
}

//return a random value such that
// a <= value <= b
int randomval(int a, int b)
{
    int ret;
	unsigned int randomValue;

    if (a>b)
    {
        ret=a;a=b;b=ret; // swap a,b
    }


	rand_s( &randomValue);
    double r = randomValue;
    r = a + r*(b-a+1)/UINT_MAX;

    ret = (int)(r);
    if (ret<a) // normalement ça peut pas arriver
        ret=a;
    if (ret>b) // normalement ça peut pas arriver
        ret=b;
    return(ret);
}

double randomval(double a, double b)
{
    double ret;
    if (a>b)
    {
        ret=a;a=b;b=ret; // swap a,b
    }
//    double r= rand();
//    r = a + r*(b-a+1)/(RAND_MAX+1);
	unsigned int randomValue;
rand_s( &randomValue);
    double r= randomValue;
	double deltamax=UINT_MAX; //+1.0;
    ret = a + r*(b-a)/deltamax;

    if (ret<a) // normalement ça peut pas arriver
        ret=a;
    if (ret>b) // normalement ça peut pas arriver
        ret=b;
    return(ret);
}

// arrondi à l'entier le + proche
// plus rapidement que ((int)(floor(x+0.5))) 
int fltround_to_int(double x)
{                  
    if ( x <= INT_MIN ) return(INT_MIN);
    if ( x >= INT_MAX ) return(INT_MAX);

    return( ((x)>=0) ? (int)((x)+0.5):(int)((x)-0.5));  
};



// renvoi le handle de la fenetre du programme en console
HWND GetConsoleHwnd(void) 
{ 
return(GetConsoleWindow());
#ifdef OLDVERSION
    #define MY_BUFSIZE 500 // buffer size for console window titles
    HWND hwndFound=NULL;         // this is what is returned to the caller
    char pszNewWindowTitle[MY_BUFSIZE]; // contains fabricated WindowTitle
    char pszOldWindowTitle[MY_BUFSIZE]; // contains original WindowTitle
    int cpt;

    // fetch current window title
    if ( GetConsoleTitle(pszOldWindowTitle, MY_BUFSIZE)==0 )
        return(NULL);

    // format a "unique" NewWindowTitle
    wsprintf(pszNewWindowTitle,"%d/%d",
                GetTickCount(),
                GetCurrentProcessId());

    // change current window title
    SetConsoleTitle(pszNewWindowTitle);

    cpt=100;
    while (hwndFound==NULL && cpt--)
    {
        // ensure window title has been updated
        O2G_Sleep(100);
        // look for NewWindowTitle
        hwndFound=FindWindow(NULL, pszNewWindowTitle);
    }

 
    // restore original window title
    SetConsoleTitle(pszOldWindowTitle);

    return(hwndFound);
#endif
} 

///////////////////////////////////////////////////////////////
// cache ou affiche la console
///////////////////////////////////////////////////////////////
HWND ShowConsoleWindow(BOOL on)
{
    HWND h=GetConsoleHwnd();
    if ( !h /*&& on*/)
    {
        // la console n'existe peut-etre pas. comme on veut l'afficher en, créé une
        BOOL bSuccess = AllocConsole();
        
        FILE *fret;
        fret=freopen( "CONOUT$", "w", stdout );
        fret=freopen( "CONOUT$", "w", stderr );
        fret=freopen( "CONIN$", "r", stdin );
        h=GetConsoleHwnd();
    }

    if (h)
    {
        if ( on )
        {
            // debug ON
            // fait appareitre la console
            ShowWindow(h,SW_RESTORE);
            ShowWindow(h, /*SW_SHOWMAXIMIZED*/ SW_SHOWNORMAL );
          //  SetForegroundWindow(h);
        }
        else
        {
            // debug OFF
            // eleve la console de l'ecran
            ShowWindow(h,SW_HIDE);
        }
    }
    return(h);
}
