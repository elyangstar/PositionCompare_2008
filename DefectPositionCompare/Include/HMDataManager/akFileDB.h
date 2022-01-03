#pragma once

#include <map>
#include <vector>

//hash_map을 사용하는 경우
//1. 많은 자료를 저장하고, 검색 속도가 빨라야 한다.
//2. 너무 빈번하게 자료를 삽입, 삭제 하지 않는다.
#define ITEMSEP "_" //구분자

#define mapIDVal std::map<CString, CString>
#define mapIDValIt mapIDVal::iterator



class AFX_EXT_CLASS CakFileDB
{
public:
	CakFileDB(void);
	~CakFileDB(void);

	bool SetFileName(char* filename);
	bool WriteToFile(char* filename = NULL);
	void clear();
	void RemoveAllItem(){clear();};

	void setWriteEnter(); //동기화 객체 시작
	void setWriteRelease();  //동기화 객체 중지

	void	SetRewriteMode(BOOL bRewrite)	{ m_bRewrite = bRewrite; }
	BOOL	GetRewriteMode()				{ return m_bRewrite; }

	//단일 데이터
	void SetItemValue(char* strKey, char* strVal);
	void SetItemValue(char* strKey, int nVal);
	void SetItemValue(char* strKey, float fVal);
	void SetItemValue(char* strKey, double dVal);
	void SetItemValue(char* strKey, long dVal);

	void GetItemValue(char* strKey, CString* strVal, char* strDefaultVal = "");
	void GetItemValue(char* strKey, char* strVal, char* strDefaultVal = "");
	void GetItemValue(char* strKey, unsigned short* nVal, int nDefaultVal = 0);
	void GetItemValue(char* strKey, int* nVal, int nDefaultVal = 0);
	void GetItemValue(char* strKey, float* fVal, float fDefaultVal = 0);
	void GetItemValue(char* strKey, double* dVal, double dDefaultVal = 0);
	void GetItemValue(char* strKey, long* dVal, long dDefaultVal = 0);

	char* getItemPoint(char* strKey);

	//다중 데이터 관리
	void setItemClear(char* strKey);
	int  getItemNum(char* strKey);

	void SetItemValue(int nIndex, char* strKey, char* strVal);
	void SetItemValue(int nIndex, char* strKey, int nVal);
	void SetItemValue(int nIndex, char* strKey, float fVal);
	void SetItemValue(int nIndex, char* strKey, double dVal);

	void GetItemValue(int nIndex, char* strKey, CString* strVal, char* strDefaultVal = "");
	void GetItemValue(int nIndex, char* strKey, char* strVal, char* strDefaultVal = "");
	void GetItemValue(int nIndex, char* strKey, unsigned short* nVal, int nDefaultVal = 0);
	void GetItemValue(int nIndex, char* strKey, int* nVal, int nDefaultVal = 0);
	void GetItemValue(int nIndex, char* strKey, float* fVal, float fDefaultVal = 0);
	void GetItemValue(int nIndex, char* strKey, double* dVal, double dDefaultVal = 0);

	char* getItemPoint(int nIndex, char* strKey);




	BOOL deleteItem(char* strKey); //
	BOOL RemoveItem(char* strKey){return deleteItem(strKey);};
	int deleteItem(int nIndex); //
	BOOL	RemoveItem(int nIdx, char* szName);


protected:
	mapIDVal m_mapData;
	std::vector<mapIDValIt> m_vecOrder;

	CRITICAL_SECTION m_csAkFileDB;
	CString m_strOpenFileName;

	BOOL				m_bRewrite;
};
