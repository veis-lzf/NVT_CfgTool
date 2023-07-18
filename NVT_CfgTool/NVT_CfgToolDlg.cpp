
// NVT_CfgToolDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "NVT_CfgTool.h"
#include "NVT_CfgToolDlg.h"
#include "afxdialogex.h"
#include "CIniFileEdit.h"
#include "CSplitStr.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNVTCfgToolDlg 对话框
CArray<BYTE> g_buf;

CNVTCfgToolDlg::CNVTCfgToolDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NVT_CFGTOOL_DIALOG, pParent)
	, m_GpioPin(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON5);
	m_CfgFile.SetString(_T(""));
	m_index = 0;
	m_CfgFile = _T("./Config/Config.ini");
}

void CNVTCfgToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CfgFilePath, m_cfgFilePath);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_ChipType);
	DDX_Control(pDX, IDC_COMBO_TYPE2, m_GpioGroup);
	DDX_CBIndex(pDX, IDC_COMBO_TYPE3, m_GpioPin);
	DDX_Control(pDX, IDC_COMBO_TYPE4, m_Level);
	DDX_Control(pDX, IDC_COMBO_TYPE3, m_PinMux);
	DDX_Control(pDX, IDC_EDIT_Result, m_Result);
	DDX_Control(pDX, IDC_EDIT_Cmd, m_cmdType);
}

BEGIN_MESSAGE_MAP(CNVTCfgToolDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CNVTCfgToolDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CNVTCfgToolDlg::OnBnClickedCancel)
	ON_BN_CLICKED(ID_BUTTON_FileBrower, &CNVTCfgToolDlg::OnBnClickedButtonFilebrower)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE2, &CNVTCfgToolDlg::OnGroupSelChange)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, &CNVTCfgToolDlg::OnChipTypeSelChange)
END_MESSAGE_MAP()


// CNVTCfgToolDlg 消息处理程序

BOOL CNVTCfgToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	OnInitGUI();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CNVTCfgToolDlg::OnPaint()
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
HCURSOR CNVTCfgToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNVTCfgToolDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
//	CDialogEx::OnOK();
	int nCurSel = m_ChipType.GetCurSel();
	CString sCurSel;
	m_ChipType.GetWindowText(sCurSel);
	if (!_tcscmp(sCurSel, _T("MCU")))
	{
		MCU_CombineData();
	}
	else if (!_tcscmp(sCurSel, _T("NT98332")) || !_tcscmp(sCurSel, _T("NT98331")))
	{
		int baseOffset[] = { 0, 8, 13, 45, 61, 71 };
		// 组内引脚数
		int pinNumInGroup = m_PinValArray[m_GpioGroup.GetCurSel()].sBuf.GetCount();
		// 组序号
		int GroupOrder = m_GpioGroup.GetItemData(m_GpioGroup.GetCurSel());
		// 引脚序号
		int pinNum = m_PinMux.GetItemData(m_PinMux.GetCurSel());
		// 电平
		int nLevel = m_Level.GetItemData(m_Level.GetCurSel());
		CString szOutPut;
		szOutPut.Format(_T("nvt_gpio_test %d 1 %d"), baseOffset[GroupOrder]+ pinNum, nLevel);
		m_Result.SetWindowText(szOutPut);
	}
	else if (!_tcscmp(sCurSel, _T("NT98323")) || !_tcscmp(sCurSel, _T("NT98321")))
	{
		// 组内引脚数
		int pinNumInGroup = m_PinValArray[m_GpioGroup.GetCurSel()].sBuf.GetCount();
		// 组序号
		int GroupOrder = m_GpioGroup.GetItemData(m_GpioGroup.GetCurSel());
		// 引脚序号
		int pinNum = m_PinMux.GetItemData(m_PinMux.GetCurSel());
		// 电平
		int nLevel = m_Level.GetItemData(m_Level.GetCurSel());
		CString szOutPut;
		szOutPut.Format(_T("nvt_gpio_test %d 1 %d"), GroupOrder*32+pinNum, nLevel);
		m_Result.SetWindowText(szOutPut);
	}
}


void CNVTCfgToolDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}



void CNVTCfgToolDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	//CDialogEx::OnOK();
}


