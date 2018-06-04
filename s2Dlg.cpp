
// s2Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "s2.h"
#include "s2Dlg.h"
#include "afxdialogex.h"

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


// Cs2Dlg �Ի���




Cs2Dlg::Cs2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cs2Dlg::IDD, pParent)
	, m_setok(false)
	, m_strtxdata(_T(""))
	, m_strrxdata(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cs2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combocom);
	DDX_Control(pDX, IDC_MSCOMM1, m_ctrlcomm);
	DDX_Text(pDX, IDC_EDIT1, m_strtxdata);
	DDX_Text(pDX, IDC_EDIT2, m_strrxdata);
	DDX_Control(pDX, IDC_EDIT2, m_ctlrxdata);
	//  DDX_Control(pDX, IDC_BUTTON8, button8);
}

BEGIN_MESSAGE_MAP(Cs2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Cs2Dlg::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &Cs2Dlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON2, &Cs2Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Cs2Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &Cs2Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &Cs2Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &Cs2Dlg::OnBnClickedButton6)
	
	ON_BN_CLICKED(IDC_BUTTON8, &Cs2Dlg::OnBnClickedButton8)
END_MESSAGE_MAP()


// Cs2Dlg ��Ϣ�������

BOOL Cs2Dlg::OnInitDialog()
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
	m_combocom.AddString(_T("COM1")); // Ϊ��Ͽ�ؼ����б������б���  
    m_combocom.AddString(_T("COM2"));   
    m_combocom.AddString(_T("COM3"));   
    m_combocom.AddString(_T("COM4"));   
    m_combocom.AddString(_T("COM5"));   
    m_combocom.AddString(_T("COM6"));   
    m_combocom.AddString(_T("COM7"));   
    m_combocom.AddString(_T("COM8"));   
    m_combocom.AddString(_T("COM9"));   
    m_combocom.AddString(_T("COM10")); 


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Cs2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cs2Dlg::OnPaint()
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
HCURSOR Cs2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Cs2Dlg::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nsel;
	nsel=m_combocom.GetCurSel();//��ȡ��Ͽؼ��б����ѡ���������
	m_ctrlcomm.put_CommPort(nsel+1);//ѡ�񴮿ں�(������Ϊ�б����������Ǵ�0��ʼ������(nSel+1)��Ӧ�Ĳ���������ѡ�Ĵ��ں�)  
    m_ctrlcomm.put_PortOpen(TRUE);//�򿪴���    
    m_ctrlcomm.put_Settings(_T("115200,n,8,1")); 
    m_ctrlcomm.put_InputMode(1);  // �Զ����Ʒ�ʽ��ȡ����   
    m_ctrlcomm.put_RThreshold(2); //����1��ʾÿ�����ڽ��ջ��������ж��ڻ����1���ַ�ʱ������һ���������ݵ�OnComm�¼�   
    m_ctrlcomm.put_InputLen(0); //���õ�ǰ���������ݳ���Ϊ0����ʾȫ����ȡ 
    m_ctrlcomm.get_Input();//��Ԥ���������������������    

    m_setok = true;     //��Ǵ�������OK 

}
BEGIN_EVENTSINK_MAP(Cs2Dlg, CDialogEx)
	ON_EVENT(Cs2Dlg, IDC_MSCOMM1, 1, Cs2Dlg::OnComm, VTS_NONE)
END_EVENTSINK_MAP()


