
// s6Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "s6.h"
#include "s6Dlg.h"
#include "afxdialogex.h"
#include "mclmcr.h"
#include "matrix.h"
#include "mclcppclass.h"
#include "mex.h"
#include "matrix.h"
#include <HalconCpp.h>
using namespace std;

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


// Cs6Dlg 对话框




Cs6Dlg::Cs6Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cs6Dlg::IDD, pParent)
	, m_strjsqdata(_T(""))
	, m_strfsqdata(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cs6Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combocom);
	DDX_Control(pDX, IDC_MSCOMM2, m_comm);
	DDX_Control(pDX, IDC_EDIT17, m_editjsq);
	DDX_Text(pDX, IDC_EDIT17, m_strjsqdata);
	DDX_Text(pDX, IDC_EDIT18, m_strfsqdata);
}

BEGIN_MESSAGE_MAP(Cs6Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_dkck, &Cs6Dlg::OnBnClickeddkck)
	ON_BN_CLICKED(IDC_fs, &Cs6Dlg::OnBnClickedfs)
	ON_BN_CLICKED(IDC_jdxs, &Cs6Dlg::OnBnClickedjdxs)
	ON_BN_CLICKED(IDC_jsqc, &Cs6Dlg::OnBnClickedjsqc)
	ON_BN_CLICKED(IDC_hl, &Cs6Dlg::OnBnClickedhl)
	ON_BN_CLICKED(IDC_fw, &Cs6Dlg::OnBnClickedfw)
	ON_BN_CLICKED(IDC_tz, &Cs6Dlg::OnBnClickedtz)
	ON_BN_CLICKED(IDC_sj, &Cs6Dlg::OnBnClickedsj)
	ON_BN_CLICKED(IDC_syjz, &Cs6Dlg::OnBnClickedsyjz)
	ON_BN_CLICKED(IDC_jggcs, &Cs6Dlg::OnBnClickedjggcs)
	ON_BN_CLICKED(IDC_kqxj, &Cs6Dlg::OnBnClickedkqxj)
	ON_BN_CLICKED(IDC_ztxj, &Cs6Dlg::OnBnClickedztxj)
	ON_BN_CLICKED(IDC_gbxj, &Cs6Dlg::OnBnClickedgbxj)
END_MESSAGE_MAP()


// Cs6Dlg 消息处理程序

