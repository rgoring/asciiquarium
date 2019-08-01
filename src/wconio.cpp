

#include <windows.h>
#include <crtdbg.h> // pour _ASSERT()
#include <stdio.h>

#include "viewport.h"
#include "utils.h"
#include "wconio.h"

int PixSizeX, PixSizeY;
int xCar2Pixx;
int yCar2Pixy;


int posX, posY;
HWND m_hwnd;

HBRUSH BrushFond;
HPEN pen;
HFONT hfont;

HBRUSH OldBrush[2];
HPEN Oldpen[2];
HFONT   Oldhfont[2]; 
HBITMAP Oldbitmap[2];

COLORREF currentcolor_txt;

int currentBuffer=0;
HDC hdcvue[2];
HBITMAP bitmapvue[2];



int Taillex;
int Tailley;
char *TabCar=NULL;
COLORREF *TabAttrib=NULL;

COLORREF BackGroundColor =  RGB(  0,  0,  0);

#define LO_INTENSITY (170)
#define HI_INTENSITY (255)
#define MI_INTENSITY ((LO_INTENSITY+LO_INTENSITY)/2)

COLORREF TabColor[WHITE+1];

COLORREF InitialTabColor[WHITE+1]=
{
    /*
    RGB(           0,           0,           0),  // BLACK
    RGB(           0,           0,LO_INTENSITY),  // BLUE
    RGB(           0,LO_INTENSITY,           0),  // GREEN
    RGB(           0,LO_INTENSITY,LO_INTENSITY),  // CYAN
    RGB(LO_INTENSITY,           0,           0),  // RED
    RGB(LO_INTENSITY,           0,LO_INTENSITY),  // MAGENTA
    RGB(LO_INTENSITY,LO_INTENSITY,           0),  // BROWN
    RGB(MI_INTENSITY,MI_INTENSITY,MI_INTENSITY),  // LIGHTGRAY
    RGB(LO_INTENSITY,LO_INTENSITY,LO_INTENSITY),  // DARKGRAY
    RGB(           0,           0,HI_INTENSITY),  // LIGHTBLUE
    RGB(           0,HI_INTENSITY,           0),  // LIGHTGREEN
    RGB(           0,HI_INTENSITY,HI_INTENSITY),  // LIGHTCYAN
    RGB(HI_INTENSITY,           0,           0),  // LIGHTRED
    RGB(HI_INTENSITY,           0,HI_INTENSITY),  // LIGHTMAGENTA
    RGB(HI_INTENSITY,HI_INTENSITY,           0),  // YELLOW
    RGB(HI_INTENSITY,HI_INTENSITY,HI_INTENSITY)   // WHITE
    */

    RGB(           0,           0,           0),  // BLACK
    RGB(           0,           0,LO_INTENSITY),  // BLUE
    RGB(          24,175,          24),  // GREEN
    RGB(          20,147         , 147),  // CYAN
    RGB(LO_INTENSITY,          50,          50),  // RED
    RGB(LO_INTENSITY,           0,LO_INTENSITY),  // MAGENTA
    RGB(170,100,           23),  // BROWN
    RGB(MI_INTENSITY,MI_INTENSITY,MI_INTENSITY),  // LIGHTGRAY
    RGB(103,103,103),  // DARKGRAY
    RGB(           0,           0,HI_INTENSITY),  // LIGHTBLUE
    RGB(           0,HI_INTENSITY,           0),  // LIGHTGREEN
    RGB(          83,HI_INTENSITY,HI_INTENSITY),  // LIGHTCYAN
    RGB(HI_INTENSITY,          92,          92),  // LIGHTRED
    RGB(HI_INTENSITY,           0,HI_INTENSITY),  // LIGHTMAGENTA
    RGB(HI_INTENSITY,HI_INTENSITY,           0),  // YELLOW
    RGB(HI_INTENSITY,HI_INTENSITY,HI_INTENSITY)   // WHITE
};

////////////////////////
//calcul de couleur


