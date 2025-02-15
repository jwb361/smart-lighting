
// MFC_SDI_Client.cpp : 定义应用程序的类行为。
//


#include "stdafx.h"
#include "afxwinappex.h"
#include "MFC_SDI_Client.h"
#include "MainFrm.h"
#include "LoginDlg.h"
#include "MFC_SDI_ClientDoc.h"
#include "MFC_SDI_ClientView.h"
#include "SetG.h"
#include "ModifyAllDlg.h"
#include "TestDlg.h"
#include "CWebBrowser.h"
#include "CWebBrowser2.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CMFC_SDI_ClientApp
BEGIN_MESSAGE_MAP(CMFC_SDI_ClientApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CMFC_SDI_ClientApp::OnAppAbout)
	// 基于文件的标准文档命令
//	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
//	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	ON_COMMAND(ID_SETUSER, &CMFC_SDI_ClientApp::OnSetuser)
	ON_COMMAND(ID_SetG, &CMFC_SDI_ClientApp::OnSetg)
	ON_COMMAND(ID_Modify, &CMFC_SDI_ClientApp::OnModify)
	ON_COMMAND(ID_CAgain, &CMFC_SDI_ClientApp::OnCagain)
	ON_COMMAND(ID_32783, &CMFC_SDI_ClientApp::On32783)
	ON_UPDATE_COMMAND_UI(ID_CAgain, &CMFC_SDI_ClientApp::OnUpdateCagain)
	ON_COMMAND(ID_RENEW, &CMFC_SDI_ClientApp::OnRenew)
END_MESSAGE_MAP()


// CMFC_SDI_ClientApp 构造

CMFC_SDI_ClientApp::CMFC_SDI_ClientApp()
: m_return(false)
, m_InitTrue(false)
, m_connected(false)
, m_DlgMainONStatus(false)
, m_DlgMainOFFStatus(false)
, m_DlgAssistONStatus(false)
, m_DlgAssistOFFStatus(false)
, m_DlgDoubleONStatus(false)
, m_DlgDoubleOFFStatus(false)
, nWarningCount(0)
, m_where(false)
, nGeshu(0)
{
	m_bHiColorIcons = TRUE;
	h1=NULL;
	ZeroMemory(nStatus,4);
	ZeroMemory(sendTerminal,4);
	nRCount=0;
	//m_Desition=0x00;
	//m_InitInfo=(IintInfo*)malloc(sizeof(IintInfo));
	//ZeroMemory(m_InitInfo,sizeof(IintInfo));
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CMFC_SDI_ClientApp 对象

CMFC_SDI_ClientApp theApp;


// CMFC_SDI_ClientApp 初始化

BOOL CMFC_SDI_ClientApp::InitInstance()
{
//  	CSplashWnd* pSplash = new CSplashWnd;
//  	pSplash->ShowWindow(m_nCmdShow);
//// 	Sleep(2500);
	//如果一个运行在 Windows XP 上的应用程序清单指定要
	//使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
//这是代码区 有用的
 	 while(!m_InitTrue)
 	{
   		while (!m_return)
   			{
   				CLoginDlg dlg;
   				if (dlg.DoModal()==IDCANCEL)
   				{
   					return false;
   					break;
   				}
   				else
   				{
   					GetPrivateProfileString("Server","serverip",NULL,m_ip,20,"D:\\server.ini");
   					m_port=GetPrivateProfileInt("Server","serverport",0,"D:\\server.ini");
   					strNamePass.Format(_T("%s"),dlg.m_szNamePassword);
   					h1=::CreateThread(NULL, 0, ConnectThreadFunc, this, 0, NULL);
  					Sleep(5000);
   				}
   			}
 			char a[3]={'L','G','#'};
 			send(m_ConnectSock,a,3,0);
 			if (m_WaitDlg.DoModal()==IDOK)
 			{
 					m_return =false;
 					closesocket(m_ConnectSock);
 					TerminateThread(h1,0);
 					AfxMessageBox(_T("初始化失败，请重新打开！"));
 			}
 			else 
 				m_InitTrue=true;
 		} 
/*测试代码*/
     // 	GetPrivateProfileString("Server","serverip",NULL,m_ip,20,"D:\\server.ini");
     // 	m_port=GetPrivateProfileInt("Server","serverport",0,"D:\\server.ini");
     // 	h1=::CreateThread(NULL, 0, ConnectThreadFunc, this, 0, NULL);
   		//if (m_WaitDlg.DoModal()==IDCANCEL)
   		//	m_return=FALSE;
	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)
	InitContextMenuManager();
	InitKeyboardManager();
	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);
	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMFC_SDI_ClientDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CTabListView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
	// 分析标准外壳命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
	return FALSE;
	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();
	//skinppLoadSkin(_T("vladstudio.ssk"));
	// 仅当具有后缀时才调用 DragAcceptFiles
	//  在 SDI 应用程序中，这应在 ProcessShellCommand 之后发生
	return TRUE;
}
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	/*afx_msg void OnUpdateCagain(CCmdUI *pCmdUI);*/
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	/*ON_UPDATE_COMMAND_UI(ID_CAgain, &CAboutDlg::OnUpdateCagain)*/
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CMFC_SDI_ClientApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CMFC_SDI_ClientApp 自定义加载/保存方法

void CMFC_SDI_ClientApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CMFC_SDI_ClientApp::LoadCustomState()
{
}

void CMFC_SDI_ClientApp::SaveCustomState()
{
}

// CMFC_SDI_ClientApp 消息处理程序

void CMFC_SDI_ClientApp::OnSetuser()
{

	CSetNewUser dlg;
	dlg.DoModal();
}

void CMFC_SDI_ClientApp::OnSetg()
{
	CSetG dlg;
	dlg.DoModal();
}

void CMFC_SDI_ClientApp::OnModify()
{
	// TODO: Add your command handler code here
	CModifyAllDlg dlg;
	dlg.DoModal();
}

void CMFC_SDI_ClientApp::OnCagain()
{
	// TODO: Add your command handler code here
	h1=::CreateThread(NULL, 0, ConnectThreadFunc, this, 0, NULL);
	Sleep(500);
	if (m_return)
	{
		AfxMessageBox(_T("重连成功！"));
		m_connected=false;
	}
	else
	{
		AfxMessageBox(_T("重连失败！"));
		m_connected=true;
	}
}

void CMFC_SDI_ClientApp::On32783()
{
	// TODO: Add your command handler code here
	CTestDlg dlg;
	dlg.DoModal();
}

int CMFC_SDI_ClientApp::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class
	//skinppExitSkin();
	//closesocket(m_ConnectSock);
	
	if (nRCount!=0)
	{
		free(m_RoadListInfo[nRCount]);
		nRCount--;
	}
 	else
		return CWinAppEx::ExitInstance();
}

void CMFC_SDI_ClientApp::OnUpdateCagain(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (m_connected)
	{
		pCmdUI->Enable(TRUE);
	}
	else
		pCmdUI->Enable(FALSE);
}

void CMFC_SDI_ClientApp::OnRenew()
{
	// TODO: Add your command handler code here
	char a[3]={'L','G','#'};
	send(m_ConnectSock,a,3,0);
	m_WaitDlg.DoModal();
}

 
