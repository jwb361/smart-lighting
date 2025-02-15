#include "StdAfx.h"
#include "ClientSocket.h"

#include "head.h"

CClientSocket::CClientSocket(CInterface *pInterFace,CMyWaveIn *pIn,CUdpSocket *pUdp):
m_bConnect(FALSE),
m_pInterface (NULL),
m_pIn(NULL),
m_pUdp (NULL)
{
	m_pBuffer = new char[1024];
	m_pInterface = pInterFace;
	m_pIn = pIn;
	m_pUdp = pUdp;
}

CClientSocket::~CClientSocket()
{
	delete [1024]m_pBuffer;
}


void CClientSocket::OnClose(int nErrorCode)
{
	m_bConnect = FALSE;
	m_pInterface->BeClose ();

	CSocket::OnClose(nErrorCode);
}

void CClientSocket::OnReceive(int nErrorCode) 
{
	struct TalkFrame *frame;
	frame = (struct TalkFrame *)m_pBuffer;

	int iLen = sizeof(struct TalkFrame);
	while(iLen > 0)
	{
		int i = Receive (m_pBuffer + sizeof(struct TalkFrame) - iLen,iLen);
		if (i == SOCKET_ERROR )
			return ;
		iLen -= i;
	}
	if (strcmp(frame->cFlag ,"TalkFrame") != 0)
	{
		return;
	}

	iLen = frame->iLen;
	frame->iLen;
	while (iLen > 0)
	{
		int i = Receive (
			m_pBuffer + sizeof(struct TalkFrame) + (frame->iLen - iLen),
			iLen);
		if (i == SOCKET_ERROR )
			return ;
		iLen -= i;
	}

	CString add;
	UINT port;
	switch (frame->iCom )
	{
	case TC_NORMAL_TALK:
		memset(frame,0,sizeof (struct TalkFrame));
		sprintf(frame->cFlag,"TalkFrame");
		GetPeerName (add,port);
		if (m_pInterface ->IsConnect (add))
		{
			frame->iCom = TC_AGREE_TALK;
			frame->iLen = 0;
			if (SOCKET_ERROR  == Send (m_pBuffer,sizeof(struct TalkFrame)))
			{
				TRACE("Send agree command fail.\n");
				break ;
			};

			m_pInterface->TalkStart (add);
			m_pUdp->SetIp (add);
			m_pIn->EnableSend (TRUE);
			m_pInterface->m_bWork = TRUE;
			break;
		};
		frame->iCom = TC_DISAGREE_TALK;
		frame->iLen = 0;
		Send (m_pBuffer,sizeof(struct TalkFrame));
		Close ();
		break;
	default:
		break;
	}

	CSocket::OnReceive(nErrorCode);
}