void CNVTCfgToolDlg::OnBnClickedButtonFilebrower()
{
	static TCHAR BASED_CODE szFilter[] = 
		_T("ini Files (*.ini)|*.ini|")
		_T("txt Files (*.txt)|*.txt|")
		_T("All Files (*.*)|*.*||");

	CString path;
	m_cfgFilePath.GetWindowText(path);

	CFileDialog fileDlg(TRUE, NULL, path.GetString(),
		OFN_EXPLORER | OFN_HIDEREADONLY, szFilter);

	INT nRet = fileDlg.DoModal();

	if (nRet == IDCANCEL)
		return;

	 // 加载配置文件路径
	m_cfgFilePath.SetWindowText(fileDlg.GetPathName());
	m_CfgFile = fileDlg.GetPathName();
	OnLoadCfg(m_CfgFile);
}


void CNVTCfgToolDlg::OnInitGUI()
{
	OnLoadCfg(m_CfgFile);
	m_cfgFilePath.SetWindowText(m_CfgFile);
}

BOOL CNVTCfgToolDlg::OnLoadCfg(LPCWSTR lpszFilePath)
{
	if (lpszFilePath == NULL)
		return FALSE;

	CIniFileEdit::CfgStrStruct strTmp;
	CString strKeyValue;
	CSplitStr SplitStr;
	int Count = 0;

	m_ChipType.ResetContent();
	m_GpioGroup.ResetContent();
	m_PinMux.ResetContent();
	m_Level.ResetContent();

	m_TypeValArray.sBuf.RemoveAll();
	m_CmdValArray.sBuf.RemoveAll();
	for (int i = 0; i < 32; ++i)
	{
		m_PortValArray[i].sBuf.RemoveAll();
		m_PinValArray[i].sBuf.RemoveAll();
	}

	// 加载芯片类型：格式，字段内容+,：TYPE=NT98332,98331,...
	m_cfgFileEdit.SetFileHandle(lpszFilePath);
	strTmp.lpAppName = _T("CHIP_TYPE");
	strTmp.lpKeyName = _T("TYPE");
	strTmp.lpFileName = NULL;
	m_cfgFileEdit.GetProfileString(&strTmp, strKeyValue);
	// 设置分隔符为','
	SplitStr.SetSplitFlag(_T(","));
	SplitStr.SetSequenceAsOne(TRUE);
	SplitStr.SetData(strKeyValue.GetString()); // 需要传入实际字符串地址
	SplitStr.GetSplitStrArray(m_TypeValArray.sBuf);
	m_TypeValArray.nLen = m_TypeValArray.sBuf.GetCount();

	for (Count = 0; Count < m_TypeValArray.nLen; ++Count)
	{
		m_ChipType.SetItemData(m_ChipType.AddString(m_TypeValArray.sBuf.GetAt(Count)), Count);
	}

	// 加载GPIO组
	strTmp.lpAppName = _T("GPIO_GROUP");
	strTmp.lpKeyName = _T("PORT");
	strTmp.lpFileName = NULL;
	m_cfgFileEdit.GetProfileString(&strTmp, strKeyValue);

	// 设置分隔符为'%'
	CStringArray tmpBuf;
	SplitStr.SetSplitFlag(_T("%"));
	SplitStr.SetSequenceAsOne(TRUE);
	SplitStr.SetData(strKeyValue.GetString());
	SplitStr.GetSplitStrArray(tmpBuf);;

	for(int i = 0; i < tmpBuf.GetCount(); ++i)
	{
		SplitStr.SetSplitFlag(_T(","));
		SplitStr.SetSequenceAsOne(TRUE);
		SplitStr.SetData(tmpBuf.GetAt(i));
		SplitStr.GetSplitStrArray(m_PortValArray[i].sBuf);
	}
	m_PortValArray->nLen = m_PortValArray->sBuf.GetCount();

	// 加载PIN组
	strTmp.lpAppName = _T("GPIO_PINMUX");
	strTmp.lpKeyName = _T("PINMUX");
	strTmp.lpFileName = NULL;
	m_cfgFileEdit.GetProfileString(&strTmp, strKeyValue);

	SplitStr.SetSplitFlag(_T("%"));
	SplitStr.SetSequenceAsOne(TRUE);
	SplitStr.SetData(strKeyValue.GetString());
	tmpBuf.RemoveAll(); // 清空临时缓冲区，再进行数据拷贝
	SplitStr.GetSplitStrArray(tmpBuf);

	for (int i = 0; i < tmpBuf.GetCount(); ++i)
	{
		SplitStr.SetSplitFlag(_T(","));
		SplitStr.SetSequenceAsOne(TRUE);
		SplitStr.SetData(tmpBuf.GetAt(i));
		SplitStr.GetSplitStrArray(m_PinValArray[i].sBuf);
	}
	m_PinValArray->nLen = m_PinValArray->sBuf.GetCount();

	// 加载命令格式
	strTmp.lpAppName = _T("PROTOCOL_HEAD");
	strTmp.lpKeyName = _T("PROTOCOL");
	strTmp.lpFileName = NULL;
	m_cfgFileEdit.GetProfileString(&strTmp, strKeyValue);

	SplitStr.SetSplitFlag(_T("%"));
	SplitStr.SetSequenceAsOne(TRUE);
	SplitStr.SetData(strKeyValue.GetString());
	SplitStr.GetSplitStrArray(m_CmdValArray.sBuf);


	// 设置缺省显示
	int nCurSel = 0;
	m_ChipType.SetCurSel(nCurSel);

	for (int subCount = 0; subCount < m_PortValArray[m_ChipType.GetCurSel()].sBuf.GetCount(); ++subCount)
	{
		m_GpioGroup.SetItemData(m_GpioGroup.AddString(m_PortValArray[m_ChipType.GetCurSel()].sBuf.GetAt(subCount)), subCount);
	}
	m_GpioGroup.SetCurSel(m_ChipType.GetCurSel());

	CString szStr;
	int nNum = _ttoi(m_PinValArray->sBuf.GetAt(m_GpioGroup.GetCurSel()));
	for (int i = 0; i < nNum; ++i)
	{
		szStr.Format(_T("%d"), i);
		m_PinMux.SetItemData(m_PinMux.AddString(szStr), i);
	}
	m_PinMux.SetCurSel(m_ChipType.GetCurSel());

	m_Level.SetItemData(m_Level.AddString(_T("高电平")), 1);
	m_Level.SetItemData(m_Level.AddString(_T("低电平")), 0);
	m_Level.SetCurSel(0);

	m_cmdType.SetWindowText(m_CmdValArray.sBuf.GetAt(m_ChipType.GetCurSel()));

	return TRUE;
}


