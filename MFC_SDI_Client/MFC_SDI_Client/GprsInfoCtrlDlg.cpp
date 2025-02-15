// GprsInfoCtrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFC_SDI_Client.h"
#include "GprsInfoCtrlDlg.h"


// CGprsInfoCtrlDlg dialog

IMPLEMENT_DYNAMIC(CGprsInfoCtrlDlg, CDialog)

CGprsInfoCtrlDlg::CGprsInfoCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGprsInfoCtrlDlg::IDD, pParent)
{

}

CGprsInfoCtrlDlg::~CGprsInfoCtrlDlg()
{
}

void CGprsInfoCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GINFO_TAB, m_Tab);
}
// CGprsInfoCtrlDlg message handlers
BEGIN_MESSAGE_MAP(CGprsInfoCtrlDlg, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_GINFO_TAB, &CGprsInfoCtrlDlg::OnTcnSelchangeGinfoTab)
END_MESSAGE_MAP()
BOOL CGprsInfoCtrlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	theApp.m_pGCInfoDlg=this;
	TCITEM tcItem;
	tcItem.mask = TCIF_TEXT;
	tcItem.pszText = _T("基本信息");
	m_Tab.InsertItem(0,&tcItem);
	tcItem.pszText = _T("开关信息");
	m_Tab.InsertItem(1,&tcItem);
	tcItem.pszText = _T("线缆信息");
	m_Tab.InsertItem(2,&tcItem);

	m_pGLocalVIew = new CGPRSLocaInfomation();
	m_pGLocalVIew->Create(IDD_GPRSLocal,&m_Tab);
	CRect m_rect;
	m_Tab.GetClientRect(m_rect);
	m_rect.DeflateRect(0,20,0,0);
	m_pGLocalVIew->MoveWindow(m_rect);
	m_pGLocalVIew->ShowWindow(SW_SHOW);

 	m_RoadView = new CRoudInfoView();
 	m_RoadView->Create(IDD_Roud_Info,&m_Tab);
 	m_RoadView->MoveWindow(m_rect);
 	m_RoadView->ShowWindow(SW_HIDE);
	// TODO:  Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CGprsInfoCtrlDlg::OnTcnSelchangeGinfoTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	int sel = m_Tab.GetCurFocus();
	switch(sel)
	{
	case 0:
		m_pGLocalVIew->ShowWindow(SW_SHOW);
		m_RoadView->ShowWindow(SW_HIDE);
		break;
	case 1 :
		{
			pGetTerminanlInfo=theApp.m_pLocalInfoDlg->GetSelTerminalInfo();
			if (pGetTerminanlInfo==NULL)
			{
				AfxMessageBox(_T("请选择终端！"));
				return;
			}
			else
			{
				memcpy(theApp.TID+1,pGetTerminanlInfo->TID,4);
				theApp.TID[0]='R';
				theApp.TID[5]='#';
				send(theApp.m_ConnectSock,theApp.TID,6,0);
				m_pGLocalVIew->ShowWindow(SW_HIDE);
				m_RoadView->ShowWindow(SW_SHOW);
				break;
			}
		}
	case 2:
		break;
	case 3:
		break;
	}
	*pResult = 0;
}

void CGprsInfoCtrlDlg::SendRCurrent()
{
	ConTrlInfo* pGetInfo1=(ConTrlInfo*)malloc(sizeof(ConTrlInfo));
	ZeroMemory(pGetInfo1,sizeof(ConTrlInfo));
	pGetInfo1->m_First[0]=0x2F;
	pGetInfo1->m_First[1]=0x43;
	pGetInfo1->m_First[2]=0x2F;
	pGetInfo1->m_First[3]=0x06;
	memcpy(pGetInfo1->m_ID,pGetTerminanlInfo->TID,4);
	pGetInfo1->m_OrderType[0]=0x1A;
	pGetInfo1->m_OrderObject[0]=0x33;
	pGetInfo1->m_ActiveType[0]=0xBD;
	pGetInfo1->m_CheckData[0]=0xA0;
	pGetInfo1->m_EndBuffer[1]=0xCC;
	Sleep(200);
	SendContrlInfo(&hdr,pGetInfo1);
	free(pGetInfo1);
}
void CGprsInfoCtrlDlg::SendRUpdata()
{
	ConTrlInfo* pGetInfo1=(ConTrlInfo*)malloc(sizeof(ConTrlInfo));
	ZeroMemory(pGetInfo1,sizeof(ConTrlInfo));
	pGetInfo1->m_First[0]=0x2F;
	pGetInfo1->m_First[1]=0x43;
	pGetInfo1->m_First[2]=0x2F;
	pGetInfo1->m_First[3]=0x06;
	memcpy(pGetInfo1->m_ID,pGetTerminanlInfo->TID,4);
	pGetInfo1->m_OrderType[0]=0x1A;
	pGetInfo1->m_OrderObject[0]=0x32;
	pGetInfo1->m_ActiveType[0]=0xBD;
	pGetInfo1->m_CheckData[0]=0xA0;
	pGetInfo1->m_EndBuffer[1]=0xCC;
	Sleep(200);
	SendContrlInfo(&hdr,pGetInfo1);
	free(pGetInfo1);
}

