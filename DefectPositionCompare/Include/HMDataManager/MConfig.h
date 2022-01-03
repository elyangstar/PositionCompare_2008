// MConfig.h: interface for the CMConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MCONFIG_H__7E45994E_D3B2_4D62_97B3_A072CA6C9594__INCLUDED_)
#define AFX_MCONFIG_H__7E45994E_D3B2_4D62_97B3_A072CA6C9594__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>

typedef struct _tag_MConfig_Config_Variables_
{
	CString	strVariableName;
	CString strVariable;
} _MCONFIG_ONE_VARIABLE_;

typedef std::vector <_MCONFIG_ONE_VARIABLE_>  _MCONFIG_VARIABLE_CONTAINER_;

typedef struct _tag_MConfig_Config_Section_
{
	CString						 strSectionName;
	_MCONFIG_VARIABLE_CONTAINER_ VariableContainer;
} _MCONFIG_ONE_SECTION_;

typedef std::vector <_MCONFIG_ONE_SECTION_>  _MCONFIG_SECTION_CONTAINER_;

class AFX_EXT_CLASS CMConfig  
{
public:
	CMConfig();
	virtual ~CMConfig();

public: 
	CMConfig &operator+= (CMConfig &rhs);
	_MCONFIG_SECTION_CONTAINER_ &GetSectionContainer(void) { return m_ConfigContents ;}

public:
	BOOL Read(CString strFilePath);
	CString &GetFilePath(void) 
	{
		return m_strFilePath; 
	}

public:
	BOOL GetItemValue(CString strName, CString& strValue, CString strDefault = _T(""));
	BOOL GetItemValue(CString strName, int& nValue, int nDefault=0);
	BOOL GetItemValue(CString strName, unsigned short& nValue, unsigned short nDefault=0);
	BOOL GetItemValue(CString strName, float &fValue, float fDefault =0);
	BOOL GetItemValue(CString strName, double& dValue, double dDefault = 0);

	BOOL SetItemValue(CString strName, CString strValue);
	BOOL SetItemValue(CString strName, int nValue);
	BOOL SetItemValue(CString strName, unsigned short nValue);
	BOOL SetItemValue(CString strName, float fValue);
	BOOL SetItemValue(CString strName, double dValue);

public:
	BOOL GetItemValue(CString strSection, CString strName, CString& strValue, CString strDefault= _T(""));
	BOOL GetItemValue(CString strSection, CString strName, int& nValue, int nDefault=0);
	BOOL GetItemValue(CString strSection, CString strName, unsigned short& nValue, unsigned short nDefault=0);
	BOOL GetItemValue(CString strSection, CString strName, float &fValue, float fDefault=0);
	BOOL GetItemValue(CString strSection, CString strName, double& dValue, double dDefault=0);

	BOOL SetItemValue(CString strSection, CString strName, CString strValue);
	BOOL SetItemValue(CString strSection, CString strName, int nValue);
	BOOL SetItemValue(CString strSection, CString strName, unsigned short nValue);
	BOOL SetItemValue(CString strSection, CString strName, float fValue);
	BOOL SetItemValue(CString strSection, CString strName, double dValue);

public:
	BOOL MakeWriteString(CString &strContent);
	BOOL Write(CString strFilePath, BOOL bBackup=TRUE);

protected:
	_MCONFIG_ONE_SECTION_ *FindSection(CString strSectionName);
	_MCONFIG_ONE_VARIABLE_ *FindVariable(CString &strSectionName, CString &strVariableName);
	_MCONFIG_ONE_VARIABLE_ *FindVariable(CString strVariableName);
	void Backup(void);


protected:
	BOOL ParseStringToLineArray(char *pBuffer, int nLength, CStringArray &arrString);
	BOOL ParseLinesToData(CStringArray &arrString);

private:
	CString							m_strFilePath;
	_MCONFIG_SECTION_CONTAINER_		m_ConfigContents;	

};

#endif // !defined(AFX_MCONFIG_H__7E45994E_D3B2_4D62_97B3_A072CA6C9594__INCLUDED_)
