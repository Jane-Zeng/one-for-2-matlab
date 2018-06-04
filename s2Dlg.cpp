
// s2Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "s2.h"
#include "s2Dlg.h"
#include "afxdialogex.h"

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


// Cs2Dlg 对话框




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


// Cs2Dlg 消息处理程序

BOOL Cs2Dlg::OnInitDialog()
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
	m_combocom.AddString(_T("COM1")); // 为组合框控件的列表框添加列表项  
    m_combocom.AddString(_T("COM2"));   
    m_combocom.AddString(_T("COM3"));   
    m_combocom.AddString(_T("COM4"));   
    m_combocom.AddString(_T("COM5"));   
    m_combocom.AddString(_T("COM6"));   
    m_combocom.AddString(_T("COM7"));   
    m_combocom.AddString(_T("COM8"));   
    m_combocom.AddString(_T("COM9"));   
    m_combocom.AddString(_T("COM10")); 


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cs2Dlg::OnPaint()
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
HCURSOR Cs2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Cs2Dlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	int nsel;
	nsel=m_combocom.GetCurSel();//获取组合控件列表框中选中项的索引
	m_ctrlcomm.put_CommPort(nsel+1);//选择串口号(这里因为列表框的索引号是从0开始，所以(nSel+1)对应的才是我们所选的串口号)  
    m_ctrlcomm.put_PortOpen(TRUE);//打开串口    
    m_ctrlcomm.put_Settings(_T("115200,n,8,1")); 
    m_ctrlcomm.put_InputMode(1);  // 以二进制方式检取数据   
    m_ctrlcomm.put_RThreshold(2); //参数1表示每当串口接收缓冲区中有多于或等于1个字符时将引发一个接收数据的OnComm事件   
    m_ctrlcomm.put_InputLen(0); //设置当前接收区数据长度为0，表示全部读取 
    m_ctrlcomm.get_Input();//先预读缓冲区以清除残留数据    

    m_setok = true;     //标记串口设置OK 

}
BEGIN_EVENTSINK_MAP(Cs2Dlg, CDialogEx)
	ON_EVENT(Cs2Dlg, IDC_MSCOMM1, 1, Cs2Dlg::OnComm, VTS_NONE)
END_EVENTSINK_MAP()


void Cs2Dlg::OnComm()
{
	// TODO: 在此处添加消息处理程序代码
	VARIANT variant_inp;   //Variant 是一种特殊的数据类型，除了定长String数据及用户定义类型外，可以包含任何种类的数据。  
    COleSafeArray safearray_inp;       
    LONG len,k;      
    BYTE rxdata[2048]; //设置BYTE数组 An 8-bit integer that is not signed.       
    CString strtemp,lastline; 
	
    if(m_ctrlcomm.get_CommEvent() == 2) //事件值为2表示接收缓冲区内有字符       
    {              
        ////////以下你可以根据自己的通信协议加入处理代码   
        variant_inp=m_ctrlcomm.get_Input();     //读缓冲区    
        safearray_inp=variant_inp;              //VARIANT型变量转换为ColeSafeArray型变量  
        len=safearray_inp.GetOneDimSize();      //得到有效数据长度          
        for(k=0;k<len;k++)               
            safearray_inp.GetElement(&k,rxdata+k);//转换为BYTE型数组           
        for(k=0;k<len;k++)                    //将数组转换为Cstring型变量      
        {             
            BYTE bt=*(char*)(rxdata+k);//字符型        
            strtemp.Format(_T("%c"),bt); //将字符送入临时变量strtemp存放     
            m_strrxdata+=strtemp; //加入接收编辑框对应字符串
			lastline+=strtemp;
		} 
    }      
	/*CString temp=_T("\r\n");
	m_strrxdata+=temp; */ //使接收后换行
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
	  SetDlgItemText(IDC_EDIT3,lastline);         ////输出出现特定字符次数的字符串
	}
	else
	{lastline=" ";SetDlgItemText(IDC_EDIT3,lastline);}
    UpdateData(FALSE); //更新编辑框内容 
	m_ctlrxdata.LineScroll(m_ctlrxdata.GetLineCount());
}

void Cs2Dlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_ctrlcomm.get_PortOpen())
	{
			m_ctrlcomm.put_PortOpen(FALSE);
			SetDlgItemText(IDC_BUTTON8,(_T("关")));
	}
	else
	{
			m_ctrlcomm.put_PortOpen(TRUE);
			SetDlgItemText(IDC_BUTTON8,(_T("开")));
	}
	
}

void Cs2Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_setok == true)    //判断是否打开并初始化串口  
    {  
        UpdateData(TRUE);  //读取编辑框内容  
        m_ctrlcomm.put_Output(COleVariant(m_strtxdata+"\r\n")); //发送数据  
    }   
   else  
    {  
        MessageBox(_T("请先选择COM口或打开开关"));  
    } 

}

void Cs2Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_strrxdata="";
	UpdateData(FALSE);
}


void Cs2Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_setok == true)    //判断是否打开并初始化串口  
    {  
       CByteArray sjhexdata;
	   sjhexdata.Add(0x30);
	   sjhexdata.Add(0x10);
	   sjhexdata.Add(0x14);
	    
	   m_ctrlcomm.put_OutBufferCount(0);
	   m_ctrlcomm.put_Output(COleVariant(sjhexdata));//发送数据  
    }   
   else  
    {  
        MessageBox(_T("请先选择COM口或打开开关"));  
    } 
}


void Cs2Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_setok == true)    //判断是否打开并初始化串口  
    {  
       CByteArray tzhexdata;
	   tzhexdata.Add(0x30);
	    
	   m_ctrlcomm.put_OutBufferCount(0);
	   m_ctrlcomm.put_Output(COleVariant(tzhexdata));//发送数据  
    }   
   else  
    {  
        MessageBox(_T("请先选择COM口或打开开关"));  
    } 
}


void Cs2Dlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_setok == true)    //判断是否打开并初始化串口  
    {  
	   /*tz="G00 J1=0 J2=0 J3=-90 J4=0 J5=-90 J6=0";*/
	   CByteArray fwhexdata;
	   
	   fwhexdata.Add(0x10);
	   fwhexdata.Add(0x15);
	   m_ctrlcomm.put_OutBufferCount(0);
       m_ctrlcomm.put_Output(COleVariant(fwhexdata));
	    
	   /*m_ctrlcomm.put_OutBufferCount(0);
	   m_ctrlcomm.put_Output(COleVariant(fwhexdata));*///发送数据  
    }   
   else  
    {  
        MessageBox(_T("请先选择COM口或打开开关"));  
    } 
}


void Cs2Dlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_setok == true)    //判断是否打开并初始化串口  
    {  
       CByteArray hlhexdata;
	  
	   hlhexdata.Add(0x10);
	   hlhexdata.Add(0x12);
	    
	   m_ctrlcomm.put_OutBufferCount(0);
	   m_ctrlcomm.put_Output(COleVariant(hlhexdata));//发送数据  
    }   
   else  
    {  
        MessageBox(_T("请先选择COM口或打开开关"));  
    } 
}
