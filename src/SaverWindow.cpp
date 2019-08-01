// SaverWindow.cpp : implementation file
//

//#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h" 
#include "asciiquarium.h"
#include "SaverWindow.h"

#include "asciianim.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
 
#define REDRAW_TIMER_ID  1
#define REDRAW_TIMERVAL  100 // ms


/////////////////////////////////////////////////////////////////////////////
// CSaverWindow

CSaverWindow::CSaverWindow()
{
	m_nbpoissondesire=6;
	m_sansEau   = 0;
	m_exitOnEsc =0;
	m_saisie_lasttimekbd=0;
	m_saisie_nbcar=0;
}

CSaverWindow::~CSaverWindow()
{
  aqua.close_scene();
  if ( ! m_bPreview )
  {
//      while (ShowCursor(TRUE)<0); // curseur affiché si compteur >=0

        //SetCursorPos(positionSouris.x, positionSouris.y);
  }
}


BEGIN_MESSAGE_MAP(CSaverWindow, CWnd)
	//{{AFX_MSG_MAP(CSaverWindow)
	ON_WM_CREATE()
	ON_WM_PAINT()
ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



// Following Code taken from Ben Bryant's Smoov Saver. A great saver!
BOOL CSaverWindow::Create( HWND hwndParent )
{
    hblank_curseur=AfxGetApp()->LoadCursor(IDC_CURSOR1);
    h2=AfxGetApp()->LoadCursor(IDC_CURSOR2);



    // Register a class with no cursor.
    const char* pszClassName 
        = AfxRegisterWndClass(
        CS_HREDRAW|CS_VREDRAW|CS_SAVEBITS|CS_DBLCLKS, /* style*/
        hblank_curseur /* curseur*/ // un curseur vide pour ne pas afficher le curseur de souris*/
        );

#ifdef _DEBUG
	DWORD dwExStyle = 0; // pour pouvoir debuger, sinon la fenetre couvre tout l'ecran
#else
	DWORD dwExStyle = WS_EX_TOPMOST;
#endif
	DWORD dwStyle = WS_POPUP | WS_VISIBLE;
	m_bPreview = FALSE;

	if ( hwndParent )
	{
		// Get dimensions of preview window
		::GetClientRect( hwndParent, &rect );
		dwExStyle = 0;
		dwStyle = WS_CHILD | WS_VISIBLE;
		m_bPreview = TRUE;
        
	}
	else
	{
        rect.left = ::GetSystemMetrics( SM_XVIRTUALSCREEN );
        rect.top = ::GetSystemMetrics( SM_YVIRTUALSCREEN );
        rect.right = rect.left + ::GetSystemMetrics( SM_CXVIRTUALSCREEN ); //*2/3;
        rect.bottom = rect.top + ::GetSystemMetrics( SM_CYVIRTUALSCREEN ); //*2/3;
if(0)
{
        rect.left = 10;
        rect.top = 100;
        rect.right = rect.left + 800; //::GetSystemMetrics( SM_CXSCREEN );
        rect.bottom = rect.top + 500;//::GetSystemMetrics( SM_CYSCREEN );
}


	}

    return CWnd::CreateEx( dwExStyle, pszClassName, "", dwStyle,
		rect.left, rect.top, rect.Width(), rect.Height(), hwndParent, NULL );

}

void bouge(void)
{
  INPUT tinput[5];
int deb=0;

    tinput[deb].type=INPUT_MOUSE;
    tinput[deb].mi.dx=1;
    tinput[deb].mi.dy=1;
    tinput[deb].mi.mouseData=0;
    tinput[deb].mi.dwFlags=MOUSEEVENTF_MOVE;
    tinput[deb].mi.time=0;
    tinput[deb].mi.dwExtraInfo=NULL;
deb++;
if(1)
{
    tinput[deb].type=INPUT_MOUSE;
    tinput[deb].mi.dx=-1;
    tinput[deb].mi.dy=-1;
    tinput[deb].mi.mouseData=0;
    tinput[deb].mi.dwFlags=MOUSEEVENTF_MOVE;
    tinput[deb].mi.time=0;
    tinput[deb].mi.dwExtraInfo=NULL;
deb++;
}
    UINT ret =SendInput(deb, tinput,  sizeof(INPUT) );
    if (ret!=(UINT)deb)
    {
        Beep(1000,50);
    }
}