BOOL Cs6Dlg::OnInitDialog()
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

	GetCom();
	int nselect=m_combocom.GetCurSel()+1;
	m_comm.put_CommPort(short(nselect));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cs6Dlg::GetCom()//程序启动时获取全部可用串口
{
	HANDLE hcom;
	int i,num,k;
	CString str;
	BOOL flag;

	((CComboBox*)GetDlgItem(IDC_COMBO1))->ResetContent();
	flag=false;
	num=0;
	for(i=1;i<=10;i++)
	{
		str.Format(_T("\\\\.\\COM%d"),i);
		hcom=CreateFile(str,0,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
		if(INVALID_HANDLE_VALUE!=hcom)
		{//能打开串口，则添加该串口
			CloseHandle(hcom);
			str=str.Mid(4);
			((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(str);
			if(flag==false)
			{
				flag=true;
				num=i;
			}
		}
	}
	i=((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCount();
	if(i==0)
	{//若找不到可用串口则禁用“打开串口”按钮
		((CComboBox*)GetDlgItem(IDC_COMBO1))->EnableWindow(false);
	}
	else
	{
		k=((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCount();
		((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(k-1);
	}
}

void Cs6Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cs6Dlg::OnPaint()
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
HCURSOR Cs6Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Cs6Dlg::OnBnClickeddkck()
{
	// TODO: 在此添加控件通知处理程序代码
  if(!m_comm.get_PortOpen())
  {
	int nsel;
	nsel=m_combocom.GetCurSel();//获取组合控件列表框中选中项的索引
	m_comm.put_CommPort(nsel+1);//选择串口号(这里因为列表框的索引号是从0开始，所以(nSel+1)对应的才是我们所选的串口号)
	m_comm.put_PortOpen(TRUE);//打开串口    
    m_comm.put_Settings(_T("115200,n,8,1")); 
    m_comm.put_InputMode(1);  // 以二进制方式检取数据   
    m_comm.put_RThreshold(2); //参数1表示每当串口接收缓冲区中有多于或等于1个字符时将引发一个接收数据的OnComm事件   
    m_comm.put_InputLen(0); //设置当前接收区数据长度为0，表示全部读取 
    m_comm.get_Input();//先预读缓冲区以清除残留数据    
	
    m_setok = true;     //标记串口设置OK 
	
	SetDlgItemText(IDC_dkck,(_T("已开(再按关)")));
   }
	else
	{
			m_comm.put_PortOpen(false);
			SetDlgItemText(IDC_dkck,(_T("已关(再按开)")));
			m_setok = false;
	}
}
BEGIN_EVENTSINK_MAP(Cs6Dlg, CDialogEx)
	ON_EVENT(Cs6Dlg, IDC_MSCOMM2, 1, Cs6Dlg::OnComm2, VTS_NONE)
END_EVENTSINK_MAP()


void Cs6Dlg::OnComm2()
{
	// TODO: 在此处添加消息处理程序代码
	VARIANT variant_inp;   //Variant 是一种特殊的数据类型，除了定长String数据及用户定义类型外，可以包含任何种类的数据。  
    COleSafeArray safearray_inp;       
    LONG len,k;      
    BYTE rxdata[2048]; //设置BYTE数组 An 8-bit integer that is not signed.       
    CString strtemp; 
	
    if(m_comm.get_CommEvent() == 2) //事件值为2表示接收缓冲区内有字符       
    {              
        ////////以下你可以根据自己的通信协议加入处理代码   
        variant_inp=m_comm.get_Input();     //读缓冲区    
        safearray_inp=variant_inp;              //VARIANT型变量转换为ColeSafeArray型变量  
        len=safearray_inp.GetOneDimSize();      //得到有效数据长度          
        for(k=0;k<len;k++)               
            safearray_inp.GetElement(&k,rxdata+k);//转换为BYTE型数组           
        for(k=0;k<len;k++)                    //将数组转换为Cstring型变量      
        {             
            BYTE bt=*(char*)(rxdata+k);//字符型        
            strtemp.Format(_T("%c"),bt); //将字符送入临时变量strtemp存放     
            m_strjsqdata+=strtemp; //加入接收编辑框对应字符串
		} 
    }  
	UpdateData(FALSE); //更新编辑框内容 
	m_editjsq.LineScroll(m_editjsq.GetLineCount());
	CString nstr,lstr;
	int i=m_editjsq.GetLineCount();
	if(i>=2)
	{
	   int llen=m_editjsq.LineLength(m_editjsq.LineIndex(i-2));
	   m_editjsq.GetLine(i-2,nstr.GetBuffer(llen),llen);
	   nstr.ReleaseBuffer();
	   lstr.Format(_T("%s"),nstr);//提取到最后一行
	}

	CString d=(_T("J"));
	int index=lstr.Find(d);
	int count=0;
	if(index<4)
	{
	   while(index!=-1)
	   {
		   count++;
		   index=lstr.Find(d,index+1);
	   }
	   if(count>=3)
	   {
		   SetDlgItemText(IDC_EDIT19,lstr); ////输出出现特定字符次数的字符串
	   }
	   else
	   {lstr="";SetDlgItemText(IDC_EDIT19,lstr);}
    //SetDlgItemText(IDC_EDIT19,lstr);
	}
}


void Cs6Dlg::OnBnClickedfs()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_setok == true)    //判断是否打开并初始化串口  
    {  
        UpdateData(TRUE);  //读取编辑框内容
		m_comm.put_OutBufferCount(0);
        m_comm.put_Output(COleVariant(m_strfsqdata+"\r\n")); //发送数据  
    }   
   else  
    {  
        MessageBox(_T("请先选择COM口或打开开关"));  
    } 
}


void Cs6Dlg::OnBnClickedjdxs()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_setok == true)    //判断是否打开并初始化串口  
    {  
        CString jdxs=(_T("G07 GCM=0")); 
		m_comm.put_OutBufferCount(0);
        m_comm.put_Output(COleVariant(jdxs+"\r\n")); //发送数据  
    }   
   else  
    {  
        MessageBox(_T("请先选择COM口或打开开关"));  
    } 
}


void Cs6Dlg::OnBnClickedjsqc()
{
	// TODO: 在此添加控件通知处理程序代码
	m_strjsqdata="";
	UpdateData(FALSE);
}


void Cs6Dlg::OnBnClickedhl()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_setok == true)    //判断是否打开并初始化串口  
    {  
       CByteArray hlhexdata;
	  
	   hlhexdata.Add(0x10);
	   hlhexdata.Add(0x12);
	    
	   m_comm.put_OutBufferCount(0);
	   m_comm.put_Output(COleVariant(hlhexdata));//发送数据  
    }   
   else  
    {  
        MessageBox(_T("请先选择COM口或打开开关"));  
    } 
}


void Cs6Dlg::OnBnClickedfw()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_setok == true)    //判断是否打开并初始化串口  
    {  
        CString fw=(_T("G00 J1=0 J2=0 J3=-90 J4=0 J5=-90 J6=0")); 
		m_comm.put_OutBufferCount(0);
        m_comm.put_Output(COleVariant(fw+"\r\n")); //发送数据  
    }   
   else  
    {  
        MessageBox(_T("请先选择COM口或打开开关"));  
    } 
}


void Cs6Dlg::OnBnClickedtz()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_setok == true)    //判断是否打开并初始化串口  
    {  
       CByteArray tzhexdata;
	   tzhexdata.Add(0x30);
	    
	   m_comm.put_OutBufferCount(0);
	   m_comm.put_Output(COleVariant(tzhexdata));//发送数据  
    }   
   else  
    {  
        MessageBox(_T("请先选择COM口或打开开关"));  
    } 
}


