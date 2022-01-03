// HMRegistery.h: interface for the CRegist class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HMREGISTERY_H__BFF1B539_B69C_46E1_8575_A595F5AC4D29__INCLUDED_)
#define AFX_HMREGISTERY_H__BFF1B539_B69C_46E1_8575_A595F5AC4D29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define SHLM	HKEY_LOCAL_MACHINE
#define SHCU	HKEY_CURRENT_USER
#define SHCR	HKEY_CLASSES_ROOT

class AFX_EXT_CLASS CHMRegistery
{
public:
	//////////////////////////////////////////////////////////////////////////
	// 임의 사용 가능 함수.
	BOOL	WriteString(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, LPCTSTR lpData);
	BOOL	WriteDouble(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, double dData);
	BOOL	WriteInt(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, int nData);
	BOOL	ReadString(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, LPTSTR lpRet, DWORD nSize);
	BOOL	ReadDouble(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, double dDefault, double& dValue);
	BOOL	ReadInt(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, int nDefault, int& nValue);

	BOOL	WriteString(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, int nIdx, LPCTSTR lpData);
	BOOL	WriteDouble(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, int nIdx, double dData);
	BOOL	WriteInt(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, int nIdx, UINT nData);
	BOOL	ReadString(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, int nIdx, LPTSTR lpRet, DWORD nSize);
	BOOL	ReadDouble(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, int nIdx, double dDefault, double& dValue);
	BOOL	ReadInt(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, int nIdx, int nDefault, int& nValue);

	BOOL	DeleteKey(HKEY hKey, LPCTSTR lpKey);
	BOOL	DeleteValue(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValueName);
	BOOL	DeleteValue(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValueName, int nIdx);

	//////////////////////////////////////////////////////////////////////////
	// Setting 값 적용 함수.
	void	SetKey(HKEY hKey, LPCTSTR lpKey)		{ m_hKey = hKey;	m_strKey = lpKey; }

	BOOL	WriteString(LPCTSTR lpValue, LPCTSTR lpData);
	BOOL	WriteDouble(LPCTSTR lpValue, double dData);
	BOOL	WriteInt(LPCTSTR lpValue, UINT nData);
	BOOL	ReadString(LPCTSTR lpValue, LPTSTR lpRet, DWORD nSize);
	BOOL	ReadDouble(LPCTSTR lpValue, double dDefault, double& dValue);
	BOOL	ReadInt(LPCTSTR lpValue, int nDefault, int& nValue );

	BOOL	WriteString(LPCTSTR lpValue, int nIdx, LPCTSTR lpData);
	BOOL	WriteDouble(LPCTSTR lpValue, int nIdx, double dData);
	BOOL	WriteInt(LPCTSTR lpValue, int nIdx, UINT nData);
	BOOL	ReadString(LPCTSTR lpValue, int nIdx, LPTSTR lpRet, DWORD nSize);
	BOOL	ReadDouble(LPCTSTR lpValue, int nIdx, double dDefault, double& dValue);
	BOOL	ReadInt(LPCTSTR lpValue, int nIdx, int nDefault, int& nValue);

	BOOL	DeleteKey();
	BOOL	DeleteValue(LPCTSTR lpValueName);
	BOOL	DeleteValue(LPCTSTR lpValueName, int nIdx);

	CHMRegistery();
	virtual ~CHMRegistery();

protected:
	HKEY		m_hKey;
	CString		m_strKey;
};

#endif // !defined(AFX_HMREGISTERY_H__BFF1B539_B69C_46E1_8575_A595F5AC4D29__INCLUDED_)
