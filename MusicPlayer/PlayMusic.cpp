// PlayMusic.cpp : implementation file
//

#include "stdafx.h"


#include "MusicPlayer.h"
#include "PlayMusic.h"


// CPlayMusic

IMPLEMENT_DYNAMIC(CPlayMusic, CWnd)

CPlayMusic::CPlayMusic()
{

}

CPlayMusic::~CPlayMusic()
{
}


BEGIN_MESSAGE_MAP(CPlayMusic, CWnd)
END_MESSAGE_MAP()



// CPlayMusic message handlers

void CPlayMusic::Open(HWND hwnd,CString str)
{
	m_dID=NULL;
	m_Parent=hwnd;
	m_Open.lpstrElementName=str;
	mciSendCommand(NULL,MCI_OPEN,MCI_OPEN_ELEMENT,(DWORD)(LPVOID)&m_Open);
	m_dID=m_Open.wDeviceID;
}
void CPlayMusic::Play(CString str)
{
	m_Play.dwCallback=(DWORD)m_Parent;
	mciSendCommand(m_dID,MCI_PLAY,MCI_NOTIFY,(DWORD)(LPVOID)&m_Play);

}


void CPlayMusic::Pause()
{
	mciSendCommand(m_dID,MCI_PAUSE,NULL,NULL);
}


void CPlayMusic::Stop()
{
	mciSendCommand(m_dID,MCI_CLOSE,NULL,NULL);
	m_Status.dwReturn=0;
}


DWORD CPlayMusic::GetLength()
{
	m_Status.dwItem=MCI_STATUS_LENGTH;
	mciSendCommand(m_dID,MCI_STATUS,MCI_STATUS_ITEM,(DWORD)(LPVOID)&m_Status);
	return m_Status.dwReturn;
}


DWORD  CPlayMusic::GetNow()
{
	m_Status.dwItem=MCI_STATUS_POSITION;
	mciSendCommand(m_dID,MCI_STATUS,MCI_STATUS_ITEM,(DWORD)(LPVOID)&m_Status);
	return m_Status.dwReturn;
}


int CPlayMusic::GetMode()
{
	m_Status.dwItem=MCI_STATUS_MODE;
	mciSendCommand(m_dID,MCI_STATUS,MCI_STATUS_ITEM,(DWORD)(LPVOID)&m_Status);
	return m_Status.dwReturn;
}

void CPlayMusic::SetVolume(int vol)
{
	MCI_DGV_SETAUDIO_PARMS mcivol;
	mcivol.dwCallback=(DWORD)m_Parent;
	mcivol.dwItem=MCI_DGV_SETAUDIO_VOLUME;
	mcivol.dwValue=vol;
	mciSendCommand(m_dID,MCI_SETAUDIO,MCI_DGV_SETAUDIO_VALUE|MCI_DGV_SETAUDIO_ITEM,(DWORD)(LPVOID)&mcivol);
}

