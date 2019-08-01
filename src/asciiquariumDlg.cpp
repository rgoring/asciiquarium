
// asciiquariumDlg.cpp : implementation file
//

#include "stdafx.h"
#include "asciiquarium.h"
#include "asciiquariumDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ANIMATION_WINDOW_ID IDC_CREDIT 
#define REDRAW_TIMER_ID  1
#define REDRAW_TIMERVAL  75 // ms

#define DENSITE_POISSON_PREVIEW 0.15 // densité 'linéique' !
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CasciiquariumDlg dialog




CasciiquariumDlg::CasciiquariumDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CasciiquariumDlg::IDD, pParent)
    , m_nbpoisson(0)
    , m_Credit(_T(""))
    , m_SansEau(FALSE)
	, m_ExitOnlyOnESC(FALSE)
	, m_keySeq(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    espX=espY=10;
	m_saisie_lasttimekbd=0;
	m_saisie_nbcar=0;
}

void CasciiquariumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, ID_NBPOISSON, m_nbpoisson);
	DDV_MinMaxInt(pDX, m_nbpoisson, 0, 999);
	DDX_Text(pDX, IDC_CREDIT, m_Credit);
	DDX_Check(pDX, IDC_CHECKWATER, m_SansEau);
	DDX_Check(pDX, IDC_CHECKQUITESC, m_ExitOnlyOnESC);
	DDX_Text(pDX, IDC_KEYSEQ, m_keySeq);
	DDX_Control(pDX, IDC_KEYSEQ, m_edtKeySeq);
}

BEGIN_MESSAGE_MAP(CasciiquariumDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
    ON_WM_CLOSE()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_WM_TIMER()
    ON_WM_SIZE()
    ON_WM_SIZING()
    ON_BN_CLICKED(IDC_CHECKWATER, &CasciiquariumDlg::OnBnClickedCheckwater)
	ON_EN_UPDATE(IDC_KEYSEQ, &CasciiquariumDlg::OnEnUpdateKeyseq)
END_MESSAGE_MAP()


// CasciiquariumDlg message handlers

BOOL CasciiquariumDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	// TODO: Add extra initialization here

/*
MoveWindow( 100, 150, 300, 200, FALSE );

Invalidate();
UpdateWindow();
*/

m_Credit = 
"asciiquarium Windows V1.3   J.Sommer\r\n"
"based on Kirk Baucom's Asciiquarium perl script\r\n"
" http://www.robobunny.com/projects/asciiquarium\r\n"
"Credit to Joan G. Stark for the ASCII artwork\r\n"
" http://www.ascii-art.com"
;
UpdateData(FALSE);

    CWnd *w=GetDlgItem(ANIMATION_WINDOW_ID);
    if (w && ::IsWindow(w->GetSafeHwnd()) )
    {
        // recupere la postition / la fenetre
        RECT rwind;
        GetWindowRect(&rwind);
        initialCX = rwind.right-rwind.left;
        initialCY  = rwind.bottom - rwind.top;

        RECT rclient;
        GetClientRect(&rclient);

        RECT rectW;
        WINDOWPLACEMENT pl;
        w->GetWindowPlacement( &pl); // en coordonée Client
        rectW = pl.rcNormalPosition;

        espX = rclient.right - rectW.right;
        espY = rclient.bottom - rectW.bottom;;

        // initialise l'animation
      aqua.init_scene(w->GetSafeHwnd(),TRUE, 50, 1, m_SansEau, DENSITE_POISSON_PREVIEW, true);
      SetTimer( REDRAW_TIMER_ID, REDRAW_TIMERVAL, NULL );
    }



	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CasciiquariumDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CasciiquariumDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CasciiquariumDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CasciiquariumDlg::OnClose() 
{
    /*
    KillTimer(REDRAW_TIMER_ID);
    aqua.close_scene();
    */
    CDialog::OnClose();
}
void CasciiquariumDlg::OnOK() 
{
    // TODO: Add extra validation here
    KillTimer(REDRAW_TIMER_ID);
    aqua.close_scene();
    CDialog::OnOK();
}


void CasciiquariumDlg::OnCancel() 
{
    // TODO: Add extra cleanup here
    KillTimer(REDRAW_TIMER_ID);
    aqua.close_scene();
    CDialog::OnCancel();
}

void CasciiquariumDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: Add your message handler code here and/or call default
    if(nIDEvent==REDRAW_TIMER_ID)
        aqua.drawnext_scene();
    CDialog::OnTimer(nIDEvent);
}

