
//#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <signal.h>
#include <stdio.h>

#include "utils.h"

#define _BCONIO_C_
#include "bconio.h"
#undef _BCONIO_C_



int _wscroll=0;
int directvideo=0;

#define MAX_SCREENBUFFER (2)
HANDLE TabHandle[MAX_SCREENBUFFER]={NULL,NULL};
HANDLE CurrentConsoleOutput=GetStdHandle(STD_OUTPUT_HANDLE);

/////////////////////////////////////////////////////////////////////////

#ifdef EXISTE_PAS_AILLEURS
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
#endif
///////////////////////////////////////////////////////////////////////////

bool SignalRecu = false;
void __cdecl signal_arret ( int sig  )
{
    SignalRecu = true;
    Beep(500,30);
}


bool initconsole(void)
{
    bool ret=   ShowConsoleWindow(TRUE)!=NULL;
    if(ret)
    {
        signal( SIGINT  , signal_arret);
        signal( SIGTERM , signal_arret);
        signal( SIGBREAK, signal_arret);
        signal( SIGABRT , signal_arret);
    }
    return(ret);
}
void closeconsole(void)
{
    ShowConsoleWindow(FALSE) ;
}

///////////////////////////////////////////////////////////////////////////

void setCurrentBuffer(int n)
{
	HANDLE h;
	if (n<MAX_SCREENBUFFER && n>=0)
		h=TabHandle[n];
	else h=NULL;
	if (h==NULL)
		h=GetStdHandle(STD_OUTPUT_HANDLE);

	CurrentConsoleOutput=h;
//SetStdHandle(STD_OUTPUT_HANDLE,  HANDLE hHandle  );
//freopen( "CONOUT$", "w", stdout );
}

void displayBuffer(int n)
{
	HANDLE h;
	if (n<MAX_SCREENBUFFER && n>=0)
		h=TabHandle[n];
	else h=NULL;
	if (h==NULL)
		h=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleActiveScreenBuffer(h);
}

void SetInputProps(void)
{

    HANDLE inh= GetStdHandle(STD_INPUT_HANDLE);
    DWORD dwStdInMode;

    if ( GetConsoleMode(inh, &dwStdInMode) )
    {
     /* when turning off ENABLE_LINE_INPUT, you MUST also turn off  ENABLE_ECHO_INPUT. */
     //dwStdInMode = (dwStdInMode & ~(ENABLE_LINE_INPUT |ENABLE_ECHO_INPUT)) | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT
        dwStdInMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
        SetConsoleMode(inh, dwStdInMode );
    }
}

void SetBufferProps(void)
{
    if(0)
    {
        COORD coo;
        coo.X = 100;
        coo.Y = 100;
        if(SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE),CONSOLE_FULLSCREEN_MODE, &coo )==0)
        {
            int err=GetLastError();
        }
        coo.Y=coo.Y;
    }



	CONSOLE_FONT_INFO cfont;
	if( GetCurrentConsoleFont(CurrentConsoleOutput,FALSE,&cfont) )
	{
		COORD coo=GetConsoleFontSize(CurrentConsoleOutput, cfont.nFont);
int x=0;

	}


    // désacive 'wrap' en fin de ligne
    DWORD mode;
    if ( GetConsoleMode(CurrentConsoleOutput, &mode) )
    {
     /* when turning off ENABLE_LINE_INPUT, you MUST also turn off  ENABLE_ECHO_INPUT. */
     //dwStdInMode = (dwStdInMode & ~(ENABLE_LINE_INPUT |ENABLE_ECHO_INPUT)) | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT
        mode = mode & ~(ENABLE_WRAP_AT_EOL_OUTPUT);
        SetConsoleMode(CurrentConsoleOutput, mode );
    }



	// taille de la fenetre
	COORD coordScreen;

	/* get the largest size we can size the console window to */
	coordScreen = GetLargestConsoleWindowSize(CurrentConsoleOutput);
//coordScreen.X=90; coordScreen.Y=50; ////////<==================================debug
	taille_ecran( coordScreen.X, coordScreen.Y);
	_setcursortype(_NOCURSOR);
}

void CreateBuffer(int n)
{
	if (n<MAX_SCREENBUFFER && n>=0)
	{
		TabHandle[n]=CreateConsoleScreenBuffer(GENERIC_READ|GENERIC_WRITE ,FILE_SHARE_READ|FILE_SHARE_WRITE ,NULL,CONSOLE_TEXTMODE_BUFFER,NULL);
        setCurrentBuffer(n);


             COORD coo;
             coo.X = 100;
             coo.Y = 100;
//		if(SetConsoleDisplayMode(TabHandle[n],CONSOLE_FULLSCREEN_MODE, &coo )==0) 
        {
            int err=GetLastError();
        }
	}
}