double calul_1couleur(double temp1, double temp2, double temp3)
{
    double color;
    
    if (temp3 < 00.) temp3 += 1.0;
    if (temp3 > 1.0) temp3 -= 1.0;

    if( 6.0*temp3 < 1.0 )      color=temp1+(temp2-temp1)*6.0*temp3;
    else if (2.0*temp3 < 1.0 ) color=temp2;
    else if (3.0*temp3 < 2.0 ) color=temp1+(temp2-temp1)*((2.0/3.0)-temp3)*6.0;
    else color=temp1;
    
    return(color);
}
// r,g,b HSL entre 0 et 1
void CalculeValeursHSL2RGB(double H, double S, double L, 
                       double *r, double *g, double *b
                       )
{
    double temp1,temp2;
    double Rtemp3, Gtemp3, Btemp3;
    
    //  If S=0, define R, G, and B all to L
    if (S==0)
    {
        *r = *g = *b = L;
        return;
    }
    
    if (L < 0.5 )
        temp2=L*(1.0+S);
    else
        temp2=L+S - L*S;
    
    temp1 = 2.0*L - temp2;
    
    Rtemp3=H+1.0/3.0;
    Gtemp3=H;
    Btemp3=H-1.0/3.0;
    
    *r = calul_1couleur(temp1, temp2, Rtemp3);
    *g = calul_1couleur(temp1, temp2, Gtemp3);
    *b = calul_1couleur(temp1, temp2, Btemp3);
    
    return;
}


// r,g,b HSL entre 0 et 1
void CalculeValeursRGB2HSL(double r, double g, double b,
                          /* WORD wNbCouleursParPlan, */
                           double *H, double *S, double *L)
{
  double   delta, cmax, cmin;

  cmax = max(r,max(g,b));
  cmin = min(r,min(g,b));

  *L=(cmax+cmin)/2.0;
  if (cmax==cmin) 
  {
      // du gris car r=g=b
    *S = 0;
    *H = 0; // it's really undefined
  } 
  else 
  {
    if (*L < 0.5) *S = (cmax-cmin)/(cmax+cmin);
    else            *S = (cmax-cmin)/(2.0-cmax-cmin);

    delta = cmax - cmin;

    if (r==cmax) *H = (g-b)/delta;
    else 
      if (g==cmax) *H = 2.0 +(b-r)/delta;
      else         *H = 4.0 +(r-g)/delta;

    *H /= 6.0;
    if (*H < 0.0)
        *H += 1;
    if (*H > 1.0) 
        *H -= 1; // n'arrive pas

    // ?   if (*pdH>238.0/(wNbCouleursParPlan-1)) *pdH-=238.0/(wNbCouleursParPlan-1);
  }

  return;
}

// arrondi à l'entier le + proche
// plus rapidement que ((int)(floor(x+0.5))) 
int flt_to_int(double x)
{                                                     
    return( ((x)>=0) ? (int)((x)+0.5):(int)((x)-0.5));  
};                                                     


/* entre 0 et 1 */
double luminosite(COLORREF col)
{
    BYTE r = GetRValue( col );
    BYTE g = GetGValue( col );
    BYTE b = GetBValue( col );
    
    double dH, dS, dL;
    
    CalculeValeursRGB2HSL(r/255.0 , g/255.0, b/255.0, /*256,*/ &dH, &dS, &dL);

    return(dL);
}
COLORREF ModifieLuminosite(COLORREF col, double correction/*entre 0 et 1*/)
{
    BYTE r = GetRValue( col );
    BYTE g = GetGValue( col );
    BYTE b = GetBValue( col );

    double dH, dS, dL;
    
    CalculeValeursRGB2HSL(r/255.0 , g/255.0, b/255.0, /*256,*/ &dH, &dS, &dL);


    dL += correction;
    // avec inversion possible
    if(1)
    {
        while ( dL < 0.0 )
            dL += 1.0 ;
        while ( dL > 1.0 )
            dL -= 1.0 ;
    }

    if ( dL < 0.0 )  dL = 0.0 ;
    if ( dL > 1.0 )  dL = 1.0 ;


    double dr, dg, db;
    
    CalculeValeursHSL2RGB(dH , dS, dL,  &dr, &dg, &db);
    
    r=(BYTE)fltround_to_int(dr*255);
    g=(BYTE)fltround_to_int(dg*255);
    b=(BYTE)fltround_to_int(db*255);


    COLORREF ret=RGB(r,g,b);

    return( ret );
}
void AjustColor(COLORREF cfondGraphe)
{
#define LUMINOSITE_MINI_FOND (.99)
#define DELTA_LUMINOSITE     (.4)

    double lfond;

/*     
   double correctionFond;
    double lgrille;

    
    lfond = luminosite(cfondGraphe);
    if (lfond < LUMINOSITE_MINI_FOND )
        correctionFond=LUMINOSITE_MINI_FOND -lfond;
    else
        correctionFond=0;
    
    cfg->cfondGraphe= ModifieLuminosite(cfg->cfondGraphe, correctionFond);
    lgrille = luminosite(cfg->cgrille);
    if ( lgrille > lfond  && correctionFond > 0 )
    {
        // la grille était plus claire que le fond et le fond est corriger en plus clair
        // => on inverse la luminosité de la grille par rapport au fond
          //newlgrille  = LUMINOSITE_MINI_FOND - (lgrille - lfond  );
          // newlgrille  -lgrille  =  LUMINOSITE_MINI_FOND -2*lgrille + lfond  );
        double correctionGrille;
        correctionGrille = LUMINOSITE_MINI_FOND -2*lgrille + lfond ;
        cfg->cgrille= ModifieLuminosite(cfg->cgrille, correctionGrille   );

    }
*/

    lfond = luminosite(cfondGraphe);
    for (int i=0; i< NB_ELEMENT(TabColor); i++)
    {
        double l;
        double correction;

        l=luminosite(TabColor[i]);
        if ( l<lfond && (lfond-l) < DELTA_LUMINOSITE  )
        {
            correction = - ( l-(lfond-DELTA_LUMINOSITE) );
            TabColor[i] = ModifieLuminosite(TabColor[i], correction);
        }
        else if ( l>=lfond && (l-lfond) < DELTA_LUMINOSITE  )
        {
            correction = (lfond+DELTA_LUMINOSITE)- l;
            TabColor[i] = ModifieLuminosite(TabColor[i], correction);
        }
    }
}