void Cs2Dlg::OnComm()
{
	// TODO: �ڴ˴������Ϣ����������
	VARIANT variant_inp;   //Variant ��һ��������������ͣ����˶���String���ݼ��û����������⣬���԰����κ���������ݡ�  
    COleSafeArray safearray_inp;       
    LONG len,k;      
    BYTE rxdata[2048]; //����BYTE���� An 8-bit integer that is not signed.       
    CString strtemp,lastline; 
	
    if(m_ctrlcomm.get_CommEvent() == 2) //�¼�ֵΪ2��ʾ���ջ����������ַ�       
    {              
        ////////��������Ը����Լ���ͨ��Э����봦�����   
        variant_inp=m_ctrlcomm.get_Input();     //��������    
        safearray_inp=variant_inp;              //VARIANT�ͱ���ת��ΪColeSafeArray�ͱ���  
        len=safearray_inp.GetOneDimSize();      //�õ���Ч���ݳ���          
        for(k=0;k<len;k++)               
            safearray_inp.GetElement(&k,rxdata+k);//ת��ΪBYTE������           
        for(k=0;k<len;k++)                    //������ת��ΪCstring�ͱ���      
        {             
            BYTE bt=*(char*)(rxdata+k);//�ַ���        
            strtemp.Format(_T("%c"),bt); //���ַ�������ʱ����strtemp���     
            m_strrxdata+=strtemp; //������ձ༭���Ӧ�ַ���
			lastline+=strtemp;
		} 
    }      
	/*CString temp=_T("\r\n");
	m_strrxdata+=temp; */ //ʹ���պ���
	CString d=(_T("3"));
	int index=lastline.Find(d);
	int count=0;
	while(index!=-1)
	{
		count++;
		index=lastline.Find(d,index+1);
	}
	if(count==4)
	{
	  SetDlgItemText(IDC_EDIT3,lastline);         ////��������ض��ַ��������ַ���
	}
	else
	{lastline=" ";SetDlgItemText(IDC_EDIT3,lastline);}
    UpdateData(FALSE); //���±༭������ 
	m_ctlrxdata.LineScroll(m_ctlrxdata.GetLineCount());
}

void Cs2Dlg::OnBnClickedButton8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_ctrlcomm.get_PortOpen())
	{
			m_ctrlcomm.put_PortOpen(FALSE);
			SetDlgItemText(IDC_BUTTON8,(_T("��")));
	}
	else
	{
			m_ctrlcomm.put_PortOpen(TRUE);
			SetDlgItemText(IDC_BUTTON8,(_T("��")));
	}
	
}

void Cs2Dlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_setok == true)    //�ж��Ƿ�򿪲���ʼ������  
    {  
        UpdateData(TRUE);  //��ȡ�༭������  
        m_ctrlcomm.put_Output(COleVariant(m_strtxdata+"\r\n")); //��������  
    }   
   else  
    {  
        MessageBox(_T("����ѡ��COM�ڻ�򿪿���"));  
    } 

}

void Cs2Dlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_strrxdata="";
	UpdateData(FALSE);
}


void Cs2Dlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_setok == true)    //�ж��Ƿ�򿪲���ʼ������  
    {  
       CByteArray sjhexdata;
	   sjhexdata.Add(0x30);
	   sjhexdata.Add(0x10);
	   sjhexdata.Add(0x14);
	    
	   m_ctrlcomm.put_OutBufferCount(0);
	   m_ctrlcomm.put_Output(COleVariant(sjhexdata));//��������  
    }   
   else  
    {  
        MessageBox(_T("����ѡ��COM�ڻ�򿪿���"));  
    } 
}


void Cs2Dlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_setok == true)    //�ж��Ƿ�򿪲���ʼ������  
    {  
       CByteArray tzhexdata;
	   tzhexdata.Add(0x30);
	    
	   m_ctrlcomm.put_OutBufferCount(0);
	   m_ctrlcomm.put_Output(COleVariant(tzhexdata));//��������  
    }   
   else  
    {  
        MessageBox(_T("����ѡ��COM�ڻ�򿪿���"));  
    } 
}


void Cs2Dlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_setok == true)    //�ж��Ƿ�򿪲���ʼ������  
    {  
	   /*tz="G00 J1=0 J2=0 J3=-90 J4=0 J5=-90 J6=0";*/
	   CByteArray fwhexdata;
	   
	   fwhexdata.Add(0x10);
	   fwhexdata.Add(0x15);
	   m_ctrlcomm.put_OutBufferCount(0);
       m_ctrlcomm.put_Output(COleVariant(fwhexdata));
	    
	   /*m_ctrlcomm.put_OutBufferCount(0);
	   m_ctrlcomm.put_Output(COleVariant(fwhexdata));*///��������  
    }   
   else  
    {  
        MessageBox(_T("����ѡ��COM�ڻ�򿪿���"));  
    } 
}


void Cs2Dlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_setok == true)    //�ж��Ƿ�򿪲���ʼ������  
    {  
       CByteArray hlhexdata;
	  
	   hlhexdata.Add(0x10);
	   hlhexdata.Add(0x12);
	    
	   m_ctrlcomm.put_OutBufferCount(0);
	   m_ctrlcomm.put_Output(COleVariant(hlhexdata));//��������  
    }   
   else  
    {  
        MessageBox(_T("����ѡ��COM�ڻ�򿪿���"));  
    } 
}
