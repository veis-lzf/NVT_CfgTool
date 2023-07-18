#pragma once

/* INI���������ļ������� */
class CIniFileEdit
{
	LPCTSTR m_pCfgFile; // INI�����ļ�·��

public:
	typedef struct 
	{
		LPCTSTR lpAppName;  // INI�ļ��е�һ���ֶ���.
		LPCTSTR lpKeyName;  // lpAppName�µ�һ������,ͨ�׽����Ǳ�����.
		LPCTSTR lpString;   // ��ֵ, Ҳ���Ǳ�����ֵ,��������ΪLPCTSTR�ͻ�CString�͵�.
		LPCTSTR lpFileName; // �����ļ�·��
	} CfgStrStruct;

	typedef struct
	{
		LPCTSTR lpAppName;  // INI�ļ��е�һ���ֶ���.
		LPCTSTR lpKeyName;  // lpAppName�µ�һ������,ͨ�׽����Ǳ�����.
		INT nDefault;       // ��ֵ, Ҳ���Ǳ�����ֵ,��������ΪLPCTSTR�ͻ�CString�͵�.
		LPCTSTR lpFileName; // �����ļ�·��
	} CfgIntStruct;

public:
	// ��������������
	CIniFileEdit(LPCTSTR file=NULL);
	virtual ~CIniFileEdit();

	// ��ʼ���ļ�/��ȡ�ļ�·������·���׵�ֵַ��Ϊһ������洢��m_pCfgFile
	void SetFileHandle(LPCTSTR handle);
	LPCTSTR GetFileHandle(void);

	// �ַ������ͼ�ֵ����
	DWORD GetProfileString(CfgStrStruct *pCfg, CString &nReturn); // ��ȡ��ֵ
	BOOL SetProfileString(CfgStrStruct *pCfg); // д���ֵ

	// ��ֵ���ͼ�ֵ����
	UINT GetProfileInt(CfgIntStruct* pCfg, INT nDefault=0); // ��ȡ��ֵ

	// ɾ��������
	BOOL RemoveProfileKey(LPCTSTR lpAppName, LPCTSTR lpFileName = NULL); // ɾ���ڵ�
	BOOL RemoveProfileSubKey(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpFileName = NULL); // ɾ����ֵ

};