void Cs6Dlg::OnBnClickedsj()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_setok == true)    //判断是否打开并初始化串口  
    {  
       CByteArray sjhexdata;
	   sjhexdata.Add(0x30);
	   sjhexdata.Add(0x10);
	   sjhexdata.Add(0x14);
	    
	   m_comm.put_OutBufferCount(0);//清空发送缓冲区
	   m_comm.put_Output(COleVariant(sjhexdata));//发送数据  
    }   
   else  
    {  
        MessageBox(_T("请先选择COM口或打开开关"));  
    } 
}
BOOL Cs6Dlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_LBUTTONDOWN)
	{
		if(pMsg->hwnd==GetDlgItem(IDC_J1Z)->m_hWnd)////////////1+
		 { 
			if(m_setok == true)
			{
	          CString J1Z=(_T("J1+")); 
	          m_comm.put_OutBufferCount(0);
              m_comm.put_Output(COleVariant(J1Z+"\r\n")); //发送数据
		     }
		  }

		if(pMsg->hwnd==GetDlgItem(IDC_J1F)->m_hWnd)////////////1-
		 { 
			if(m_setok == true)
			{
	          CString J1F=(_T("J1-")); 
	          m_comm.put_OutBufferCount(0);
              m_comm.put_Output(COleVariant(J1F+"\r\n")); //发送数据
		    }
		  }

		if(pMsg->hwnd==GetDlgItem(IDC_J2Z)->m_hWnd)////////////2+
		 { 
			if(m_setok == true)
			{
	          CString J2Z=(_T("J2+")); 
	          m_comm.put_OutBufferCount(0);
              m_comm.put_Output(COleVariant(J2Z+"\r\n")); //发送数据
		    }
		  }

		if(pMsg->hwnd==GetDlgItem(IDC_J2F)->m_hWnd)////////////2-
		 { 
			if(m_setok == true)
			{
	          CString J2F=(_T("J2-")); 
	          m_comm.put_OutBufferCount(0);
              m_comm.put_Output(COleVariant(J2F+"\r\n")); //发送数据
		    }
		  }

		if(pMsg->hwnd==GetDlgItem(IDC_J3Z)->m_hWnd)////////////3+
		 { 
			if(m_setok == true)
			{
	          CString J3Z=(_T("J3+")); 
	          m_comm.put_OutBufferCount(0);
              m_comm.put_Output(COleVariant(J3Z+"\r\n")); //发送数据
		    }
		  }

		if(pMsg->hwnd==GetDlgItem(IDC_J3F)->m_hWnd)////////////3-
		 { 
			if(m_setok == true)
			{
	          CString J3F=(_T("J3-")); 
	          m_comm.put_OutBufferCount(0);
              m_comm.put_Output(COleVariant(J3F+"\r\n")); //发送数据
		    }
		  }

		if(pMsg->hwnd==GetDlgItem(IDC_J4Z)->m_hWnd)////////////4+
		 { 
			if(m_setok == true)
			{
	          CString J4Z=(_T("J4+")); 
	          m_comm.put_OutBufferCount(0);
              m_comm.put_Output(COleVariant(J4Z+"\r\n")); //发送数据
		    }
		  }

		if(pMsg->hwnd==GetDlgItem(IDC_J4F)->m_hWnd)////////////4-
		 { 
			if(m_setok == true)
			{
	          CString J4F=(_T("J4-")); 
	          m_comm.put_OutBufferCount(0);
              m_comm.put_Output(COleVariant(J4F+"\r\n")); //发送数据
		    }
		  }

		if(pMsg->hwnd==GetDlgItem(IDC_J5Z)->m_hWnd)////////////5+
		 { 
			if(m_setok == true)
			{
	          CString J5Z=(_T("J5+")); 
	          m_comm.put_OutBufferCount(0);
              m_comm.put_Output(COleVariant(J5Z+"\r\n")); //发送数据
		    }
		  }

		if(pMsg->hwnd==GetDlgItem(IDC_J5F)->m_hWnd)////////////5-
		 { 
			if(m_setok == true)
			{
	          CString J5F=(_T("J5-")); 
	          m_comm.put_OutBufferCount(0);
              m_comm.put_Output(COleVariant(J5F+"\r\n")); //发送数据
		    }
		  }

		if(pMsg->hwnd==GetDlgItem(IDC_J6Z)->m_hWnd)////////////6+
		 { 
			if(m_setok == true)
			{
	          CString J6Z=(_T("J6+")); 
	          m_comm.put_OutBufferCount(0);
              m_comm.put_Output(COleVariant(J6Z+"\r\n")); //发送数据
		    }
		  }

		if(pMsg->hwnd==GetDlgItem(IDC_J6F)->m_hWnd)////////////6-
		 { 
			if(m_setok == true)
			{
	          CString J6F=(_T("J6-")); 
	          m_comm.put_OutBufferCount(0);
              m_comm.put_Output(COleVariant(J6F+"\r\n")); //发送数据
		    }
		  }
	}
	else if(pMsg->message==WM_LBUTTONUP)
    {
		if(pMsg->hwnd==GetDlgItem(IDC_J1Z)->m_hWnd)////////////1+T
		 { 
		   if (m_setok == true)    //判断是否打开并初始化串口  
            {  
	           CString J1ZT=(_T("J10")); 
	           m_comm.put_OutBufferCount(0);
               m_comm.put_Output(COleVariant(J1ZT+"\r\n")); //发送数据
		    }
		  }

		if(pMsg->hwnd==GetDlgItem(IDC_J1F)->m_hWnd)////////////1-T
		 { 
		   if (m_setok == true)    //判断是否打开并初始化串口  
            {  
	           CString J1FT=(_T("J10")); 
	           m_comm.put_OutBufferCount(0);
               m_comm.put_Output(COleVariant(J1FT+"\r\n")); //发送数据
		    }
		  }

		if(pMsg->hwnd==GetDlgItem(IDC_J2Z)->m_hWnd)////////////2+T
		 { 
		   if (m_setok == true)    //判断是否打开并初始化串口  
            {  
	           CString J2ZT=(_T("J20")); 
	           m_comm.put_OutBufferCount(0);
               m_comm.put_Output(COleVariant(J2ZT+"\r\n")); //发送数据
		    }
		  }

		if(pMsg->hwnd==GetDlgItem(IDC_J2F)->m_hWnd)////////////2-T
		 { 
		   if (m_setok == true)    //判断是否打开并初始化串口  
            {  
	           CString J2FT=(_T("J20")); 
	           m_comm.put_OutBufferCount(0);
               m_comm.put_Output(COleVariant(J2FT+"\r\n")); //发送数据
		    }
		  }

		if(pMsg->hwnd==GetDlgItem(IDC_J3Z)->m_hWnd)////////////3+T
		 { 
		   if (m_setok == true)    //判断是否打开并初始化串口  
            {  
	           CString J3ZT=(_T("J30")); 
	           m_comm.put_OutBufferCount(0);
               m_comm.put_Output(COleVariant(J3ZT+"\r\n")); //发送数据
		    }
		  }

		if(pMsg->hwnd==GetDlgItem(IDC_J3F)->m_hWnd)////////////3-T
		 { 
		   if (m_setok == true)    //判断是否打开并初始化串口  
            {  
	           CString J3FT=(_T("J30")); 
	           m_comm.put_OutBufferCount(0);
               m_comm.put_Output(COleVariant(J3FT+"\r\n")); //发送数据
		    }
		  }

		if(pMsg->hwnd==GetDlgItem(IDC_J4Z)->m_hWnd)////////////4+T
		 { 
		   if (m_setok == true)    //判断是否打开并初始化串口  
            {  
	           CString J4ZT=(_T("J40")); 
	           m_comm.put_OutBufferCount(0);
               m_comm.put_Output(COleVariant(J4ZT+"\r\n")); //发送数据
		    }
		  }

		if(pMsg->hwnd==GetDlgItem(IDC_J4F)->m_hWnd)////////////4-T
		 { 
		   if (m_setok == true)    //判断是否打开并初始化串口  
            {  
	           CString J4FT=(_T("J40")); 
	           m_comm.put_OutBufferCount(0);
               m_comm.put_Output(COleVariant(J4FT+"\r\n")); //发送数据
		    }
		  }

		if(pMsg->hwnd==GetDlgItem(IDC_J5Z)->m_hWnd)////////////5+T
		 { 
		   if (m_setok == true)    //判断是否打开并初始化串口  
            {  
	           CString J5ZT=(_T("J50")); 
	           m_comm.put_OutBufferCount(0);
               m_comm.put_Output(COleVariant(J5ZT+"\r\n")); //发送数据
		    }
		  }

		if(pMsg->hwnd==GetDlgItem(IDC_J5F)->m_hWnd)////////////5-T
		 { 
		   if (m_setok == true)    //判断是否打开并初始化串口  
            {  
	           CString J5FT=(_T("J50")); 
	           m_comm.put_OutBufferCount(0);
               m_comm.put_Output(COleVariant(J5FT+"\r\n")); //发送数据
		    }
		  }

		if(pMsg->hwnd==GetDlgItem(IDC_J6Z)->m_hWnd)////////////6+T
		 { 
		   if (m_setok == true)    //判断是否打开并初始化串口  
            {  
	           CString J6ZT=(_T("J60")); 
	           m_comm.put_OutBufferCount(0);
               m_comm.put_Output(COleVariant(J6ZT+"\r\n")); //发送数据
		    }
		  }

		if(pMsg->hwnd==GetDlgItem(IDC_J6F)->m_hWnd)////////////6-T
		 { 
		   if (m_setok == true)    //判断是否打开并初始化串口  
            {  
	           CString J6FT=(_T("J60")); 
	           m_comm.put_OutBufferCount(0);
               m_comm.put_Output(COleVariant(J6FT+"\r\n")); //发送数据
		    }
		  }
	 }
	return CDialog::PreTranslateMessage(pMsg);
}
void Cs6Dlg::OnOK()
{
	//CDialogEx::OnOK();
}

