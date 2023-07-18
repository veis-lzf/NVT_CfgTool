#include "pch.h"
#include "CSplitStr.h"

CSplitStr::CSplitStr()
{
	SetData(_T(""));
	SetSequenceAsOne(TRUE);
	SetSplitFlag(_T(","));
}

CSplitStr::~CSplitStr()
{
}

void CSplitStr::SetData(CString sData)
{
	m_sData = sData;
	m_sData.TrimLeft();
	m_sData.TrimRight();
}

CString CSplitStr::GetData()
{
	return m_sData;
}

void CSplitStr::GetSplitStrArray(CStringArray& array)
{
	CString sData = GetData();
	CString sSplitFlag = GetSplitFlag();
	if (sData.Right(1) != sSplitFlag)
	{
		sData += sSplitFlag;
	}
	CString sTemp;
	int pos = -1;
	while ((pos = sData.Find(sSplitFlag, 0)) != -1)
	{
		sTemp = sData.Left(pos);
		if (!GetSequenceAsOne())
		{
			array.Add(sTemp);
		}
		else
		{
			if (!sTemp.IsEmpty() && sTemp != _T("")) // 连续的分隔符视为单个处理
			{
				array.Add(sTemp);
			}
		}
		sData = sData.Right(sData.GetLength() - pos - 1);

		if(GetSequenceAsOne())
			sData = sData.TrimLeft(sSplitFlag);
	}
}