///////////////////////
bool initWindow(HWND hwnd, BOOL parentBackgroud /*if possible*/)
{
    m_hwnd=hwnd;

    OldBrush[0]=OldBrush[1]=NULL;
    Oldpen[0]=Oldpen[1]=NULL;
    Oldhfont[0]=Oldhfont[1]=NULL; 

    memcpy(TabColor , InitialTabColor, sizeof(TabColor)) ;

    HDC hdc=GetDC(m_hwnd);

    RECT rect;
    GetWindowRect(m_hwnd,&rect);
    PixSizeX=rect.right-rect.left+1;
    PixSizeY=rect.bottom-rect.top+1;



    int hauteur=16;//20;
    bool okfont;
    int sens=0;
    do
    {
        hfont = CreateFont(
            hauteur,
            0,// // largeur si 0: automatique en fonction de la hauteur et de l'aspect de la police
            0,
            0,
            FW_BOLD, //FW_NORMAL, //FW_BOLD,//FW_THIN,//FW_BOLD, 
            0,
            0,
            0,
            ANSI_CHARSET,
            OUT_DEVICE_PRECIS,
            CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY,
            DEFAULT_PITCH|FF_SWISS,  // FF_DECORATIVE, //FF_DONTCARE,//FF_MODERN,//FF_ROMAN,//FF_SCRIPT,//FF_SWISS,
            NULL
            );

        //Définir le texte
        SIZE dims;
        HFONT oldf=(HFONT)SelectObject(hdc, hfont);
        // chaine pour calculer la taille moyenne d'un caracère
        //        #define STRINGTEST "/_&~#{[|`\\^@]é\"'(-_)$*<>=AZERTYUIOPQSDFGHJKLMWXCVBN"
#define STRINGTEST "O"
        GetTextExtentPoint32(hdc, STRINGTEST, strlen(STRINGTEST), &dims);
        SelectObject(hdc, oldf);
        xCar2Pixx = max(dims.cx/strlen(STRINGTEST),1);
        yCar2Pixy = max(dims.cy,1);

        Taillex = PixSizeX/xCar2Pixx;
        Tailley = PixSizeY/yCar2Pixy;
        // on voudrait au moins un peu de place
        if ( ( Taillex<47 || Tailley< 10 )/*&& PixSizeX>150*/ && hauteur>6 && (sens==0||sens==-1) )
        {
            sens=-1;
            DeleteObject(hfont);
            okfont=false;
            hauteur--;
            //printf("Hauteur-- =%u\n", hauteur);
        }
        else if ( ( Taillex>300 && Tailley> 30 ) && hauteur<100 && (sens==0||sens==1))
        {
            sens=1;
            DeleteObject(hfont);
            okfont=false;
            hauteur++;
            //printf("Hauteur++ =%u\n", hauteur);
        }
        else
            okfont=true;
    } while (!okfont);

    BrushFond=CreateSolidBrush(BackGroundColor);
#ifdef _DEBUG
    pen= CreatePen(PS_SOLID, 1, RGB(255,100, 100));
#else
    pen= CreatePen(PS_SOLID, 1, BackGroundColor);
#endif


    hdcvue[0] =CreateCompatibleDC(hdc);
    bitmapvue[0]=CreateCompatibleBitmap(hdc, PixSizeX, PixSizeY);

    Oldhfont[0]=(HFONT)SelectObject(hdcvue[0], hfont);

    //   SetTextAlign(hdcvue[0], TA_CENTER);


    SetBkMode(hdcvue[0], TRANSPARENT );
    SetBkColor(hdcvue[0], BackGroundColor ); // inutile car BkMode = TRANSPARENT !!!

    OldBrush[0]=(HBRUSH)SelectObject ( hdcvue[0], BrushFond);

    Oldbitmap[0]=(HBITMAP)SelectObject ( hdcvue[0], bitmapvue[0]);

    Oldpen[0] = (HPEN)SelectObject ( hdcvue[0], pen);


    hdcvue[1] =CreateCompatibleDC(hdc);
    bitmapvue[1]=CreateCompatibleBitmap(hdc, PixSizeX, PixSizeY);


    // rempli  bitmapvue[1] avec la couleur du fond (pour effacer), hdcvue[1] sert à 'effacer' hdcvue[0]
    Oldbitmap[1]=(HBITMAP)SelectObject ( hdcvue[1], bitmapvue[1]);
    Oldpen[1]   =   (HPEN)SelectObject ( hdcvue[1], pen);
    OldBrush[1] = (HBRUSH)SelectObject ( hdcvue[1], BrushFond);
    Rectangle(hdcvue[1],0,0,PixSizeX-1, PixSizeY-1); 

    COLORREF moyfond=BackGroundColor;
    if (parentBackgroud && m_hwnd && GetParent(m_hwnd))
    {
        HWND hparent=GetParent(m_hwnd);
        RECT rparent;
        GetWindowRect(hparent, &rparent);

        HDC hdc=GetWindowDC(hparent);
        HDC cpdc=CreateCompatibleDC(hdc);
        HBITMAP winbitmap=CreateCompatibleBitmap(hdc, rparent.right-rparent.left, rparent.bottom - rparent.top);
        HBITMAP oldbitmap=(HBITMAP)SelectObject ( cpdc, winbitmap);

        // recupère la zone de m_hwnd
        // ! toute les fenetre ne traite pas ce message
        //   les CDialog oui, ouf
        int ret= SendMessage(GetParent(m_hwnd), WM_PRINT, (WPARAM) cpdc, PRF_CHILDREN | PRF_CLIENT | PRF_ERASEBKGND | PRF_NONCLIENT | PRF_OWNED);
        if(ret)
        {
            // copy la partie qu'on veut
            RECT rviewport;
            GetWindowRect(m_hwnd, &rviewport);

            BitBlt(hdcvue[1], 0, 0, PixSizeX, PixSizeY, cpdc, 
                rviewport.left-rparent.left, 
                rviewport.top-rparent.top, 
                SRCCOPY);

            // calcul la couleur moyenne du fond
            // prend au hasard qque pt dans l'image...
            int nb=PixSizeX*PixSizeY/10;
            double r,g,b;
            r=g=b=0;
            for(int i=0; i<nb;i++)
            {
                COLORREF pix=GetPixel(hdcvue[1], randomval(0,PixSizeX-1), randomval(0,PixSizeY-1));
                r += GetRValue(pix);
                g += GetGValue(pix);
                b += GetBValue(pix);

            }
            if(nb)
            {
                r/=nb;
                g/=nb;
                b/=nb;
                moyfond = RGB( (BYTE)fltround_to_int(r), (BYTE)fltround_to_int(g), (BYTE)fltround_to_int(b) );
            }

        }
        else
        {
            // Beep(1000,200);
        }
        SelectObject ( cpdc, oldbitmap);
        DeleteObject(winbitmap);
        DeleteDC(cpdc);
        ReleaseDC(hparent,hdc);
    }
    //else    BitBlt(hdcvue[1], 0, 0, PixSizeX, PixSizeY, hdc, 0, 0, SRCCOPY);

    ReleaseDC(m_hwnd,hdc);

  AjustColor( moyfond );



    TabCar=new char[Taillex*Tailley];
    TabAttrib=new COLORREF[Taillex*Tailley];
    for(int i=0;i<Taillex*Tailley; i++) 
    {
        TabCar[i]=0;
        TabAttrib[i]=BackGroundColor;
    }

    setCurrentWindow(0);
    clrWindow();
    return(true);
}