void CNVTCfgToolDlg::OnGroupSelChange()
{
	CString szStr;
	int nNum = _ttoi(m_PinValArray[m_ChipType.GetCurSel()].sBuf.GetAt(m_GpioGroup.GetCurSel()));
	m_PinMux.ResetContent();
	for (int i = 0; i < nNum; ++i)
	{
		szStr.Format(_T("%d"), i);
		m_PinMux.SetItemData(m_PinMux.AddString(szStr), i);
	}
	m_PinMux.SetCurSel(0);
}


void CNVTCfgToolDlg::OnChipTypeSelChange()
{
	m_GpioGroup.ResetContent();
	for (int subCount = 0; subCount < m_PortValArray[m_ChipType.GetCurSel()].sBuf.GetCount(); ++subCount)
	{
		m_GpioGroup.SetItemData(m_GpioGroup.AddString(m_PortValArray[m_ChipType.GetCurSel()].sBuf.GetAt(subCount)), subCount);
	}
	m_GpioGroup.SetCurSel(0);

	m_cmdType.SetWindowText(m_CmdValArray.sBuf.GetAt(m_ChipType.GetCurSel()));

	OnGroupSelChange();
}
/**
 * @brief 把数据组合，并输出结果
 * @return 保留参数，未使用
*/
int CNVTCfgToolDlg::MCU_CombineData()
{
	CString str;
	m_cmdType.GetWindowText(str);
	int port_index = m_GpioGroup.GetItemData(m_GpioGroup.GetCurSel());
	int pin_index = m_PinMux.GetItemData(m_PinMux.GetCurSel());
	int level = m_Level.GetItemData(m_Level.GetCurSel());

	int port_result = port_index * 32 + pin_index;
	m_szPinIndex.Format(_T("%02x"), port_result);

	m_szPinLevel.Format(_T("%02d"), level);

	int ret = GetInputHexStr();
	if (ret == -1)
	{
		MessageBox(_T("输入错误！"), _T("错误提示"), MB_ICONERROR);
		return -1;
	}
	m_outStr = m_szInput;
	str.Format(_T("%s %s "), m_szPinIndex.GetString(), m_szPinLevel.GetString());
	m_outStr += str;
	CStringToHex(m_outStr);


	BYTE ch = 0;
	for (int i = 0; i < g_buf.GetCount(); ++i)
	{
		ch ^= g_buf[i];
	}
	str.Format(_T("%02x"), ch);
	m_outStr += str;
	m_outStr.MakeUpper();
	m_outStr = _T("\\x") + m_outStr;
	m_Result.SetWindowText( m_outStr);
	return 0;
}

