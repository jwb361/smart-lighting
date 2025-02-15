#pragma once
#include "ReportCtrl.h"
#include "SetG.h"
// CGPRSLocaInfomation dialog

class CGPRSLocaInfomation : public CDialog
{
	DECLARE_DYNAMIC(CGPRSLocaInfomation)

public:
	CGPRSLocaInfomation(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGPRSLocaInfomation();

// Dialog Data
	enum { IDD = IDD_GPRSLocal };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void ShowLocationInfo(GPRSInfo* pGetINfo);
	virtual BOOL OnInitDialog();
	CString m_gprsid;
	CString m_gprsname;
	CString m_gprsphone;
	CString m_gprsarea;
	CString m_gprslocation;
	CString m_gprstime;
	CString strID;
	CString strName;
	int     m_TerminalCount;
	CReportCtrl m_List_Terminal;
	TerminalInfo* GetSelTerminalInfo(void);
	void ShowTerminalInfo(int nTcount);
	afx_msg void OnBnClickedBtnGmodify();
	afx_msg void OnNMDblclkListTerminal(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditGid();
	CString m_GGGGGGID;
};
