#include "pch.h"
#include "CIniFileEdit.h"

CIniFileEdit::CIniFileEdit(LPCTSTR file)
{
    m_pCfgFile = file;
}

CIniFileEdit::~CIniFileEdit()
{
}

/*
 * @brief�����ñ���INI�����ļ�·��
 * @param��
 *      handle��INI�����ļ�·��
 **/
void CIniFileEdit::SetFileHandle(LPCTSTR handle)
{
    m_pCfgFile = handle;
}

/*
 * @brief����ȡ����INI�����ļ�·��
 * @return������m_pCfgFile��ֵ�����û�δ��ʼ����ȱʡΪNULL
 **/
LPCTSTR CIniFileEdit::GetFileHandle(void)
{
    return m_pCfgFile;
}

/*
 * @brief����ȡ�ַ�����ֵ
 * @param��
 *      pCfg����ֵ�ṹ��
 *      szReturn������ֵ������
 * @return������ֵ�Ǹ��Ƶ����������ַ���������������ֹ�ַ�
 **/
DWORD CIniFileEdit::GetProfileString(CfgStrStruct* pCfg, CString& szReturn)
{
    if (NULL == pCfg->lpFileName && NULL == m_pCfgFile)
        return NULL;

    LPCTSTR fileName;
    pCfg->lpString = NULL; // ȱʡֵ����ΪNULL
    if (NULL != pCfg->lpFileName)
        fileName = pCfg->lpFileName;
    else
        fileName = m_pCfgFile;

    return ::GetPrivateProfileString(pCfg->lpAppName, pCfg->lpKeyName, pCfg->lpString, 
        szReturn.GetBuffer(MAX_PATH), MAX_PATH, fileName);
}

/*
 * @brief���Ѽ�ֵд�뱾��INI�����ļ�
 * @param��
 *      pCfg����ֵ�ṹ�壬�����@CfgIntStruct
 * @return���ɹ�����TRUE�����򷵻�FALSE
 **/
BOOL CIniFileEdit::SetProfileString(CfgStrStruct* pCfg)
{
    if (NULL == pCfg->lpFileName && NULL == m_pCfgFile)
        return NULL;

    LPCTSTR fileName;
    if (NULL != pCfg->lpFileName)
        fileName = pCfg->lpFileName;
    else
        fileName = m_pCfgFile;

    return ::WritePrivateProfileString(pCfg->lpAppName, pCfg->lpKeyName, pCfg->lpString, fileName);
}

/*
 * @brief����ȡ�ַ�����ֵ
 * @param��
 *      pCfg����ֵ�ṹ��
 *      nDefault��Ĭ�Ϸ���ֵ��ע������ȡ������ֵʱ��Ĭ�Ϸ��أ�
 * @return������ֵ�Ǹ��Ƶ����������ַ���������������ֹ�ַ������򷵻�Ĭ��ֵ��ȱʡΪ0��
 **/
UINT CIniFileEdit::GetProfileInt(CfgIntStruct* pCfg, INT nDefault)
{
    if (NULL == pCfg->lpFileName && NULL == m_pCfgFile)
        return NULL;

    LPCTSTR fileName;
    if (NULL != pCfg->lpFileName)
        fileName = pCfg->lpFileName;
    else
        fileName = m_pCfgFile;

    return ::GetPrivateProfileInt(pCfg->lpAppName, pCfg->lpKeyName, nDefault, fileName);
}

/*
 * @brief��ɾ������ڵ��ֵ
 * @param��
 *      lpAppName���ڵ��ֵ����
 *      lpFileName�������ļ�·����ȱʡΪNULL��ʹ��m_pCfgFile��ֵ
 * @return���ɹ�����TRUE�����򷵻�FALSE
 **/
BOOL CIniFileEdit::RemoveProfileKey(LPCTSTR lpAppName, LPCTSTR lpFileName)
{
    if (NULL == lpFileName && NULL == m_pCfgFile)
        return NULL;

    LPCTSTR fileName;
    if (NULL != lpFileName)
        fileName = lpFileName;
    else
        fileName = m_pCfgFile;

    return ::WritePrivateProfileString(lpAppName, NULL , NULL, fileName);
}

/*
 * @brief��ɾ���Ӽ�ֵ
 * @param��
 *      lpAppName���ڵ��ֵ����
 *      lpKeyName���Ӽ�ֵ����
 *      lpFileName�������ļ�·����ȱʡΪNULL��ʹ��m_pCfgFile��ֵ
 * @return���ɹ�����TRUE�����򷵻�FALSE
 **/
BOOL CIniFileEdit::RemoveProfileSubKey(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpFileName)
{
    if (NULL == lpFileName && NULL == m_pCfgFile)
        return NULL;

    LPCTSTR fileName;
    if (NULL != lpFileName)
        fileName = lpFileName;
    else
        fileName = m_pCfgFile;

    return ::WritePrivateProfileString(lpAppName, lpKeyName, NULL, fileName);
}
