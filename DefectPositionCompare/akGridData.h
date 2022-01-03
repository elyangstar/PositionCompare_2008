#pragma once

#include <vector>
#include <string>

class CakParser
{
public:
	CakParser(void)
	{
		m_pSrcText = NULL;
	};
	virtual ~CakParser(void){};

	void process(const char* pText, const char* pToken = " \r\n\t,^");
	
	const char* getTokStr(int nIndex);
	bool getTokStr(int nTokIndex, char* pBuf, int nLen);
	
	int getTokNum(){return (int)m_vecTokPos.size();};
	
	int getTokPos(int nIndex){return m_vecTokPos[nIndex];};
	int getTokLen(int nIndex){return m_vecTokLen[nIndex];};


protected:
	const char* m_pSrcText;
	std::vector<int> m_vecTokPos;
	std::vector<int> m_vecTokLen;
	std::string m_strTokBuffer;
};


// union _CellNumData
// {
// 	int nData;
// 	float fData;
// 	double dData;
// };
struct _akCellData 
{
	int nRow, nCol;

	std::string m_strText;

	
};

struct _akCell_Row
{
	std::vector<_akCellData> m_vecGridCellData;
};

class CakTextMatrix
{
public:
	CakTextMatrix(void);
	virtual ~CakTextMatrix(void);


public:
	bool ImportFile(char* pFileName); //���Ͽ��� �д� ��� ����[2018/4/18]
	bool ImportText(char* pText); //�������� �����͸� �ѹ��� �޴� ���.  ����[2018/4/18]

	bool ExportFile(char* pFileName, char* pDevideFlag=",");
	bool ExportFileInterval(char* pFileName, char* pIntervalRef);

	void setDevideFlag(char* pFlag = " \r\n\t,^");
	void setIntervalRef(char* pIntervalRef);
public:
	bool AddRowData(char* pTextData);
	bool printLine(int nRowIndex, char* pBuf, int nLen, char* pDevideFlag=",");
	bool printLineInterval(int nRowIndex, char* pBuf, int nLen);

public:
	void setRowCount(int nNum=10, bool bIncrease = false);
	void setColCount(int nNum=10, bool bIncrease = false);
	int getRowCount(){return m_nRowsNum;};
	int getColCount(){return m_nColsNum;};

	int getRowIndex(char* pTitle);
	int getColIndex(char* pTitle);

public:
	void setItemText(int nRow, int nCol, const char* pText);
	const char* getItemText(int nRow, int nCol);

public:
	virtual void printOut();//������ ���� Trace�� ���
	
protected:
	void makeCellItemArray(); //�����Ϳ� ������ �����ϱ� ���� ��ó�� ����[2017/12/6]


protected:
	std::string m_strDevideFlag;
	std::vector<_akCell_Row> m_vecCellData_Row; //���� ���� ������ ����
	std::vector<_akCellData*> m_vecCellItem; //������ �����ϱ� ���ؼ� NxN������ Cell �ڷ��� ����Ʈ�� ����
	int m_nRowsNum, m_nColsNum;

	int m_nIntervalLength;
	std::vector<int> m_vecIntervalPos;
	
};