void CasciiquariumDlg::OnSize(UINT nType, int cx, int cy)
{
     CDialog::OnSize(nType, cx, cy);
     

    // TODO: Add your message handler code here
    if( nType==SIZE_RESTORED || nType==SIZE_MAXIMIZED)
    {
        CWnd *w=GetDlgItem(ANIMATION_WINDOW_ID);
        WINDOWPLACEMENT pl;
        RECT rectW;
        if (w && ::IsWindow(w->GetSafeHwnd()) )
        {
            UpdateData(TRUE);

            w->GetWindowPlacement( &pl); // en coordonée Client
            rectW = pl.rcNormalPosition;
            w->MoveWindow( rectW.left,rectW.top, cx-rectW.left-espX, cy-rectW.top-espY, FALSE );
            // efface les bords parce que ça bave quand on réduit la taille
            RECT bord;
            bord.left = cx -espX-1;
            bord.top  = rectW.top;
            bord.bottom = cy;
            bord.right  = cx;
            InvalidateRect(&bord);
            bord.left = rectW.left;
            bord.top  = cy-espY-1;
            bord.bottom = cy;
            bord.right  = cx;
            InvalidateRect(&bord);

            UpdateWindow();

            aqua.close_scene();
            aqua.init_scene(w->GetSafeHwnd(), TRUE,50, 1, m_SansEau, DENSITE_POISSON_PREVIEW);
        }

    }
}



void CasciiquariumDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
#define XMINI_FENETRE initialCX
#define YMINI_FENETRE initialCY
    BOOL larg, haut;
    haut= (pRect->bottom- pRect->top)<YMINI_FENETRE;
    larg = (pRect->right- pRect->left)<XMINI_FENETRE;
    
    if (larg)
    {
        switch(fwSide)
        {
        case WMSZ_LEFT:
        case WMSZ_BOTTOMLEFT:
        case WMSZ_TOPLEFT:
            // on déforme à gauche=> on change le coté gauche
            pRect->left=pRect->right- XMINI_FENETRE;
            break;
        case WMSZ_RIGHT:
        case WMSZ_BOTTOMRIGHT:
        case WMSZ_TOPRIGHT:
            // on déforme à droite => on change le coté droite
            pRect->right = pRect->left+ XMINI_FENETRE;
            break;
        }
    }
    
    if (haut)
    {
        switch(fwSide)
        {
        case WMSZ_BOTTOM:
        case WMSZ_BOTTOMLEFT:
        case WMSZ_BOTTOMRIGHT:
            // on déforme en bas => on change le bas
            pRect->bottom= pRect->top + YMINI_FENETRE;
            break;
        case  WMSZ_TOP:
        case WMSZ_TOPLEFT:
        case WMSZ_TOPRIGHT:
            // on déforme en haut => on change le haut
            pRect->top = pRect->bottom - YMINI_FENETRE;
            break;
        }
    }
#undef XMINI_FENETRE 
#undef YMINI_FENETRE 


    CDialog::OnSizing(fwSide, pRect);

    // TODO: Add your message handler code here
}




void CasciiquariumDlg::OnBnClickedCheckwater()
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);

    CWnd *w=GetDlgItem(ANIMATION_WINDOW_ID);
    if (w && ::IsWindow(w->GetSafeHwnd()) )
    {
        aqua.close_scene();
        aqua.init_scene(w->GetSafeHwnd(), TRUE,50, 1, m_SansEau, DENSITE_POISSON_PREVIEW);
    }
}


BOOL CasciiquariumDlg::PreTranslateMessage(MSG* pMsg)
{

   if(pMsg->message == WM_KEYUP   )  
   {
	char car=(char)pMsg->wParam;
   }

   if(pMsg->message == WM_KEYDOWN   )  
   {
	   if (&m_edtKeySeq == this->GetFocus() )
	   {
			   time_t maintenant=time(NULL);
		   if (maintenant-m_saisie_lasttimekbd > 5) // max 10s entre chaque frappe
			   m_saisie_nbcar=0;
		   m_saisie_lasttimekbd=maintenant;
		   if (m_saisie_nbcar<MAXSAISIE)
		   {
			   char car=(char)pMsg->wParam;
			   if (car==VK_NUMPAD0) car ='0';
			   else if (car==VK_NUMPAD1) car ='1';
			   else if (car==VK_NUMPAD2) car ='2';
			   else if (car==VK_NUMPAD3) car ='3';
			   else if (car==VK_NUMPAD4) car ='4';
			   else if (car==VK_NUMPAD5) car ='5';
			   else if (car==VK_NUMPAD6) car ='6';
			   else if (car==VK_NUMPAD7) car ='7';
			   else if (car==VK_NUMPAD8) car ='8';
			   else if (car==VK_NUMPAD9) car ='9';

			   m_saisie_car[m_saisie_nbcar++]=car;
			   CString sc;
			   CString lst;
			   for(int i=0;i<m_saisie_nbcar; i++)
			   {
				   sc.Format(" %02X", m_saisie_car[i]);
				   lst+=sc;
			   }
			   m_edtKeySeq.SetWindowText(lst);
		   }
	   }
	   else
		   m_saisie_nbcar=0;
   }

   return CDialog::PreTranslateMessage(pMsg);
//	return CWnd::PreTranslateMessage(pMsg);
}

void CasciiquariumDlg::OnEnUpdateKeyseq()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.

	// TODO:  Add your control notification handler code here
	int x=0;
}
