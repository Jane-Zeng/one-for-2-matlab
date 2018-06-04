
// s4Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "s4.h"
#include "s4Dlg.h"
#include "afxdialogex.h"
#include "guitest.h"
#include <iostream>
#include "mclmcr.h"
#include "matrix.h"
#include "mclcppclass.h"
#include "pmp560.h"
#include "sanxi.h"
#include "zhic.h"
#pragma comment(lib,"pmp560.lib")
#pragma comment(lib,"guitest.lib")
#pragma comment(lib,"sanxi.lib")
#pragma comment(lib,"zhic.lib")
using namespace std;

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


// Cs4Dlg �Ի���




Cs4Dlg::Cs4Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cs4Dlg::IDD, pParent)
	, fedit(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cs4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SPIN1, spinc);
	DDX_Text(pDX, IDC_EDIT1, fedit);
	DDX_Control(pDX, IDC_EDIT2, medit);
	DDX_Control(pDX, IDC_EDIT4, pedit);
}

BEGIN_MESSAGE_MAP(Cs4Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &Cs4Dlg::OnDeltaposSpin1)
	
	ON_BN_CLICKED(IDC_BUTTON1, &Cs4Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Cs4Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// Cs4Dlg ��Ϣ�������

BOOL Cs4Dlg::OnInitDialog()
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
	/*if(!guitestInitialize())
	{
		cout<<"could not initialize libmysvd!"<<endl;
		exit(0);
	}*/
	/*if( ! mclInitializeApplication(NULL,0) )
 {
 fprintf(stderr, "Could not initialize the application.n");
 exit(1);
 }*/
	if(!pmp560Initialize())
	{
		cout<<"could not initialize libmysvd!"<<endl;
		exit(0);
	}
	if(!sanxiInitialize())
	{
		cout<<"could not initialize libmysvd!"<<endl;
		exit(0);
	}
	if(!zhicInitialize())
	{
		cout<<"could not initialize libmysvd!"<<endl;
		exit(0);
	}
	spinc.SetRange(0,4);
	fedit=2;
	UpdateData(false);
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Cs4Dlg::OnDestroy()
{
	CDialog::OnDestroy();
	//guitestTerminate();
}

void Cs4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cs4Dlg::OnPaint()
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
HCURSOR Cs4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cs4Dlg::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	
	if(pNMUpDown->iDelta==1)//������ϼ�ͷ
	{
		UpdateData(TRUE);
		fedit+=0.5;
		if(fedit>4)
			fedit=4;
		UpdateData(FALSE);
	}
	else if(pNMUpDown->iDelta==-1)//������¼�ͷ
	{
		UpdateData(TRUE);
		fedit-=0.5;
		if(fedit<0)
			fedit=0;
		UpdateData(FALSE);
	}
}
   
void Cs4Dlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//guitestInitialize();
	//UpdateData(TRUE);

	//double lam=fedit;//=2
	//double *lp=&lam;
	//double lambda[1]={*lp};
	//mwArray l(1,1,mxDOUBLE_CLASS);
	//l.SetData(lambda,1);
	CString str,ss1,t,f;
	mwArray Z(1,6,mxDOUBLE_CLASS);
	mwArray T(4,4,mxDOUBLE_CLASS);
	double n[4][4]={0};
	double z[6]={0};
	
	GetDlgItem(IDC_EDIT2)->GetWindowTextW(str);
	for(int i=0;i<6;i++)
	{
		AfxExtractSubString(ss1,str,i,' ');//�ַ��ָ�
		z[i]=_wtof(ss1);                   //�������
	}
	Z.SetData(z,6);
	pmp560(1,T,Z);
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			n[i][j]=T.Get(2,(i+1),(j+1));
		    t.Format(_T("%.5f"),n[i][j]);       //����ַ�
            f+=t+' ';
		}
		f+="\r\n";
	}
	SetDlgItemText(IDC_EDIT3,f);
	CString path(_T("C:\\Users\\Administrator\\Desktop\\capture\\maybeuseful\\filename.bmp"));
	CImage image;
	image.Load(path);
	CRect rec,rep;
	::SetForegroundWindow(this->m_hWnd);//�Ի���ʼ����ǰ
	CWnd *pwnd=GetDlgItem(IDC_STATIC1);//��ȡ�ؼ����
	pwnd->GetClientRect(rec);             //ָ������
	CDC *pdc=GetDlgItem(IDC_STATIC1)->GetDC();//��ȡpicture��DC
	
	SetStretchBltMode(pdc->m_hDC,STRETCH_HALFTONE);//������ָ���豸�����е���չģʽ�����λͼʧ��
	rep=CRect(rec.TopLeft(),CSize((int)rec.Width(),(int)rec.Height()));
	//image.StretchBlt(pdc->m_hDC,rep,SRCCOPY);//ͬimage.Draw��ͼ��
	image.Draw(pdc->m_hDC,rep);
	image.Destroy();
	pwnd->ReleaseDC(pdc);       //�ͷ���Դ���������ڴ�й©��ʱ��ÿɼ�Ӱ��
	
}

