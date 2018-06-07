
// s5Dlg.cpp : ʵ���ļ�
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


// Cs5Dlg �Ի���




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


// Cs5Dlg ��Ϣ�������

BOOL Cs5Dlg::OnInitDialog()
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
	if(!addInitialize())
	{
		cout<<"could not initialize libmysvd!"<<endl;
		exit(0);
	}
	SetDlgItemText(IDC_EDIT13,_T("0"));
	SetDlgItemText(IDC_EDIT14,_T("0"));
	SetDlgItemText(IDC_EDIT15,_T("0"));
	SetDlgItemText(IDC_EDIT16,_T("1"));
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cs5Dlg::OnPaint()
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	for(int i=0;i<16;i++)
	{
	   ((CEdit*)GetDlgItem(IDC_EDIT1+i))->GetWindowTextW(s[i]);
	    a[i]=_wtof(s[i]);                  //�������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//GetDlgItem(IDC_EDIT1)->GetWindowTextW(sa);
	//    a[0]=_wtof(sa);                  //�������
	//A(1,1)=a[0];
	//GetDlgItem(IDC_EDIT2)->GetWindowTextW(sb);
	//    b[0]=_wtof(sb);                  //�������
	//B.SetData(b,2);                      //2��1����
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
