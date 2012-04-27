#pragma once

#include "resource.h"
// CDoRWorkDlg dialog
#include "FileView.h"
class CDoRWorkDlg : public CDialog
{
	DECLARE_DYNAMIC(CDoRWorkDlg)

public:
	CDoRWorkDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDoRWorkDlg();

// Dialog Data
	enum { IDD = IDD_DoRWorkDlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void UpdateRoadstatus(bool nbool);
 	CString m_RName;
	CString RID;
	CString m_status;
	CString m_szLID1;
protected:
	virtual void OnCancel();
	virtual void PostNcDestroy();
	afx_msg void OnBnClickedBtnAll();
	afx_msg void OnBnClickedBtnAll11();
	
public:
	afx_msg void OnEnChangeRname();
};

////////////////