void Cs4Dlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
    CString str1,str2,str3,ss1,ss2,st,sf;
	mwArray Q(1,6,mxDOUBLE_CLASS);
	mwArray T(4,4,mxDOUBLE_CLASS);
	double n[4][4]={0};
	double q[6]={0};
	int len1=medit.LineLength(medit.LineIndex(0));
	medit.GetLine(0,str1.GetBuffer(len1),len1);
	for(int i=0;i<6;i++)
	{
		AfxExtractSubString(ss1,str1,i,' ');//�ַ��ָ�
		//AfxExtractSubString(ss2,ss1,1,'=');
		q[i]=_wtof(ss1);                   //�������
	}
	Q.SetData(q,6);
	sanxi(1,T,Q);
	for(int i=0;i<4;i++)
	{ 
		for(int j=0;j<4;j++)
		{
			n[i][j]=T.Get(2,(i+1),(j+1));     
	        st.Format(_T("%.5f"),n[i][j]);       //����ַ�
            sf+=st+' ';
		}
		sf+="\r\n";
	}
	SetDlgItemText(IDC_EDIT3,sf);
	CString path1(_T("C:\\Users\\Administrator\\Desktop\\capture\\maybeuseful\\1.bmp"));
	CImage image1;
	image1.Load(path1);
	CRect rec1,rep1;
	::SetForegroundWindow(this->m_hWnd);//�Ի���ʼ����ǰ
	CWnd *pwnd1=GetDlgItem(IDC_STATIC1);//��ȡ�ؼ����
	pwnd1->GetClientRect(rec1);             //ָ������
	CDC *pdc1=GetDlgItem(IDC_STATIC1)->GetDC();//��ȡpicture��DC
	
	SetStretchBltMode(pdc1->m_hDC,STRETCH_HALFTONE);//������ָ���豸�����е���չģʽ�����λͼʧ��
	rep1=CRect(rec1.TopLeft(),CSize((int)rec1.Width(),(int)rec1.Height()));
	//image.StretchBlt(pdc->m_hDC,rep,SRCCOPY);//ͬimage.Draw��ͼ��
	image1.Draw(pdc1->m_hDC,rep1);
	image1.Destroy();
	pwnd1->ReleaseDC(pdc1);       //�ͷ���Դ���������ڴ�й©��ʱ��ÿɼ�Ӱ��
	/*for(int i=0;i<6;i++){
	st.Format(_T("%g"),q[i]);
	sf+=st+' ';}
	SetDlgItemText(IDC_EDIT3,sf);*/
	mwArray Q1(1,6,mxDOUBLE_CLASS);
	mwArray Q2(1,6,mxDOUBLE_CLASS);
	double q1[6]={0},q2[6]={0};
	int len2=medit.LineLength(medit.LineIndex(1));
	medit.GetLine(1,str2.GetBuffer(len2),len2);
	for(int i=0;i<6;i++)
	{
		AfxExtractSubString(ss1,str2,i,' ');//�ַ��ָ�
		//AfxExtractSubString(ss2,ss1,1,'=');
		q1[i]=_wtof(ss1);                   //�������
	}
	Q1.SetData(q1,6);
	int len3=medit.LineLength(medit.LineIndex(2));
	medit.GetLine(2,str3.GetBuffer(len3),len3);
	for(int i=0;i<6;i++)
	{
		AfxExtractSubString(ss1,str3,i,' ');//�ַ��ָ�
		//AfxExtractSubString(ss2,ss1,1,'=');
		q2[i]=_wtof(ss1);                   //�������
	}
	Q2.SetData(q2,6);
	zhic(Q1,Q2);
	CString path2(_T("C:\\Users\\Administrator\\Desktop\\capture\\maybeuseful\\2.bmp"));
	CImage image2;
	image2.Load(path2);
	CRect rec2,rep2;
	::SetForegroundWindow(this->m_hWnd);//�Ի���ʼ����ǰ
	CWnd *pwnd2=GetDlgItem(IDC_STATIC2);//��ȡ�ؼ����
	pwnd2->GetClientRect(rec2);             //ָ������
	CDC *pdc2=GetDlgItem(IDC_STATIC2)->GetDC();//��ȡpicture��DC
	
	SetStretchBltMode(pdc2->m_hDC,STRETCH_HALFTONE);//������ָ���豸�����е���չģʽ�����λͼʧ��
	rep2=CRect(rec2.TopLeft(),CSize((int)rec2.Width(),(int)rec2.Height()));
	//image.StretchBlt(pdc->m_hDC,rep,SRCCOPY);//ͬimage.Draw��ͼ��
	image2.Draw(pdc2->m_hDC,rep2);
	image2.Destroy();
	pwnd2->ReleaseDC(pdc2); 
	
	CString path3(_T("C:\\Users\\Administrator\\Desktop\\capture\\maybeuseful\\3.bmp"));
	CImage image3;
	image3.Load(path3);
	CRect rec3,rep3;
	::SetForegroundWindow(this->m_hWnd);//�Ի���ʼ����ǰ
	CWnd *pwnd3=GetDlgItem(IDC_STATIC3);//��ȡ�ؼ����
	pwnd3->GetClientRect(rec3);             //ָ������
	CDC *pdc3=GetDlgItem(IDC_STATIC3)->GetDC();//��ȡpicture��DC
	
	SetStretchBltMode(pdc3->m_hDC,STRETCH_HALFTONE);//������ָ���豸�����е���չģʽ�����λͼʧ��
	rep3=CRect(rec3.TopLeft(),CSize((int)rec3.Width(),(int)rec3.Height()));
	//image.StretchBlt(pdc->m_hDC,rep,SRCCOPY);//ͬimage.Draw��ͼ��
	image3.Draw(pdc3->m_hDC,rep3);
	image3.Destroy();
	pwnd3->ReleaseDC(pdc3); 
}


BOOL Cs4Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	
	/*if(WM_KEYFIRST<=pMsg->message&&pMsg->message<=WM_KEYLAST)
	{*///������ʹ�������ִ�����飬Ӧ����WM_KEYDOWN
	if(pMsg->message==WM_KEYDOWN)
	{
		if(pMsg->wParam==VK_RETURN)
		{
			if(GetDlgItem(IDC_EDIT2)==GetFocus())
			{
			/*HWND hwnd=::GetFocus();
			int iid=::GetDlgCtrlID(hwnd);
			if(iid==1003)
			{*/
				CString str,nstr,lstr;
				GetDlgItem(IDC_EDIT2)->GetWindowTextW(str);
				int i=medit.GetLineCount();
				int len=medit.LineLength(medit.LineIndex(i-1));
				medit.GetLine(i-1,nstr.GetBuffer(len),len);
				nstr.ReleaseBuffer();
				lstr.Format(_T("%s"),nstr);
	            SetDlgItemText(IDC_EDIT4,lstr);
				return false; //����Ҫ��false��������Ϊ��������Ϣ��ʹֱ֮�Ӵ�����ȥ
			}
			//return false;
		}
		//return false;
	}
	return CDialog::PreTranslateMessage(pMsg);
}
