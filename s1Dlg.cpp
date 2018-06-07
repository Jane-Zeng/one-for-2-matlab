
// s1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "s1.h"
#include "s1Dlg.h"
#include "afxdialogex.h"
#include <HalconCpp.h>
#include "stdio.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;
CSemaphore sPH(2,2);

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


// Cs1Dlg 对话框




Cs1Dlg::Cs1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cs1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cs1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editDisp);
}

BEGIN_MESSAGE_MAP(Cs1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Cs1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Cs1Dlg::OnBnClickedButton2)
	
END_MESSAGE_MAP()


// Cs1Dlg 消息处理程序

BOOL Cs1Dlg::OnInitDialog()
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
	
	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cs1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cs1Dlg::OnPaint()
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

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cs1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
 HObject ho_Image1,ho_Image2; 
 HTuple hv_AcqHandle1,hv_AcqHandle2;
 HTuple hv_Width1,hv_Height1,hv_Width2,hv_Height2; 
 HTuple hv_WindowHandle1,hv_WindowHandle2;


 bool thread=true;
 CWinThread *pThread;
 CWinThread *stopThread;
 CWinThread *nThread;
 bool tstop=false;

void Cs1Dlg::OnBnClickedButton1()
{
	 pThread = AfxBeginThread(Threadstart,this);
	// TODO: 在此添加控件通知处理程序代码
}

UINT Cs1Dlg::Threadstart(LPVOID pParam)
{
	CFileDialog dlg(FALSE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("test(*.jpg;*.bmp;*.png)|*.jpg;*.bmp;*.png|All files|*||"));
	CString pathname=dlg.GetFileName();
	pathname.GetBuffer(pathname.GetLength());
	pathname.ReleaseBuffer();
	
	Cs1Dlg* pointer1;
	pointer1 = (Cs1Dlg*)pParam;
	CRect rtWindow1; 
 HWND hImgWnd1 =pointer1->GetDlgItem(IDC_STATIC1)->m_hWnd; 
 pointer1->GetDlgItem(IDC_STATIC1)->GetClientRect(&rtWindow1);
 OpenWindow(rtWindow1.left, rtWindow1.top, rtWindow1.Width(), rtWindow1.Height(), (Hlong)hImgWnd1, "visible", "", &hv_WindowHandle1); 
 try
 {
 OpenFramegrabber("GigEVision", 0, 0, 0, 0, 0, 0, "default", -1, "default", -1, 
      "false", "default", "0223823012", 0, -1, &hv_AcqHandle1);
	while (thread)
  {
    GrabImageStart(hv_AcqHandle1,-1);
  GrabImageAsync(&ho_Image1, hv_AcqHandle1, -1);
  //WriteImage(ho_Image1,"png",0,"test");
  GetImageSize(ho_Image1, &hv_Width1, &hv_Height1);
 /* HDevWindowStack::Push(hv_WindowHandle);
  if (HDevWindowStack::IsOpen())
    DispObj(ho_Image, HDevWindowStack::GetActive());*///显示单图
  SetPart(hv_WindowHandle1, 0, 0,hv_Height1, hv_Width1 );
  HDevWindowStack::Push(hv_WindowHandle1);
 DispObj(ho_Image1, hv_WindowHandle1); 
  
    Sleep(2000);//非注释后会造成卡顿
	ho_Image1.GenEmptyObj();
	}
	tstop=1;
 }
	catch(HException &except)
{
	AfxMessageBox(CString(except.ErrorMessage())); 
 }
	return 0;
}


void Cs1Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	
	thread = false;
	//WaitForSingleObject( pThread->m_hThread, INFINITE );
	//CloseHandle(ThreadFunc);
	//CloseFramegrabber(hv_AcqHandle);//此三行配合while中Sleep可以得到与下一行及第二个线程同一效果
	stopThread =AfxBeginThread(ExitThreadFunc,this);
	//pThread->SuspendThread();//暂停实时采图线程，但不会终止该线程
}
UINT Cs1Dlg::ExitThreadFunc(LPVOID lParam)
{
	while(1)
	{
		if(tstop==1)
			break;
		Sleep(10);
	}
	//exit(0);//退出工程
	CloseFramegrabber(hv_AcqHandle1);
	return 0;
}
