

#if !defined(VIEWPORT_H_INCLUDED)
#define VIEWPORT_H_INCLUDED


enum COLORS
{
    BLACK,          /* dark colors */
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,       /* light colors */
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
};


bool initViewPort(HWND hwnd, BOOL parentBackgroud /*if possible*/);
void closeViewPort(void);

void SetCurrentViewportBuffer(int n);
void DisplayViewportBuffer(int n);


void CreateViewportBuffer(int n);

void SetViewportBufferProps(void);
void SetViewportInputProps(void);


void getviewport_size( int *xSize, int *ySize);
void clearviewport(void);
int  getviewportnbevenement(void);

void setviewportcursor(int x, int y);
void setviewportcursorcolor(int color_txt);
void outputviewport(char car);


#endif // defined(VIEWPORT_H_INCLUDED)