void gettaille_Window( int *xSize, int *ySize)
{
    *xSize = Taillex;
    *ySize = Tailley;
}

void closeWindow(void)
{
	if (Oldhfont[0])  SelectObject(hdcvue[0], Oldhfont[0]);
	if (Oldhfont[1])  SelectObject(hdcvue[1], Oldhfont[1]);
	if (OldBrush[0])  SelectObject(hdcvue[0], OldBrush[0]);
	if (OldBrush[1])  SelectObject(hdcvue[1], OldBrush[1]);
	if (Oldpen[0]  )  SelectObject(hdcvue[0], Oldpen[0]  );
	if (Oldpen[1]  )  SelectObject(hdcvue[1], Oldpen[1]  );
	if (Oldbitmap[0]) SelectObject(hdcvue[0], Oldbitmap[0]);
	if (Oldbitmap[1]) SelectObject(hdcvue[1], Oldbitmap[1]);

	if ( hfont ) DeleteObject(hfont);
	if ( pen ) DeleteObject(pen);
	if ( BrushFond ) DeleteObject(BrushFond);

	if ( bitmapvue[0] ) DeleteObject(bitmapvue[0]); 
	if ( bitmapvue[1] ) DeleteObject(bitmapvue[1]);

	 DeleteDC (hdcvue[0]);
	 DeleteDC (hdcvue[1]);
	if(TabCar) delete []TabCar;
	if(TabAttrib) delete []TabAttrib;
}