CString str1,str2,str3,st1,st2,st3,s[16];
	mwArray syjz(4,4,mxDOUBLE_CLASS);
	mwArray jggcs(3,2,mxDOUBLE_CLASS);
double a[6],aa[3][2],b[16],bb[4][4],and[4][4];
void Cs6Dlg::OnBnClickedsyjz()
{
	// TODO: 在此添加控件通知处理程序代码
	for(int i=0;i<16;i++)
	{
	   GetDlgItem(IDC_EDIT1+i)->GetWindowTextW(s[i]);
	    b[i]=_wtof(s[i]);                  //变成数字
	}
	syjz.SetData(b,16);
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
		   bb[i][j]=syjz.Get(2,i+1,j+1);
		   bb[i][j]=bb[i][j]*2;
		   st1.Format(_T("%.5f"),bb[i][j]);
	       str1+=st1+' ';
		}
	   str1+="\r\n";
	}
	for(int i=0;i<16;i++)
	{
	   SetDlgItemText(IDC_EDIT1+i,_T(""));
	}
	SetDlgItemText(IDC_EDIT17,str1);
	str1="";
}

void Cs6Dlg::OnBnClickedjggcs()
{
	// TODO: 在此添加控件通知处理程序代码
	for(int i=0;i<6;i++)
	{
	   GetDlgItem(IDC_EDIT1+i)->GetWindowTextW(s[i]);
	    a[i]=_wtof(s[i]);                  //变成数字
	}
	jggcs.SetData(a,6);
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<2;j++)
		{
		   aa[i][j]=jggcs.Get(2,i+1,j+1);
		   aa[i][j]=aa[i][j]+2;
		   st2.Format(_T("%.5f"),aa[i][j]);
	       str2+=st2+' ';
		}
	   str2+="\r\n";
	}
	for(int i=0;i<6;i++)
	{
	   SetDlgItemText(IDC_EDIT1+i,_T(""));
	}
	SetDlgItemText(IDC_EDIT17,str2);
	str2="";
}

