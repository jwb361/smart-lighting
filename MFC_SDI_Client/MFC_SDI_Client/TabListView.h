#pragma once
#include "afxcmn.h"
#include "LightView.h"
#include "RoudInfoView.h"
#include "GprsInfoCtrlDlg.h"
#include "MapViewDlg.h"
#include "WarningDlg.h"
#include "MapInfomation.h"
// CTabListView form view

class CTabListView : public CFormView
{
	DECLARE_DYNCREATE(CTabListView)

protected:
	CTabListView();           // protected constructor used by dynamic creation
	virtual ~CTabListView();

public:
	enum { IDD = IDD_VIEW_DLG };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_Tab;
	virtual void OnInitialUpdate();
	void UpDateMainFrame(void);
	CRect m_rect;
	CLightView* m_LightView;
	CGprsInfoCtrlDlg* m_GprsInfoView;
	CMapViewDlg* m_pMapView;
	CWarningDlg* m_pWarningView;
	afx_msg void OnTcnSelchangeViewTab(NMHDR *pNMHDR, LRESULT *pResult);
	//CWebBrowser m_Browser1;
	void GetVolita(char* c);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	bool m_later;
};


