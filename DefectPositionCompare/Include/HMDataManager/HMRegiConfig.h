// HMRegiConfig.h: interface for the CHMRegiConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HMREGICONFIG_H__F8E1E3C1_3652_4862_BC5B_B089CDD610CD__INCLUDED_)
#define AFX_HMREGICONFIG_H__F8E1E3C1_3652_4862_BC5B_B089CDD610CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HMConfigFile.h"
#include "HMRegistery.h"
#include "akFileDB.h"

enum Grouping {File_Mode = 1, Registery_mode = 2};

class AFX_EXT_CLASS CHMRegiConfig
{
public:
	CHMRegiConfig();
	virtual ~CHMRegiConfig();

	BOOL	SetLogWriteMode(BOOL bUse,CString strFilePath);

	BOOL	SetRegiConfig(HKEY hKey, LPCTSTR lpKey, char* szFilename, Grouping Select = File_Mode);

	BOOL	DeleteAllItem();
	BOOL	DeleteValue(LPCTSTR lpValueName);
	BOOL	DeleteValue(LPCTSTR lpValueName, int nIdx);

	// Config File에만 적용.
	BOOL	WriteToFile()					{ return m_ConfigFile.WriteToFile(); }
	void	SetRewriteMode(BOOL bRewrite)	{ m_ConfigFile.SetRewriteMode(bRewrite); }
	BOOL	GetRewriteMode()				{ return m_ConfigFile.GetRewriteMode(); }

	//////////////////////////////////////////////////////////////////////////
	BOOL	SetItemValue(char* szName,  char* szvalue);
	BOOL	SetItemValue(char* szName, int nValue);
	BOOL	SetItemValue(char* szName, unsigned short sValue);
	BOOL	SetItemValue(char* szName, double dValue);

	BOOL	SetItemValue(int nIdx, char* szName, char* szvalue);
	BOOL	SetItemValue(int nIdx, char* szName, int nValue);
	BOOL	SetItemValue(int nIdx, char* szName, unsigned short sValue);
	BOOL	SetItemValue(int nIdx, char* szName, double dValue);

	//////////////////////////////////////////////////////////////////////////
	int		GetItemValue(char* szName, CString& strValue, char* strDefault = NULL);
	int		GetItemValue(char* szName, int& nValue, int nDefault = 0);
	int		GetItemValue(char* szName, unsigned short &nValue, unsigned short sDefault = 0);
	int		GetItemValue(char* szName, double& dValue, double dDefault = 0.0);

	int		GetItemValue(int nIdx, char* szName, CString& strValue, char* strDefault = NULL);
	int		GetItemValue(int nIdx, char* szName, int& nValue, int nDefault = 0);
	int		GetItemValue(int nIdx, char* szName, unsigned short &nValue, unsigned short sDefault = 0);
	int		GetItemValue(int nIdx, char* szName, double& dValue, double dDefault = 0.0);

public:

	Grouping			m_Classification;

protected:

	CHMRegistery		m_Registery;
	//CHMConfigFile		m_ConfigFile;
	CakFileDB			m_ConfigFile;
};

#endif // !defined(AFX_HMREGICONFIG_H__F8E1E3C1_3652_4862_BC5B_B089CDD610CD__INCLUDED_)