/**
 * @bref CString转hex
 * @param szProtol 16进制字符串序列
 * @return 保留参数，未使用
*/
int CNVTCfgToolDlg::CStringToHex(CString szProtol)
{
	TCHAR wcha_hex[] = _T("0123456789ABCDEF");
	char hex[] = "0123456789ABCDEF";

	int flag = 0;
	int nLen = szProtol.GetLength();
	char ch = 0;
	szProtol.MakeUpper();
	g_buf.RemoveAll();
	TCHAR wch_h, wch_l;
	for (int i = 0; i < nLen - 1; ++i)
	{
		wch_h = szProtol.GetAt(i);
		wch_l = szProtol.GetAt(i + 1);
		for (int j = 0; j < sizeof(wcha_hex) / sizeof(TCHAR); ++j)
		{
			if (wch_h == wcha_hex[j])
			{
				for (int k = 0; k < sizeof(wcha_hex) / sizeof(TCHAR); ++k)
				{
					if (wch_l == wcha_hex[k])
					{
						ch = (j << 4) | k;
						g_buf.Add(ch);
						i++;
						flag = 1;
						break;
					}
				}
				if (flag)
				{
					flag = 0;
					break;
				}
			}
		}
	}

	return 0;
}

/**
 * @bref 获取输入的16进制字符串序列，并整理序列格式
 * @return 获取到非法字符，返回-1；否则返回0
*/
int CNVTCfgToolDlg::GetInputHexStr()
{
	CString str, result;
	m_cmdType.GetWindowText(str);

	if (str.IsEmpty())
		return -1;

	str.Delete(0, 2);
	int nLen = str.GetLength();
	str.TrimLeft();
	str.TrimRight();
	str.MakeUpper();
	TCHAR wch_h, wch_l;
	CString tmp;
	for (int i = 0; i < nLen; i++)
	{
		wch_h = str.GetAt(i);
		if (-1 == CheckValid(wch_h))
			return -1;

		while (wch_h == _T(' '))
			wch_h = str.GetAt(++i);

		wch_l = str.GetAt(++i);
		if (-1 == CheckValid(wch_l))
			return -1;

		if (wch_l == _T(' ') || wch_l == _T('\0'))
			tmp.Format(_T("0%c "), wch_h);
		else
			tmp.Format(_T("%c%c "), wch_h, wch_l);

		result += tmp;
	}
	m_szInput = result;

	return 0;
}

/**
 * @name CheckValid
 * @bref 判断输入字符是否有效，落在16进制的字符序列中
 * @param wch 输入的字符
 * @return 有效返回0，否则返回-1
*/
int CNVTCfgToolDlg::CheckValid(TCHAR wch)
{
	TCHAR whex[] = _T("0123456789ABCDEF ");
	for (int i = 0; i < sizeof(whex) / sizeof(TCHAR); ++i)
	{
		if (whex[i] == wch)
			return 0;
	}
	return -1;
}

/*
 * 从本地ini配置文件加载参数
 **/
void CNVTCfgToolDlg::LoadIniCfgParam()
{
	CString szToolPath, szFilePath;
	m_cfgFileEdit.SetFileHandle(_T("./Config/Config.ini"));

}

/*
 * 保存窗口信息到本地INI文件
 **/
void CNVTCfgToolDlg::SaveIniCfgParam()
{

}