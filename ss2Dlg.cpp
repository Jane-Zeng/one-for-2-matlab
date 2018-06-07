
// ss2Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ss2.h"
#include "ss2Dlg.h"
#include "afxdialogex.h"
#include <HalconCpp.h>
#include <iostream>
#include "HDevThread.h"
using namespace std;
using namespace HalconCpp;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// Css2Dlg �Ի���




Css2Dlg::Css2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Css2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Css2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Css2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Css2Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Css2Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Css2Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// Css2Dlg ��Ϣ�������

BOOL Css2Dlg::OnInitDialog()
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

void Css2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Css2Dlg::OnPaint()
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
HCURSOR Css2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HObject ho_Image1,ho_Image2; 
 HTuple hv_AcqHandle1,hv_AcqHandle2;
 HTuple hv_Width1,hv_Height1,hv_Width2,hv_Height2; 
 HTuple hv_WindowHandle1,hv_WindowHandle2;
 HTuple  i, hv_si, hv_filename;

 bool thread=true;
 CWinThread *pThread;
 CWinThread *sThread;
 CWinThread *nThread;
 bool tstop=false;

void Css2Dlg::OnBnClickedButton1()
{
	 pThread = AfxBeginThread(Threadstart,this);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

UINT Css2Dlg::Threadstart(LPVOID pParam)
{
	Css2Dlg* pointer1;
	pointer1 = (Css2Dlg*)pParam;
	CRect rtWindow1; 
 HWND hImgWnd1 =pointer1->GetDlgItem(IDC_STATIC)->m_hWnd; 
 pointer1->GetDlgItem(IDC_STATIC)->GetClientRect(&rtWindow1);
 OpenWindow(rtWindow1.left, rtWindow1.top, rtWindow1.Width(), rtWindow1.Height(), (Hlong)hImgWnd1, "visible", "", &hv_WindowHandle1); 
 try
 {
 OpenFramegrabber("GigEVision", 0, 0, 0, 0, 0, 0, "default", -1, "default", -1, 
      "false", "default", "0223823012", 0, -1, &hv_AcqHandle1);
	while (thread)
  {
	  for(HTuple i=0;i<3;i++)
	{
		GrabImageStart(hv_AcqHandle1,-1);
    GrabImageAsync(&ho_Image1, hv_AcqHandle1, -1);
    GetImageSize(ho_Image1, &hv_Width1, &hv_Height1);//������for���棬����ͼ��3sˢһ��
	TupleString(i, i.TupleString("d"), &hv_si);
    hv_filename = ("C:/Users/Administrator/Desktop/capture/maybeuseful/"+hv_si)+".png";
    WriteImage(ho_Image1,"png",0,hv_filename);
	
 /* HDevWindowStack::Push(hv_WindowHandle);
  if (HDevWindowStack::IsOpen())
    DispObj(ho_Image, HDevWindowStack::GetActive());*///��ʾ��ͼ
  SetPart(hv_WindowHandle1, 0, 0,hv_Height1, hv_Width1 );
  HDevWindowStack::Push(hv_WindowHandle1);
 DispObj(ho_Image1, hv_WindowHandle1); 
  
    Sleep(1000);//��ע�ͺ����ɿ���
	//ho_Image1.GenEmptyObj();
	}
    Sleep(1);
  }
 }
	catch(HException &except)
{
	AfxMessageBox(CString(except.ErrorMessage())); 
 }
	return 0;
}


void Css2Dlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	thread = false;
	WaitForSingleObject( pThread, INFINITE );
	WaitForSingleObject( nThread, INFINITE );
	CloseHandle(Threadstart);
	CloseHandle(Threadsnap);
	//CloseFramegrabber(hv_AcqHandle1);//����for�е�hv_AcqHandle1����ע�͵�
}
//UINT Css2Dlg::ExitThreadFunc(LPVOID lParam)
//{
//	while(1)
//	{
//		if(tstop==1)
//			break;
//		Sleep(10);
//	}
//	//exit(0);//�˳�����
//	CloseFramegrabber(hv_AcqHandle1);
//	return 0;
//}

void Css2Dlg::OnBnClickedButton3()
{
	nThread =AfxBeginThread(Threadsnap,this);
}
UINT Css2Dlg::Threadsnap(LPVOID nParam)
{
	Css2Dlg* pointer2;
	pointer2 = (Css2Dlg*)nParam;
	CRect rtWindow2; 
 HWND hImgWnd2 =pointer2->GetDlgItem(IDC_STATIC2)->m_hWnd; 
 pointer2->GetDlgItem(IDC_STATIC2)->GetClientRect(&rtWindow2);
 OpenWindow(rtWindow2.left, rtWindow2.top, rtWindow2.Width(), rtWindow2.Height(), (Hlong)hImgWnd2, "visible", "", &hv_WindowHandle2); 
	try{
	while (thread)
  {
	  for(HTuple i=0;i<3;i++)
	  {
	  TupleString(i, i.TupleString("d"), &hv_si);
      hv_filename = ("C:/Users/Administrator/Desktop/capture/maybeuseful/"+hv_si)+".png";
  
		 ReadImage(&ho_Image2,hv_filename);
         GetImageSize(ho_Image2, &hv_Width2, &hv_Height2);
         SetPart(hv_WindowHandle2, 0, 0,hv_Height2, hv_Width2 );
         HDevWindowStack::Push(hv_WindowHandle2);
         DispObj(ho_Image2, hv_WindowHandle2); 
		 Sleep(2000);
         //��ע�ͺ����ɿ���
	     ho_Image2.GenEmptyObj();
	     ClearWindow(hv_WindowHandle2);
	  }
      Sleep(1);
	  }
  }
	
	catch(HException &except)
{
	AfxMessageBox(CString(except.ErrorMessage())); 
 }
return 0;
}