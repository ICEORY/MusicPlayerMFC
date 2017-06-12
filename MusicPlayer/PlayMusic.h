#pragma once

// CPlayMusic
#include <MMSystem.h>
#include <Digitalv.h>

class CPlayMusic : public CWnd
{
	DECLARE_DYNAMIC(CPlayMusic)

public:
	CPlayMusic();
	virtual ~CPlayMusic();


	void Play(CString str);
	void Pause();
	void Stop();
	void SetVolume(int vol);
	void Open(HWND hwnd,CString str);
	int GetMode();
	DWORD GetNow();
	DWORD GetLength();
private:
	MCI_PLAY_PARMS m_Play;
	MCI_OPEN_PARMS m_Open;
	MCIDEVICEID m_dID;
	HWND m_Parent;
	MCI_STATUS_PARMS m_Status;
	MCI_STATUS_PARMS m_Seek;
	MCI_STATUS_PARMS m_Mode;

protected:
	DECLARE_MESSAGE_MAP()
};


