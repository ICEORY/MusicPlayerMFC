
// MusicPlayerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MusicPlayer.h"
#include "MusicPlayerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ID_TIMER 0X01

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
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
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMusicPlayerDlg 对话框




CMusicPlayerDlg::CMusicPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMusicPlayerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMusicPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_PREVIOUS, m_Btn_Previous);
	DDX_Control(pDX, IDC_BTN_PLAY, m_Btn_Play);
	DDX_Control(pDX, IDC_BTN_NEXT, m_Btn_Next);
	DDX_Control(pDX, IDC_BTN_STOP, m_Btn_Stop);
	DDX_Control(pDX, IDC_VOLUME, m_Volume);
	DDX_Control(pDX, IDC_LIST_MUSIC, m_List_Music);
	DDX_Control(pDX, IDC_BTN_ADD, m_Btn_AddFile);
}

BEGIN_MESSAGE_MAP(CMusicPlayerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_ADD, &CMusicPlayerDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_PLAY, &CMusicPlayerDlg::OnBnClickedBtnPlay)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_STOP, &CMusicPlayerDlg::OnBnClickedBtnStop)
	ON_WM_CLOSE()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(IDC_BTN_SAVE, &CMusicPlayerDlg::OnBtnSave)
	ON_COMMAND(IDC_BTN_ADDFILE, &CMusicPlayerDlg::OnBtnAddfile)
END_MESSAGE_MAP()


// CMusicPlayerDlg 消息处理程序

BOOL CMusicPlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	ButtonInit();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMusicPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMusicPlayerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
void CMusicPlayerDlg::ButtonInit()
{
	//Init all the button bmp image
	HBITMAP hBmp_Previous=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_PREVIOUS));
	m_Btn_Previous.SetBitmap(hBmp_Previous);

	HBITMAP hBmp_Play=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_PLAY));
	m_Btn_Play.SetBitmap(hBmp_Play);

	HBITMAP hBmp_Next=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_NEXT));
	m_Btn_Next.SetBitmap(hBmp_Next);

	HBITMAP hBmp_Stop=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_STOP));
	m_Btn_Stop.SetBitmap(hBmp_Stop);

	HBITMAP hBmp_Add=::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_ADDFILE));
	m_Btn_AddFile.SetBitmap(hBmp_Add);

	//Init the Music List
	m_List_Music.SetExtendedStyle( m_List_Music.GetExtendedStyle() |
                                            LVS_EX_GRIDLINES | 
                                            LVS_EX_FULLROWSELECT); 
	m_List_Music.InsertColumn(0,L"序列",NULL,40);
	m_List_Music.InsertColumn(1,L"曲名",NULL,120);
	m_List_Music.InsertColumn(2,L"时长",NULL,50);
	m_List_Music.InsertColumn(3,L"路径",NULL,200);

	m_SongCount=0;
	m_Volume.SetRangeMax(1000);
	m_Volume.SetPos(300);
	m_Playing=false;

	//AddFile();
	SetDlgItemTextW(IDC_TIMESHOW,L"播放时间: 00:00/00:00");
}

void CMusicPlayerDlg::AddFile()
{
	CFileDialog fdlg(true);
	fdlg.m_ofn.lpstrFilter=L"音乐库文件(*.txt)\0*.txt\0"
						   L"所有文件(*.*)\0*.*\0\0";
	CString FileName;
	if(IDOK==fdlg.DoModal())
	{
		FileName=fdlg.GetPathName();
	}
	if(FileName=="")return;

	CString string;
	CFile file(FileName,CFile::modeRead);
	int len=(int)file.GetLength();
	p_SongList=new char[len+1];
	p_SongList[len]='\0';
	file.Read(p_SongList,len);
	string=p_SongList;
	
	int row=0,column=0;
	for (int i=0;i<len;i++)
	{
		if(string[i]=='!')
		{
			string.Format(L"%03d",row+1);
			m_List_Music.InsertItem(row,string);
			m_SongCount++;
			column=1;
			continue;
		}
		if(string[i]=='@')
		{
			column=3;
			continue;
		}
		if(string[i]=='\n')
		{
			row++;
			continue;
		}
		//string=p_SongList[i];
		m_List_Music.SetItemText(row,column,(LPTSTR)string[i]);
	}

	delete p_SongList;
}


void CMusicPlayerDlg::OnBnClickedBtnAdd()
{
	// TODO: Add your control notification handler code here
	CFileDialog fdlg(TRUE);
	fdlg.m_ofn.lpstrFilter=L"音乐文件(*.mp3;*.wma;*.wav)\0*.mp3;*.wma;*.wav\0"
						   L"所有文件(*.*)\0*.*\0\0";
	if(IDOK==fdlg.DoModal())
	{
		CString path=fdlg.GetPathName();
		CString file=fdlg.GetFileName();
		if(path=="")return;
		int r=m_SongCount;
		m_SongCount++;
		CString s;
		s.Format(L"%03d",m_SongCount);
		m_List_Music.InsertItem(r,s);
		m_List_Music.SetItemText(r,1,file);
		m_List_Music.SetItemText(r,3,path);
	}
}