void putcar(char car)
{
    DWORD wr;
    WriteConsole(CurrentConsoleOutput, &car,1,&wr,NULL);
}

int nbevenement(void)
{
    DWORD lpcNumberOfEvents;
    if(SignalRecu) return(1);
    if ( GetNumberOfConsoleInputEvents(GetStdHandle(STD_INPUT_HANDLE),&lpcNumberOfEvents) )
        return(lpcNumberOfEvents);
    Beep(600,100);
    return(0);
}


void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
  
    SetConsoleCursorPosition(CurrentConsoleOutput, c);
    /* STD_INPUT_HANDLE STD_OUTPUT_HANDLE STD_ERROR_HANDLE */
}

int wherex(void)
{
    CONSOLE_SCREEN_BUFFER_INFO ConsoleScreenBufferInfo;
    
    GetConsoleScreenBufferInfo(CurrentConsoleOutput,  &ConsoleScreenBufferInfo );
    
    return( ConsoleScreenBufferInfo.dwCursorPosition.X );
    /* STD_INPUT_HANDLE STD_OUTPUT_HANDLE STD_ERROR_HANDLE */
}
int wherey(void)
{
    CONSOLE_SCREEN_BUFFER_INFO ConsoleScreenBufferInfo;
    
    GetConsoleScreenBufferInfo(CurrentConsoleOutput,  &ConsoleScreenBufferInfo );
    
    return( ConsoleScreenBufferInfo.dwCursorPosition.Y );
    /* STD_INPUT_HANDLE STD_OUTPUT_HANDLE STD_ERROR_HANDLE */
}


/*
#define _NOCURSOR      0
#define _NORMALCURSOR  1
*/
void _setcursortype(int type)
{
  CONSOLE_CURSOR_INFO cci; /* used when turning off the cursor */


  GetConsoleCursorInfo(CurrentConsoleOutput, &cci);
  cci.bVisible = type==_NOCURSOR? FALSE : TRUE ;
  SetConsoleCursorInfo(CurrentConsoleOutput, &cci);

}

void clrscr(void)
{
  HANDLE hConsole;


  COORD coordScreen = { 0, 0 }; /* here's where we'll home the cursor */
  BOOL bSuccess;
  DWORD cCharsWritten;
  CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */
  DWORD dwConSize; /* number of character cells in the current buffer */

  hConsole=CurrentConsoleOutput;
  /* get the number of character cells in the current buffer */
  bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);

  dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
  /* fill the entire screen with blanks */
  bSuccess = FillConsoleOutputCharacter(hConsole, (TCHAR) ' ',
      dwConSize, coordScreen, &cCharsWritten);
  /* get the current text attribute */
  bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);
  /* now set the buffer's attributes accordingly */
  bSuccess = FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
      dwConSize, coordScreen, &cCharsWritten);
  /* put the cursor at (0, 0) */
  bSuccess = SetConsoleCursorPosition(hConsole, coordScreen);
}


