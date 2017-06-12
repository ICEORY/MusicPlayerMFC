
// MusicPlayerDlg.h : 头文件
//

#pragma once
#include "PlayMusic.h"
#include "afxwin.h"
#include "afxcmn.h"

// CMusicPlayerDlg 对话框
struct SongInfo
{
	int Len_Min;
	int Len_Sec;
	int Pos_Min;
	int Pos_Sec;
	CString FileName;
};
class CMusicPlayerDlg : public CDialogEx
{
// 构造
public:
	CMusicPlayerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MUSICPLAYER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();

private:
	void ButtonInit();
	void SaveFile();
	void AddFile();
private:
	CBitmapButton m_Btn_Previous;
	CBitmapButton m_Btn_Play;
	CBitmapButton m_Btn_Next;
	CBitmapButton m_Btn_Stop;
	CSliderCtrl m_Volume;
	CListCtrl m_List_Music;
	CPlayMusic m_Player;

	SongInfo m_OnPlay;
	int m_SongCount;
	CButton m_Btn_AddFile;
	int m_Minute,m_Second;
	bool m_Playing;
	char *p_SongList;
public:
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnPlay();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnClose();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBtnSave();
	afx_msg void OnBtnAddfile();
};
