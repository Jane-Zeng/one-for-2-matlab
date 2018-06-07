
// s1Dlg.cpp : ʵ���ļ�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// Cs1Dlg �Ի���




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


// Cs1Dlg ��Ϣ�������

BOOL Cs1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cs1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
    DispObj(ho_Image, HDevWindowStack::GetActive());*///��ʾ��ͼ
  SetPart(hv_WindowHandle1, 0, 0,hv_Height1, hv_Width1 );
  HDevWindowStack::Push(hv_WindowHandle1);
 DispObj(ho_Image1, hv_WindowHandle1); 
  
    Sleep(2000);//��ע�ͺ����ɿ���
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	thread = false;
	//WaitForSingleObject( pThread->m_hThread, INFINITE );
	//CloseHandle(ThreadFunc);
	//CloseFramegrabber(hv_AcqHandle);//���������while��Sleep���Եõ�����һ�м��ڶ����߳�ͬһЧ��
	stopThread =AfxBeginThread(ExitThreadFunc,this);
	//pThread->SuspendThread();//��ͣʵʱ��ͼ�̣߳���������ֹ���߳�
}
UINT Cs1Dlg::ExitThreadFunc(LPVOID lParam)
{
	while(1)
	{
		if(tstop==1)
			break;
		Sleep(10);
	}
	//exit(0);//�˳�����
	CloseFramegrabber(hv_AcqHandle1);
	return 0;
}
