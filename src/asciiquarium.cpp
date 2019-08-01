
// asciiquarium.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "asciiquarium.h"
#include "asciiquariumDlg.h"
#include "SaverWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CasciiquariumApp

BEGIN_MESSAGE_MAP(CasciiquariumApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CasciiquariumApp construction

CasciiquariumApp::CasciiquariumApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
    m_pSaverWindow=NULL;
}


// The one and only CasciiquariumApp object

CasciiquariumApp theApp;


// CasciiquariumApp initialization
/*
The behaviour expected of the saver depends on the command-line arguments it is given. 
If the command line arguments are invalid, then the saver should terminate immediately without doing anything.

    * /c, /c ####, or no arguments at all 
           - in response to any of these the saver should pop up its configuration dialog.
           If there are no arguments then NULL should be used as the parent: this will end up happening if the
           user clicks on the saver in the Explorer.
           With /c as an argument, the dialog should use GetForegroundWindow() as its parent. With /c #### the saver should treat #### as the decimal representation of an HWND, and use this as its parent.
    * /s - this indicates that the saver should run itself as a full-screen saver.
    * /p ####, or /l #### - here the saver should treat the #### as the decimal representation of an HWND,
          should pop up a child window of this HWND, and should run in preview mode inside that window.
*/


BOOL CasciiquariumApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization

/* les fct de registre utilise this->m_pszAppName comme 2ieme 'clé' et 
    m_pszAppName: The application name can come from the parameter passed to the CWinApp constructor, 
              or, if not specified, to the resource string with the ID of AFX_IDS_APP_TITLE. 
              If the application name is not found in the resource, it comes from the program's .EXE filename. 
*/

	SetRegistryKey(_T("O2GAME")); // "Local AppWizard-Generated Applications"



	CString csCmdLine = m_lpCmdLine;
	csCmdLine.MakeLower();


	// Get the command line flags
	int nFwdSlash = csCmdLine.FindOneOf( "/-" );
	HWND hwndParent = NULL;
#ifdef _DEBUG
	TCHAR cFlag = 'c';// 's';
#else
	TCHAR cFlag = 'C';
#endif
	if ( nFwdSlash > -1 && csCmdLine.GetLength() > nFwdSlash+1 )
		cFlag = csCmdLine[nFwdSlash+1];
	if ( cFlag == 'p' && csCmdLine.GetLength() > nFwdSlash + 3 )
		hwndParent = (HWND)atoi( &((LPCTSTR)csCmdLine)[nFwdSlash+2] );
int nbp;
int hidewater;
int exitOnEsc;
 nbp      = AfxGetApp()->GetProfileInt(   "param",   "nbpoisson",     6 );
 hidewater= AfxGetApp()->GetProfileInt(   "param",   "sansEau",       0 );
 exitOnEsc= AfxGetApp()->GetProfileInt(   "param",   "exitOnlyOnESC", 0 );

	if ( tolower(cFlag) == 'c' )
	{
		// Run configuration dialog
		CWnd* pParent = (cFlag=='c')?CWnd::GetActiveWindow():NULL;
		CasciiquariumDlg dlg( pParent );
		m_pMainWnd = &dlg;

        dlg.m_nbpoisson    = nbp;
        dlg.m_SansEau      = hidewater;
		dlg.m_ExitOnlyOnESC= exitOnEsc;


        int nResponse = dlg.DoModal();
		if (nResponse == IDOK)
		{
            AfxGetApp()->WriteProfileInt(   "param",   "nbpoisson",     dlg.m_nbpoisson);
            AfxGetApp()->WriteProfileInt(   "param",   "sansEau",       dlg.m_SansEau);
            AfxGetApp()->WriteProfileInt(   "param",   "exitOnlyOnESC", dlg.m_ExitOnlyOnESC);
        }
		else if (nResponse == IDCANCEL)
		{
		}
	}
	else
    {
        // Run screen saver either desktop or preview
        m_pSaverWindow = new CSaverWindow;

  m_pSaverWindow->m_nbpoissondesire = nbp;
  m_pSaverWindow->m_sansEau   = hidewater;
  m_pSaverWindow->m_exitOnEsc = exitOnEsc;

        if ( m_pSaverWindow->Create(hwndParent) )
        {
            m_pMainWnd = m_pSaverWindow;
			return TRUE;
		}
	}












	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


int CasciiquariumApp::ExitInstance()
{
  if (m_pSaverWindow)
     delete m_pSaverWindow;


   return CWinApp::ExitInstance();
}