void CMusicPlayerDlg::OnBnClickedBtnPlay()
{
	// TODO: Add your control notification handler code here
	if(m_Playing==false)
	{
		HBITMAP hBmp_Play=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_PAUSE));
		m_Btn_Play.SetBitmap(hBmp_Play);
		m_Playing=true;


		POSITION pos=m_List_Music.GetFirstSelectedItemPosition();
		int index=0;
		if(pos)
		{
			index=m_List_Music.GetNextSelectedItem(pos);
		}
		if (index==-1)
		{
			MessageBox(L"No Song be choose",L"Warning",MB_OK);
		}
		m_OnPlay.FileName=m_List_Music.GetItemText(index,3);
		m_Player.Open(m_hWnd,m_OnPlay.FileName);
		m_Player.Play(m_OnPlay.FileName);

		DWORD SongLength=m_Player.GetLength()/1000;	
		m_OnPlay.Len_Min=SongLength/60;
		m_OnPlay.Len_Sec=SongLength%60;
		DWORD now=m_Player.GetNow()/1000;
		m_OnPlay.Pos_Min=now/60;
		m_OnPlay.Pos_Sec=now%60;

		CString str;
		str.Format(L"播放时间: %02d:%02d/%02d:%02d",m_OnPlay.Pos_Min,m_OnPlay.Pos_Sec,m_OnPlay.Len_Min,m_OnPlay.Len_Min);
		SetDlgItemTextW(IDC_TIMESHOW,str);
		SetTimer(ID_TIMER,1000,NULL);
	}
	else
	{
		HBITMAP hBmp_Play=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_PLAY));
		m_Btn_Play.SetBitmap(hBmp_Play);
		m_Playing=false;

		m_Player.Pause();
		KillTimer(ID_TIMER);
	}
}


void CMusicPlayerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
	case ID_TIMER:
		{
			DWORD now=m_Player.GetNow()/1000;
			m_OnPlay.Pos_Min=now/60;
			m_OnPlay.Pos_Sec=now%60;
			CString str;
			str.Format(L"播放时间: %02d:%02d/%02d:%02d",m_OnPlay.Pos_Min,m_OnPlay.Pos_Sec,m_OnPlay.Len_Min,m_OnPlay.Len_Min);
			SetDlgItemTextW(IDC_TIMESHOW,str);
			break;
		}
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CMusicPlayerDlg::OnBnClickedBtnStop()
{
	// TODO: Add your control notification handler code here
	if(m_Playing==false)
	{

	}
	else
	{
		HBITMAP hBmp_Play=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_PLAY));
		m_Btn_Play.SetBitmap(hBmp_Play);
		m_Playing=false;
		KillTimer(ID_TIMER);
	}
	m_Player.Stop();
}

void CMusicPlayerDlg::SaveFile()
{

}
void CMusicPlayerDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	
	CDialogEx::OnClose();
}


void CMusicPlayerDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CMenu menu;
	if(!menu.LoadMenu(IDR_MENU1))
	{
		MessageBox(L"ERROR",L"INFORMATION",MB_OK);
		return;
	}
	CPoint p;
	GetCursorPos(&p);
	CMenu *pMenu=menu.GetSubMenu(0);
	pMenu->TrackPopupMenu(TPM_LEFTALIGN,p.x,p.y,this);
	CDialogEx::OnRButtonDown(nFlags, point);
}


void CMusicPlayerDlg::OnBtnSave()
{
	// TODO: Add your command handler code here
	CFileDialog fdlg(FALSE);
	fdlg.m_ofn.lpstrFilter=L"音乐列表(*.txt)\0*.txt\0"
						   L"所有文件(*.*)\0*.*\0\0";
	fdlg.m_ofn.lpstrDefExt=L"txt";
	CString FileName;
	if(IDOK==fdlg.DoModal())
	{
		FileName=fdlg.GetPathName();
	}
	if(FileName=="")return;
	CFile file(FileName,CFile::modeWrite|CFile::modeCreate);
	CString str;
	for (int i=0;i<m_SongCount;i++)
	{
		file.Write(L"!",1);
		str=m_List_Music.GetItemText(i,1);
		USES_CONVERSION;
		char *temp=T2A(str);
		file.Write(temp,strlen(temp));
		file.Write(L"@",1);
		str=m_List_Music.GetItemText(i,3);
		temp=T2A(str);
		file.Write(temp,strlen(temp));
		file.Write(L"\0",1);
		file.Write(L"\n",1);
	}
	file.Close();
}


void CMusicPlayerDlg::OnBtnAddfile()
{
	// TODO: Add your command handler code here
	AddFile();
}
