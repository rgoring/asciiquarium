#if !defined(AFX_SAVERWINDOW_H__EED950BA_AC86_4212_9420_C029DFEDC13E__INCLUDED_)
#define AFX_SAVERWINDOW_H__EED950BA_AC86_4212_9420_C029DFEDC13E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SaverWindow.h : header file
//
#include <afxtempl.h>

#include "asciianim.h"


/////////////////////////////////////////////////////////////////////////////
// CSaverWindow window

class CSaverWindow : public CWnd
{
// Construction
public:
	CSaverWindow();
	HBRUSH m_hBackgroundBrush;
	CRect rect;
// Attributes
public:
	BOOL m_bPreview;
	CRect m_rect;

	int Height() { return m_rect.Height(); }
	int Width() { return m_rect.Width(); }
// Operations
public:
	afx_msg int Create( HWND hwndParent );
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnClose( );
    afx_msg void OnShowWindow(   BOOL bShow,   UINT nStatus );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaverWindow)
protected:
	virtual LRESULT WindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam);

	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSaverWindow();

//    CAlphaBlend m_transparent;
    POINT positionSouris;
    HCURSOR hblank_curseur, h2;

int m_nbpoissondesire;
int m_sansEau;
int m_exitOnEsc;

Caquarium aqua;
	// Generated message map functions
protected:
	//{{AFX_MSG(CSaverWindow)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	time_t m_saisie_lasttimekbd;
#define MAXSAISIE 20
	int m_saisie_car[MAXSAISIE];
	int m_saisie_nbcar;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVERWINDOW_H__EED950BA_AC86_4212_9420_C029DFEDC13E__INCLUDED_)