HObject ho_Image1,ho_Image2; 
HTuple hv_AcqHandle1,hv_AcqHandle2;
HTuple hv_Width1,hv_Height1,hv_Width2,hv_Height2; 
HTuple hv_WindowHandle1,hv_WindowHandle2;
HTuple hv_filename;

bool thread=true;
bool threadpause=false;
CWinThread *kqxjthread;
CString teststr;

void Cs6Dlg::OnBnClickedkqxj()
{
	// TODO: 在此添加控件通知处理程序代码
	if(threadpause)//暂停
	{
		threadpause=false;
		kqxjthread->ResumeThread();//则继续
	}
	else
	{
		kqxjthread=AfxBeginThread(kqxjthd,this);//开启线程
	}
}
UINT Cs6Dlg::kqxjthd(LPVOID AParam)
{
	Cs6Dlg* pointer1;
	pointer1 = (Cs6Dlg*)AParam;
	CRect rtWindow1; 
    HWND hImgWnd1 =pointer1->GetDlgItem(IDC_SXJTX)->m_hWnd; 
    pointer1->GetDlgItem(IDC_SXJTX)->GetClientRect(&rtWindow1);
    OpenWindow(rtWindow1.left, rtWindow1.top, rtWindow1.Width(), rtWindow1.Height(), (Hlong)hImgWnd1, "visible", "", &hv_WindowHandle1); 
    try
     {
        OpenFramegrabber("GigEVision", 0, 0, 0, 0, 0, 0, "default", -1, "default", -1, 
        "false", "default", "0223823012", 0, -1, &hv_AcqHandle1);
	  while (thread)
       {
		   MSG msgthd;
		   if(::PeekMessageA(&msgthd,NULL,0,0,PM_REMOVE))
		   {
			   if(msgthd.message==WM_QUIT)
			   {return 0;}
			   else
			   {
				   ::TranslateMessage(&msgthd);
				   ::DispatchMessageA(&msgthd);
			   }
		   }
           GrabImageStart(hv_AcqHandle1,-1);
           GrabImageAsync(&ho_Image1, hv_AcqHandle1, -1);

		   pointer1->GetDlgItem(IDC_EDIT1)->GetWindowTextW(teststr);
		   if(teststr!="")
		    {
			   //hv_filename = ("C:/Users/Administrator/Desktop/capture/maybeuseful/t1.png");
               WriteImage(ho_Image1,"png",0,"test1");
			   pointer1->SetDlgItemText(IDC_EDIT1,_T(""));
			   //////！！！！！！！！！！！！！
			   //处理图片得数据！！！！！！！！！！！！！
		    }
		   GetImageSize(ho_Image1, &hv_Width1, &hv_Height1);
		   SetPart(hv_WindowHandle1, 0, 0,hv_Height1, hv_Width1 );
           HDevWindowStack::Push(hv_WindowHandle1);
           DispObj(ho_Image1, hv_WindowHandle1); 
           //Sleep(2000);//非注释后会造成卡顿
	       ho_Image1.GenEmptyObj();
	    }
     }
	catch(HException &except)
     {
	    AfxMessageBox(CString(except.ErrorMessage())); 
     }
	return 0;
}

void Cs6Dlg::OnBnClickedztxj()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!threadpause)
	{
		kqxjthread->SuspendThread();//挂起、暂停线程
		threadpause=true;
	}
}

void Cs6Dlg::OnBnClickedgbxj()
{
	// TODO: 在此添加控件通知处理程序代码
	if(kqxjthread)
	{
		threadpause=false;
		::PostThreadMessageA(kqxjthread->m_nThreadID,WM_QUIT,0,0);
	}
}
