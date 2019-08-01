
#if !defined(WCONIO_H_INCLUDED)
#define WCONIO_H_INCLUDED



bool initWindow(HWND hwnd, BOOL parentBackgroud /*if possible*/);
void closeWindow(void);

void setWindowcursor(int x, int y);
void setWindowTxtcolor(int color_fond);
void outputWindowTxt(char car);

void clrWindow(void);

void DisplayWindow(int n);

void setCurrentWindow(int n);
    void gettaille_Window( int *xSize, int *ySize);

#endif // defined(WCONIO_H_INCLUDED)
