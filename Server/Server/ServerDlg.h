
// ServerDlg.h : 头文件
//

#pragma once
#include "resource.h"		// 主符号 

#include "GPRSServer.h"
#include "ClientServer.h"
#define WM_Command  WM_USER+10
#define WM_SHOWTASK WM_USER+100

// CServerDlg 对话框
class CServerDlg : public CDialog
{
// 构造
public:
	CServerDlg(CWnd* pParent = NULL);	// 标准构造函数
	NOTIFYICONDATA m_nid;
// 对话框数据
	enum { IDD = IDD_SERVER_DIALOG };
	CClientServer   m_pClientServer;
	CGPRSServer    m_pGPRSServer;
	//CClientServer  m_pClientServer;
	LRESULT OnShowTask(WPARAM wParam,LPARAM lParam);
	void OnSize(UINT nType, int cx, int cy);
	BOOL DestroyWindow();

	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedEnd();


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};

extern HWND H_ServerDlg;