int get_winForgroundColor(int borlandColor)
{
    switch(borlandColor)
    {
    case bBLACK:    return(0);
    case bBLUE:     return(FOREGROUND_BLUE);
    case bGREEN:    return(FOREGROUND_GREEN);
    case bCYAN:     return(FOREGROUND_GREEN|FOREGROUND_BLUE);
    case bRED:      return(FOREGROUND_RED);
    case bMAGENTA:  return(FOREGROUND_RED|FOREGROUND_BLUE);
    case bBROWN:    return(FOREGROUND_RED|FOREGROUND_GREEN);
    case bLIGHTGRAY:return(FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

    case bDARKGRAY    :return(FOREGROUND_INTENSITY);
    case bLIGHTBLUE   :return(FOREGROUND_BLUE|FOREGROUND_INTENSITY);
    case bLIGHTGREEN  :return(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
    case bLIGHTCYAN   :return(FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
    case bLIGHTRED    :return(FOREGROUND_RED|FOREGROUND_INTENSITY);
    case bLIGHTMAGENTA:return(FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
    case bYELLOW      :return(FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
    case bWHITE       :return(FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
    }
    return(0);
}
int get_winBackgroundColor(int borlandColor)
{
    switch(borlandColor)
    {
    case bBLACK:    return(0);
    case bBLUE:     return(BACKGROUND_BLUE);
    case bGREEN:    return(BACKGROUND_GREEN);
    case bCYAN:     return(BACKGROUND_GREEN|BACKGROUND_BLUE);
    case bRED:      return(BACKGROUND_RED);
    case bMAGENTA:  return(BACKGROUND_RED|BACKGROUND_BLUE);
    case bBROWN:    return(BACKGROUND_RED|BACKGROUND_GREEN);
    case bLIGHTGRAY:return(BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);

    case bDARKGRAY    :return(BACKGROUND_INTENSITY);
    case bLIGHTBLUE   :return(BACKGROUND_BLUE|BACKGROUND_INTENSITY);
    case bLIGHTGREEN  :return(BACKGROUND_GREEN|BACKGROUND_INTENSITY);
    case bLIGHTCYAN   :return(BACKGROUND_GREEN|BACKGROUND_BLUE|BACKGROUND_INTENSITY);
    case bLIGHTRED    :return(BACKGROUND_RED|BACKGROUND_INTENSITY);
    case bLIGHTMAGENTA:return(BACKGROUND_RED|BACKGROUND_BLUE|BACKGROUND_INTENSITY);
    case bYELLOW      :return(BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_INTENSITY);
    case bWHITE       :return(BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|BACKGROUND_INTENSITY);
    }
    return(0);
}

void textbackground(int color_fond)
{
    HANDLE hConsole;
    WORD attr;
    CONSOLE_SCREEN_BUFFER_INFO ConsoleScreenBufferInfo;
    
    hConsole=CurrentConsoleOutput;
    
    GetConsoleScreenBufferInfo(CurrentConsoleOutput,  &ConsoleScreenBufferInfo );
    attr = ConsoleScreenBufferInfo.wAttributes;
    // ne garde que la couleur du caractere
    attr = attr & (FOREGROUND_BLUE |FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
    
    attr = attr | get_winBackgroundColor(color_fond);
    SetConsoleTextAttribute(hConsole, attr);
}
void textcolor(int color_fond)
{
    HANDLE hConsole;
    WORD attr;
    CONSOLE_SCREEN_BUFFER_INFO ConsoleScreenBufferInfo;
    
    hConsole=CurrentConsoleOutput;
    
    GetConsoleScreenBufferInfo(CurrentConsoleOutput,  &ConsoleScreenBufferInfo );
    attr = ConsoleScreenBufferInfo.wAttributes;
    // ne garde que la couleur du fond
    attr = attr & (BACKGROUND_BLUE |BACKGROUND_GREEN|BACKGROUND_RED|BACKGROUND_INTENSITY);
    
    attr = attr | get_winForgroundColor(color_fond);
    SetConsoleTextAttribute(hConsole, attr);
}

void window( int left, int top, int right, int bottom)
{
}

#define PERR(bSuccess, api) {if (!(bSuccess)) Beep(100,500);/*perr(__FILE__, __LINE__, api, GetLastError());*/}

void taille_ecran( int xSize, int ySize)
{
    HANDLE hConsole;
    

    CONSOLE_SCREEN_BUFFER_INFO csbi; /* hold current console buffer info */
  BOOL bSuccess;
  SMALL_RECT srWindowRect; /* hold the new console size */
  COORD coordScreen;

    hConsole=CurrentConsoleOutput;

  bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);
  PERR(bSuccess, "GetConsoleScreenBufferInfo");
  /* get the largest size we can size the console window to */
  coordScreen = GetLargestConsoleWindowSize(hConsole);
  PERR(coordScreen.X | coordScreen.Y, "GetLargestConsoleWindowSize");
  // limit to max allowed
  xSize = min(xSize, coordScreen.X); 
  ySize = min(ySize, coordScreen.Y);

  /* define the new console window size and scroll position */
  srWindowRect.Right  = xSize - 1;
  srWindowRect.Bottom = ySize - 1;
  srWindowRect.Left   = srWindowRect.Top = 0;
  /* define the new console buffer size */
  coordScreen.X = xSize;
  coordScreen.Y = ySize;

  // reduit la ConsoleWindow a minimum
  // comme ça la taille por SetConsoleScreenBufferSize sera toujour plus grande

  // ConsoleScreenBufferSize ne doit pas etre inférieur à la taille actuel de la ConsoleWindow
  // si c'est le cas, on réduit la taille de  la ConsoleWindow
  SMALL_RECT sr=csbi.srWindow;
  bool changed=false;
  if ( xSize< (csbi.srWindow.Right-csbi.srWindow.Left+1) )
  {
      changed=true; // on reduit
      sr.Right -=  (csbi.srWindow.Right-csbi.srWindow.Left+1) - xSize; 
  }
  if ( ySize< (csbi.srWindow.Bottom-csbi.srWindow.Top+1) )
  {
      changed=true;  // on reduit
      sr.Bottom -=  (csbi.srWindow.Bottom-csbi.srWindow.Top+1) - ySize; 
  }
  if( changed )
  {
      bSuccess = SetConsoleWindowInfo(hConsole, TRUE, &sr);
      PERR(bSuccess, "SetConsoleWindowInfo");
  }

  bSuccess = SetConsoleScreenBufferSize(hConsole, coordScreen);
  PERR(bSuccess, "SetConsoleScreenBufferSize");
  bSuccess = SetConsoleWindowInfo(hConsole, TRUE, &srWindowRect);
  PERR(bSuccess, "SetConsoleWindowInfo");

#ifdef XXX
  /* if the current buffer is larger than what we want, resize the */
  /* console window first, then the buffer */
  if ( (DWORD) csbi.dwSize.X * csbi.dwSize.Y > (DWORD) xSize * ySize)
    {
    bSuccess = SetConsoleWindowInfo(hConsole, TRUE, &srWindowRect);
    PERR(bSuccess, "SetConsoleWindowInfo");
    bSuccess = SetConsoleScreenBufferSize(hConsole, coordScreen);
    PERR(bSuccess, "SetConsoleScreenBufferSize");
    }
  /* if the current buffer is smaller than what we want, resize the */
  /* buffer first, then the console window */
  if (1||(DWORD) csbi.dwSize.X * csbi.dwSize.Y < (DWORD) xSize * ySize)
    {
    bSuccess = SetConsoleScreenBufferSize(hConsole, coordScreen);
    PERR(bSuccess, "SetConsoleScreenBufferSize");
    bSuccess = SetConsoleWindowInfo(hConsole, TRUE, &srWindowRect);
    PERR(bSuccess, "SetConsoleWindowInfo");
    }
  /* if the current buffer *is* the size we want, don't do anything! */
#endif

  return;
}

void gettaille_ecran( int *xSize, int *ySize)
{
    HANDLE hConsole;
    

    CONSOLE_SCREEN_BUFFER_INFO csbi; /* hold current console buffer info */
  BOOL bSuccess;

    hConsole=CurrentConsoleOutput;

  bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);
  PERR(bSuccess, "GetConsoleScreenBufferInfo");

  *xSize = csbi.srWindow.Right-csbi.srWindow.Left+1;
  *ySize= csbi.srWindow.Bottom-csbi.srWindow.Top+1;
}

char *copy_screen( void )
{
    char *buffer;
    HANDLE hConsole;
    COORD coor;
    DWORD NumberOfCharsRead;
  DWORD dwConSize; /* number of character cells in the current buffer */
  CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */
    
    hConsole=CurrentConsoleOutput;

  GetConsoleScreenBufferInfo(hConsole, &csbi);
  dwConSize = csbi.dwSize.X * csbi.dwSize.Y;


    
    coor.X=0;
    coor.Y=0;

    buffer=(char*)malloc(dwConSize*sizeof(char)+1);
    if (buffer==NULL) return(NULL);
    if ( ReadConsoleOutputCharacter(
        hConsole,
        buffer,
        dwConSize,      // number of character cells to read from
        coor,
        &NumberOfCharsRead ) == 0)
    {
        free(buffer);
        return(NULL);
    }
    else
    {
        buffer[NumberOfCharsRead]=0;
        return(buffer);
    }
}

WORD *copy_screenAttrib(void)
{
    WORD *buffer;
    HANDLE hConsole;
    COORD coor;
    DWORD NumberOfCharsRead;
  DWORD dwConSize; /* number of character cells in the current buffer */
  CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */
    
    hConsole=CurrentConsoleOutput;

  GetConsoleScreenBufferInfo(hConsole, &csbi);
  dwConSize = csbi.dwSize.X * csbi.dwSize.Y;


    
    coor.X=0;
    coor.Y=0;

    buffer=(WORD*)malloc(dwConSize*sizeof(WORD)+1);
    if (buffer==NULL) return(NULL);
    if ( ReadConsoleOutputAttribute(
        hConsole,
        buffer,
        dwConSize,      // number of character cells to read from
        coor,
        &NumberOfCharsRead ) == 0)
    {
        free(buffer);
        return(NULL);
    }
    else
    {
        return(buffer);
    }
}

