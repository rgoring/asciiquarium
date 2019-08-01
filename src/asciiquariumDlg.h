
// asciiquariumDlg.h : header file
//

#pragma once

#include "asciianim.h"
#include "afxwin.h"

// CasciiquariumDlg dialog
class CasciiquariumDlg : public CDialog
{
// Construction
public:
	CasciiquariumDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ASCIIQUARIUM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
        afx_msg void OnClose( );

	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


    Caquarium aqua;
    int espX,espY;
    int initialCX,initialCY;

public:
    int m_nbpoisson;
    BOOL m_SansEau;
	BOOL m_ExitOnlyOnESC;
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnSizing(UINT fwSide, LPRECT pRect);

    CString m_Credit;
    afx_msg void OnBnClickedCheckwater();
	CString m_keySeq;
private:
	time_t m_saisie_lasttimekbd;
#define MAXSAISIE 20
	int m_saisie_car[MAXSAISIE];
	int m_saisie_nbcar;
	bool keyseq_hasFocus;
public:
	CEdit m_edtKeySeq;
	afx_msg void OnEnUpdateKeyseq();
};