void clrWindow(void)
{
    /*
HDC hdc = hdcvue[currentBuffer];
    BitBlt(hdc, 0, 0, PixSizeX, PixSizeY, hdcvue[1], 0, 0, BLACKNESS);
    */

int    n=1;
    // Transfer the off-screen DC to the screen
    
    BitBlt(hdcvue[0], 0, 0, PixSizeX, PixSizeY, hdcvue[n], 0, 0, SRCCOPY);


	memset(TabCar,0,sizeof(char)*Taillex*Tailley);
	memset(TabAttrib,0,sizeof(COLORREF)*Taillex*Tailley);
/*
for(int i=0;i<Taillex*Tailley; i++) 
	{
		TabCar[i]=0;
		TabAttrib[i]=BackGroundColor;
	}
	*/

}

void setCurrentWindow(int n)
{
    currentBuffer = n;
currentBuffer = 0;
}




/////////////////////////
void setWindowcursor(int x, int y)
{
_ASSERT( (x>=0) && (x<Taillex) );
_ASSERT( (y>=0) && (y<Tailley) );


    posX=x;//*xCar2Pixx;
    posY=y;//*yCar2Pixy;
}

void setWindowTxtcolor(int color_txt)
{
    currentcolor_txt=color_txt;
//    currentBrush = TabBrush[color_txt];
}

void outputWindowTxt(char car)
{
	int i=posX+posY*Taillex;

    TabCar[i]=car;
	TabAttrib[i]=currentcolor_txt;
	return;
}

void DisplayWindow(int n)
{
	// transfert le texte et affiche le buffer
	HDC hdc = hdcvue[currentBuffer];
	COLORREF prev=-1;
	for(int i=0;i<Taillex*Tailley; i++) 
	{
		if( TabCar[i]&&TabCar[i]!=' ' )
		{
 			int x=(i%Taillex)*xCar2Pixx;
			int y=(i/Taillex)*yCar2Pixy;


			if (prev!=TabColor[TabAttrib[i]])
			{
				prev=TabColor[TabAttrib[i]];
				SetTextColor(hdc, prev);
			}

			RECT rect;

			rect.top= y;
			rect.bottom=rect.top+yCar2Pixy;
			rect.left = x;
			rect.right = rect.left + xCar2Pixx;

//SetTextAlign(hdc, TA_CENTER|TA_BOTTOM);
//if(TextOut(hdc,posX,posY,&car, 1)==0)
//ExtTextOut(hdc,posX,posY, ETO_OPAQUE /*| ETO_CLIPPED*/, &rect, &car, 1, NULL);
			DrawText( hdc, &TabCar[i], 1,&rect, DT_CENTER /*|DT_NOCLIP*/|DT_SINGLELINE   | DT_VCENTER|DT_NOPREFIX);
		}



	}
	n=0;
	// Transfer the off-screen DC to the screen
	{
		HDC hdc=GetDC(m_hwnd);
		BitBlt(hdc, 0, 0, PixSizeX, PixSizeY, hdcvue[n], 0, 0, SRCCOPY);
		ReleaseDC (m_hwnd,hdc);
	}
}
