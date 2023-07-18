
// NVT_CfgToolDlg.h: 头文件
//

#pragma once
#include "CIniFileEdit.h"

// CNVTCfgToolDlg 对话框
class CNVTCfgToolDlg : public CDialogEx
{
// 构造
public:
	CNVTCfgToolDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NVT_CFGTOOL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual void OnOK();
	afx_msg void OnBnClickedButtonFilebrower();
private:
	CIniFileEdit m_cfgFileEdit;
	// 配置文件路径
	CEdit m_cfgFilePath;
	// 芯片类型
	CComboBox m_ChipType;
	// GPIO分组
	CComboBox m_GpioGroup;
	// 引脚编号
	INT m_GpioPin;
	// gpio电平
	CComboBox m_Level;
	void OnInitGUI();
	// 配置文件路径
	CString m_CfgFile;
	int m_index;
	CString m_szPinIndex, m_szPinLevel, m_outStr, m_szInput;


	struct sValArryType
	{
		int nLen;
		CStringArray sBuf;
	};

	struct sValArryType m_TypeValArray;
	struct sValArryType m_CmdValArray;
	struct sValArryType m_PortValArray[32];
	struct sValArryType m_PinValArray[32];

	BOOL OnLoadCfg(LPCWSTR lpszFilePath);
	CComboBox m_PinMux;
	CEdit m_Result;
public:
	afx_msg void OnGroupSelChange();
	afx_msg void OnChipTypeSelChange();
	int MCU_CombineData();
	int CStringToHex(CString szProtol);
	int GetInputHexStr();
	int CheckValid(TCHAR wch);
	void LoadIniCfgParam();
	void SaveIniCfgParam();
private:
	CEdit m_cmdType;
};
