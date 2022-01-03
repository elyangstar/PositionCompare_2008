// HMConfigFile.h: interface for the CHMConfigFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HMCONFIGFILE_H__9BD76395_D4EB_4173_A317_C040E5CF99AA__INCLUDED_)
#define AFX_HMCONFIGFILE_H__9BD76395_D4EB_4173_A317_C040E5CF99AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_EXT_CLASS CHMConfigItem : public CObject
{
public:
	CString s_strName;
	CString s_strValue;

	CHMConfigItem()
	{
		Reset();
	}

	void Reset()
	{
		s_strName.Empty();
		s_strValue.Empty();
	}

	void SetItem(CString& strName, CString& strValue)
	{
		s_strName = strName;
		s_strValue = strValue;
	}

	void SetItem(CString& strItem)
	{
		if (strItem.IsEmpty())
			return;

		int nTemp1 = 0, nTemp2 = 0, nTemp3 = 0;

		nTemp1 = strItem.Find('=', 0);
		nTemp2 = strItem.Find('`', 0);
		nTemp3 = strItem.Find('`', nTemp2 + 1);
		if (nTemp1 == -1 || nTemp2 == -1 || nTemp3 == -1)
		{
			s_strName = strItem;

			s_strName.TrimRight("\r");
			s_strName.TrimRight("\n");

			return;
		}

		s_strName = strItem.Left(nTemp1);
		s_strName.TrimLeft(" ");
		s_strName.TrimRight(" ");
		s_strName.TrimRight("\r");
		s_strName.TrimRight("\n");

		s_strValue.Empty();
		s_strValue = strItem.Mid(nTemp2 + 1, nTemp3 - nTemp2 - 1);
		s_strValue.TrimLeft(" ");
		s_strValue.TrimRight(" ");
		s_strValue.TrimRight("\r");
		s_strValue.TrimRight("\n");
	}
};

class AFX_EXT_CLASS CHMConfigFile  
{
public:
	CHMConfigFile();
	CHMConfigFile(char* szFilename);	// 상대경로
	virtual ~CHMConfigFile();

	BOOL	SetFileName(char* szFilename);
	BOOL	WriteToFile();
	BOOL	WriteToFileRMM();

	void	SetRewriteMode(BOOL bRewrite)	{ m_bRewrite = bRewrite; }
	BOOL	GetRewriteMode()				{ return m_bRewrite; }

	//////////////////////////////////////////////////////////////////////////
	int		GetItemValue(char* szName, CString& strValue, char* strDefault = NULL);
	int		GetItemValue(char* szName, int& nValue, int nDefault = 0);
	int		GetItemValue(char* szName, unsigned short &nValue, unsigned short sDefault = 0);
	int		GetItemValue(char* szName, double& dValue, double dDefault = 0.0);

	int		GetItemValue(int nIdx, char* szName, CString& strValue, char* strDefault = NULL);
	int		GetItemValue(int nIdx, char* szName, int& nValue, int nDefault = 0);
	int		GetItemValue(int nIdx, char* szName, unsigned short &nValue, unsigned short sDefault = 0);
	int		GetItemValue(int nIdx, char* szName, double& dValue, double dDefault = 0.0);

	//////////////////////////////////////////////////////////////////////////
	BOOL	SetItemValue(char* szName, char* szvalue);
	BOOL	SetParamItemValue(char* szName, char* szvalue);
	BOOL	SetItemValue(char* szName, int& nValue);
	BOOL	SetItemValue(char* szName, unsigned short &nValue);
	BOOL	SetItemValue(char* szName, double& dValue);

	BOOL	SetItemValue(int nIdx, char* szName, char* szvalue);
	BOOL	SetItemValue(int nIdx, char* szName, int& nValue);
	BOOL	SetItemValue(int nIdx, char* szName, unsigned short &nValue);
	BOOL	SetItemValue(int nIdx, char* szName, double& dValue);
	
	void	RemoveAllItem();
	BOOL	RemoveItem(char* szName);
	BOOL	RemoveItem(int nIdx, char* szName);

	// OhByungGil  Modify -> LogFile Write
	void	SetLogMode(BOOL bMode)					{	m_bLogMode = bMode;	}
	BOOL	GetLogMode()							{	return m_bLogMode;	}
	void	SetLogFilePath(CString strLogFilePath)	{	m_strLogFileName = strLogFilePath;}
	CString GetLogFilePath()						{	return m_strLogFileName;	}

	void	WriteLog( char* szName, char* szvalue );
	void	WriteLog( char* szName, int& nValue );
	void	WriteLog( char* szName, unsigned short &nValue );
	void	WriteLog( char* szName, double& dValue );
protected:
	BOOL	WriteToLogFile(CString& strContents);

private:
	CString				m_strFileName;
	CObList				m_ItemList;
	int					m_nItemCount;
	BOOL				m_bRewrite;

	CString				m_strLogFileName;	// OhByungGil 100531
	BOOL				m_bLogMode;

	CRITICAL_SECTION	m_cs;
};

#endif // !defined(AFX_HMCONFIGFILE_H__9BD76395_D4EB_4173_A317_C040E5CF99AA__INCLUDED_)