LRESULT CSaverWindow::WindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	static int i = 0;
	static PAINTSTRUCT ps = {NULL};
	static HDC hDC = NULL;
	static HBRUSH hBrush = NULL;
	static UINT uTimer = 0;
	static int xpos, ypos;
	static RECT rc;

    static BOOL bHere = FALSE;
    static POINT ptLast;
    POINT ptCursor, ptCheck;
	CRect rectWnd;

    switch ( nMsg )
	{
 
    case WM_SYSCOMMAND:
        if ( (wParam == SC_SCREENSAVE) || (wParam == SC_CLOSE) )
            return FALSE;
        break;

    case WM_ERASEBKGND:
//#ifdef XXXX
		GetClientRect(&rectWnd);
		//FillRect( (HDC)wParam, &rectWnd, m_hBackgroundBrush );
		
  if ( ! m_bPreview )
  {
      //SetCursor( NULL );
      SetCursor(hblank_curseur);
      SetCursor(h2);
      
      //while(ShowCursor(FALSE)>=0);// curseur pas affiché si compteur <0
  }
//#endif
		break;

               
    case WM_SETCURSOR:
		if ( ! m_bPreview )
        {
	        //SetCursor( NULL );
            //SetCursor( hblank_curseur );
      SetCursor(hblank_curseur);
      SetCursor(h2);

      SetCursor( NULL );

        }
        break;

    case WM_NCACTIVATE:
		if ( ! m_bPreview )
			if ( wParam == FALSE )
				return FALSE;
        break;

    case WM_ACTIVATE:
    case WM_ACTIVATEAPP:
		if ( m_bPreview )
			break;
        if ( wParam != FALSE )
			break;
        // Only fall through if we are losing the focus...

    case WM_MOUSEMOVE:
		if ( m_bPreview || m_exitOnEsc )
			break;
		if( ! bHere )
		{
			GetCursorPos( &ptLast );
			bHere = TRUE;
		}
		else
		{
			GetCursorPos( &ptCheck );
			ptCursor.x = ptCheck.x - ptLast.x;
			ptCursor.y = ptCheck.y - ptLast.y;
			if ( ptCursor.x < 0 )
				ptCursor.x *= -1;
			if ( ptCursor.y < 0 )
				ptCursor.y *= -1;
			if ( (ptCursor.x + ptCursor.y) > 5 )
				PostMessage( WM_CLOSE, 0, 0 );
		}
        break;

    case WM_RBUTTONDOWN:
    case WM_LBUTTONDOWN:
    case WM_MBUTTONDOWN:
		if ( m_bPreview || m_exitOnEsc )
			break;
		// a quoi ça sert ???
        GetCursorPos( &ptCursor );
        ptCursor.x ++;
        ptCursor.y ++;
        SetCursorPos( ptCursor.x, ptCursor.y );
        GetCursorPos( &ptCheck );
        if ( ptCheck.x != ptCursor.x && ptCheck.y != ptCursor.y )
	        ptCursor.x -= 2;
        ptCursor.y -= 2;
        SetCursorPos( ptCursor.x, ptCursor.y );

		if ( m_bPreview )
			break;
        PostMessage(WM_CLOSE, 0, 0l);
        break;
    case WM_KEYDOWN:
		{
	   time_t maintenant=time(NULL);
	   if (maintenant-m_saisie_lasttimekbd > 5) // max 10s entre chaque frappe
		   m_saisie_nbcar=0;
	   m_saisie_lasttimekbd=maintenant;
			int vk_code=wParam;
			if ( m_exitOnEsc && (wParam!=VK_ESCAPE) )
			{
				break;
			}
			PostMessage(WM_CLOSE, 0, 0l);
		}
        break;
    case WM_SYSKEYDOWN:
		{
	   time_t maintenant=time(NULL);
	   if (maintenant-m_saisie_lasttimekbd > 5) // max 10s entre chaque frappe
		   m_saisie_nbcar=0;
	   m_saisie_lasttimekbd=maintenant;
			int vk_code=wParam;
			if ( m_bPreview || m_exitOnEsc )
				break;
			PostMessage(WM_CLOSE, 0, 0l);
		}
        break;
    case WM_TIMER:
        if( wParam==REDRAW_TIMER_ID)
        {
		if (aqua.drawnext_scene() )
            PostMessage(WM_QUIT,0,0);
            if( 0 )
            {
                KillTimer(REDRAW_TIMER_ID);
                bouge();
            }
            //m_transparent.SetOpacity(opacite);
            
        }
        break;
    }

    return CWnd::WindowProc(nMsg, wParam, lParam);
}
///////////////////Back to my own work//////////////////////
///////

int CSaverWindow::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{

	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_hBackgroundBrush = CreateSolidBrush(RGB(0, 0, 0));


    //m_transparent.SetWindowHandle(this);
    //m_transparent.SetTransparent(this->m_hWnd, 0, TRUE);

	GetClientRect( &m_rect );
//	m_ae.SetScreen( m_rect );

    
      if ( ! m_bPreview )
      {
            GetCursorPos(&positionSouris);

      }

      //::SetClassLong(this->m_hWnd,GCL_HCURSOR,  (LONG) hblank_curseur);   

 
    aqua.init_scene(this->m_hWnd,FALSE, REDRAW_TIMERVAL, m_nbpoissondesire,m_sansEau, m_bPreview ? 0.15 : -1);
    SetTimer( REDRAW_TIMER_ID, REDRAW_TIMERVAL, NULL );
	return 0;
}

void CSaverWindow::OnClose() 
{
    KillTimer(REDRAW_TIMER_ID);
    aqua.close_scene();

	CWnd::OnClose();
}

void CSaverWindow::OnShowWindow(   BOOL bShow,   UINT nStatus )
{

    CWnd::OnShowWindow(    bShow,    nStatus );
    if ( ! m_bPreview && bShow)
    {
        //SetCursor( NULL );
        //SetCursor( hblank_curseur );
        //while(ShowCursor(FALSE)>=0);// curseur pas affiché si compteur <0



        POINT ptCursor;
        GetCursorPos( &ptCursor );
        SetCursorPos( 0, 0 );
        SetCursorPos( ptCursor.x, ptCursor.y );

        SetActiveWindow();
        SetForegroundWindow();
        SetFocus();
        bouge();
    }
#ifdef XXX
#endif

}

void CSaverWindow::OnPaint() 
{

	CPaintDC dc(this); // device context for painting

	CPoint myPoint;
	myPoint = rect.CenterPoint();

	// TODO: Add your message handler code here
	CDC* pDC = GetDC();
	//CSaverWindow scrWnd;

	CRect textRect;
	//textRect.CenterPoint() = rect.CenterPoint();
	textRect.top = (rect.top);
	textRect.left = (rect.left);


	//pDC->DrawIcon(myPoint,AfxGetApp()->LoadStandardIcon(IDI_QUESTION));
	//pDC->DrawText("This will only show on the default monitor",textRect,NULL);

	// Do not call CWnd::OnPaint() for painting messages
    
}





