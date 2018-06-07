
// s5Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "s5.h"
#include "s5Dlg.h"
#include "afxdialogex.h"
#include "mclmcr.h"
#include "matrix.h"
#include "mclcppclass.h"
#include "add.h"
#include "mex.h"
#include "matrix.h"

using namespace std;
#pragma comment(lib,"add.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// Cs5Dlg 对话框




Cs5Dlg::Cs5Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cs5Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cs5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, edita);
	DDX_Control(pDX, IDC_EDIT2, editb);
}

BEGIN_MESSAGE_MAP(Cs5Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Cs5Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Cs5Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// Cs5Dlg 消息处理程序

BOOL Cs5Dlg::OnInitDialog()
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
	if(!addInitialize())
	{
		cout<<"could not initialize libmysvd!"<<endl;
		exit(0);
	}
	SetDlgItemText(IDC_EDIT13,_T("0"));
	SetDlgItemText(IDC_EDIT14,_T("0"));
	SetDlgItemText(IDC_EDIT15,_T("0"));
	SetDlgItemText(IDC_EDIT16,_T("1"));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cs5Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cs5Dlg::OnPaint()
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
HCURSOR Cs5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

    CString str1,str2,str3,ss1,ss2,st,sf,s[16];
	CString sa,sb,sc,sd;
	mwArray A(4,4,mxDOUBLE_CLASS);
	mwArray B(4,4,mxDOUBLE_CLASS);
	mwArray C(1,2,mxDOUBLE_CLASS);
	mwArray D(1,2,mxDOUBLE_CLASS);
	double a[16],b[4][4],c[1],d[1];

void Cs5Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	for(int i=0;i<16;i++)
	{
	   ((CEdit*)GetDlgItem(IDC_EDIT1+i))->GetWindowTextW(s[i]);
	    a[i]=_wtof(s[i]);                  //变成数字
	}
	A.SetData(a,16);
	B=A;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
		   b[i][j]=B.Get(2,j+1,i+1);
		   b[i][j]=b[i][j]+1;
		   str2.Format(_T("%.5f"),b[i][j]);
	       str1+=str2+' ';
		}
	   str1+="\r\n";
	}
	SetDlgItemText(IDC_EDIT17,str1);
}

void Cs5Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//GetDlgItem(IDC_EDIT1)->GetWindowTextW(sa);
	//    a[0]=_wtof(sa);                  //变成数字
	//A(1,1)=a[0];
	//GetDlgItem(IDC_EDIT2)->GetWindowTextW(sb);
	//    b[0]=_wtof(sb);                  //变成数字
	//B.SetData(b,2);                      //2或1都行
 //   add(2,C,D,A,B);
	//c[0]=C.Get(1,1);
	//sc.Format(_T("%.5f"),c[0]);
	// d[0]=D.Get(1,1);
	// sd.Format(_T("%.5f"),d[0]);
	// ss2=sc+' '+sd;
	//SetDlgItemText(IDC_EDIT3,ss2);
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
		   b[i][j]=B.Get(2,j+1,i+1);
		   b[i][j]=b[i][j]*2;
		   str2.Format(_T("%.5f"),b[i][j]);
	       str3+=str2+' ';
		}
	   str3+="\r\n";
	}
	SetDlgItemText(IDC_EDIT17,str3);
}
