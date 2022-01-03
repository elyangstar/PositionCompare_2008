#include "StdAfx.h"
#include "akGridData.h"


void CakParser::process( const char* pText, const char* pToken /*= " \r\n\t,^"*/ )
{
	//{
		m_vecTokLen.clear();
		m_vecTokPos.clear();
	//}

	m_pSrcText = pText;

	unsigned int i_index;
	unsigned int index;

	unsigned int nTokenLen = (unsigned int)strlen(pToken);
	unsigned int string_length = (unsigned int)strlen(pText);
	unsigned char bitmask[32]={0}; //256가 bit masking을 사용하기 위해서.

	//token 배열에 저장된 문자의 ascii index 위치에 masking을 한다.
	for( i_index=0; i_index<nTokenLen; i_index++)
		bitmask[ pToken[i_index] >> 3] |= (1 << ( pToken[i_index] & 7));


	int nStartPoint=-1;
	for( index=0; index<string_length; index++)
	{
		if( (bitmask[pText[index] >> 3]) & (1 << (pText[index] & 7)) ) //구분자 찾음 태현[2017/12/7]
		{
			if(nStartPoint != -1)
			{
				m_vecTokPos.push_back(nStartPoint);
				m_vecTokLen.push_back(index-nStartPoint);
				nStartPoint = -1;
			}
		}
		else if(nStartPoint < 0) //구분자도 못찾고 시작도 안함
		{
			nStartPoint = index;
		}

	}
	if(nStartPoint >= 0)
	{
		m_vecTokPos.push_back(nStartPoint);
		m_vecTokLen.push_back(string_length-nStartPoint);
	}

};


const char* CakParser::getTokStr( int nIndex )
{
	if(m_vecTokLen.size() <= (DWORD)nIndex) return false;	// 벡터 사이즈 체크

	m_strTokBuffer.clear();
	m_strTokBuffer.append(&m_pSrcText[m_vecTokPos[nIndex]], m_vecTokLen[nIndex]);
	return m_strTokBuffer.c_str();		
}

bool CakParser::getTokStr( int nTokIndex, char* pBuf, int nLen )
{
	if(m_vecTokLen.size() <= (DWORD)nTokIndex) return false;	// 벡터 사이즈 체크
	if(nLen-1 < m_vecTokLen[nTokIndex]) return false; 	// NULL 값 고려

	strncpy(pBuf, &m_pSrcText[m_vecTokPos[nTokIndex]], m_vecTokLen[nTokIndex]);
	pBuf[m_vecTokLen[nTokIndex]] = 0;
	
	return true;	
}

CakTextMatrix::CakTextMatrix(void)
{
	m_nRowsNum = m_nColsNum = 0;

	m_nIntervalLength = 0;
	m_vecIntervalPos.clear();
	
	setDevideFlag();
}

CakTextMatrix::~CakTextMatrix(void)
{
}

bool CakTextMatrix::ImportFile( char* pFileName )
{
	
	FILE* pf = fopen(pFileName, "r");
	if(pf)
	{
		CakParser parser;
		setRowCount(0);
		setColCount(0);


		char buffer[2048]={};
		
		while (fgets(buffer, 2048, pf))
		{
			parser.process(buffer);
			
			setRowCount(1, TRUE);
			if(parser.getTokNum() > getColCount()) setColCount(parser.getTokNum());

			int nTokenNum = parser.getTokNum();
			int nRowIndex = getRowCount()-1;
			for(int i=0; i<nTokenNum; i++)
			{
				setItemText(nRowIndex, i, parser.getTokStr(i));
			}
		}
		
		fclose(pf);

		return true;
	}

	return false;
}

bool CakTextMatrix::ImportText( char* pText )
{
	if(pText == NULL) return false;
	CakParser parserLine;
	CakParser parserTok;
	parserLine.process(pText, "\n");

	char* pStrLineData;
	char* pStrLineTock;
	int nLineNum = parserLine.getTokNum();
	setRowCount(nLineNum);
	for(int i=0; i<nLineNum; i++)
	{
		pStrLineData = (char*)parserLine.getTokStr(i);
		
		parserTok.process(pStrLineData, m_strDevideFlag.c_str());
		int nTockNum = parserTok.getTokNum();
		setColCount(nTockNum);
		for(int j=0; j<nTockNum; j++)
		{
			pStrLineTock = (char*)parserTok.getTokStr(j);
			setItemText(i,j, pStrLineTock);
		}
	}

	return true;
}


bool CakTextMatrix::AddRowData( char* pTextData )
{
	if(pTextData == NULL) return false;
	
	CakParser parserTok;
	parserTok.process(pTextData, m_strDevideFlag.c_str());
	
	int nTockNum = parserTok.getTokNum();
	
	setColCount(nTockNum);
	setRowCount(1, true);

	int nRowIndex = getRowCount();
	char* pStrTok;
	
	for(int j=0; j<nTockNum; j++)
	{
		pStrTok = (char*)parserTok.getTokStr(j);
		setItemText(nRowIndex,j, pStrTok);
	}

	return true;
}



void CakTextMatrix::setDevideFlag( char* pFlag /*= " \r\n\t,"*/ )
{
	m_strDevideFlag = pFlag;

	
}

void CakTextMatrix::setRowCount( int nNum/*=10*/, bool bIncrease /*= false*/ )
{
	int nIncreaseCount = 0;
	
	if(bIncrease) nIncreaseCount = nNum;
	else nIncreaseCount = nNum - m_nRowsNum;

	if(nIncreaseCount == 0) 
	{
		return ;
	}
	else if(nIncreaseCount > 0) //증가
	{
		for(int i=0; i<nIncreaseCount; i++)
		{
			m_vecCellData_Row.push_back(_akCell_Row());
		}
		setColCount(m_nColsNum);
	}
	else if(nIncreaseCount < 0) //감소
	{
		m_vecCellData_Row.erase(m_vecCellData_Row.end() + nIncreaseCount, m_vecCellData_Row.end());
	}

	m_nRowsNum += nIncreaseCount;
	makeCellItemArray();
}

void CakTextMatrix::setColCount( int nNum/*=10*/, bool bIncrease /*= false*/ )
{
	if(bIncrease) m_nColsNum += nNum;
	else m_nColsNum = nNum;

	int nSize = (int)m_vecCellData_Row.size(); 
	for(int i=0; i<nSize; i++)
	{
		std::vector<_akCellData>* pVecGridCellData = &m_vecCellData_Row[i].m_vecGridCellData;

		int nIncreaseCount = 0;

		if(bIncrease) nIncreaseCount = nNum;
		else nIncreaseCount = m_nColsNum - (int)pVecGridCellData->size();

		

		if(nIncreaseCount == 0)
		{
			continue ;
		}
		else if(nIncreaseCount > 0) //증가
		{
			for(int i=0; i<nIncreaseCount; i++)
			{
				 pVecGridCellData->push_back(_akCellData());
			}
		}
		else if(nIncreaseCount < 0) //감소
		{
			pVecGridCellData->erase(pVecGridCellData->end() + nIncreaseCount, pVecGridCellData->end());
		}

	}

	makeCellItemArray();

	
	

	return;
}

void CakTextMatrix::printOut()
{
	int nRowNum = getRowCount();
	int nColNum = getColCount();

	for(int y=0; y<nRowNum; y++)
	{
		for(int x=0; x<nColNum; x++)
		{
			//TRACE("%s", getItemText(x,y));
			TRACE("(%02d,%02d)%s", x,y,getItemText(y,x));
			if(x < nColNum-1) TRACE("\t");
		}
		TRACE("\n");
	}
}

const char* CakTextMatrix::getItemText( int nRow, int nCol )
{
	return m_vecCellItem[nRow*m_nColsNum + nCol]->m_strText.c_str();
}

void CakTextMatrix::setItemText( int nRow, int nCol,  const char* pText )
{
	if(pText != NULL)
		m_vecCellItem[nRow*m_nColsNum + nCol]->m_strText = pText;
}

void CakTextMatrix::makeCellItemArray()
{
	m_vecCellItem.clear();

	int nRowNum = getRowCount();
	int nColNum = getColCount();

	for(int y=0; y<nRowNum; y++)
	{
		for(int x=0; x<nColNum; x++)
		{
			m_vecCellItem.push_back(&m_vecCellData_Row[y].m_vecGridCellData[x]);
		}
	}
}

int CakTextMatrix::getRowIndex( char* pTitle )
{
	for(int i=0; i<m_nRowsNum; i++)
	{
		if(m_vecCellItem[i*m_nColsNum + 0]->m_strText.compare(pTitle))
		{
			return i;
		}
	}

	return -1;
}
int CakTextMatrix::getColIndex( char* pTitle )
{
	for(int i=0; i<m_nColsNum; i++)
	{
		if(m_vecCellItem[0*m_nColsNum + i]->m_strText.compare(pTitle))
		{
			return i;
		}
	}

	return -1;
}

bool CakTextMatrix::ExportFileInterval( char* pFileName, char* pIntervalRef )
{
	FILE* pf = fopen(pFileName, "w");
	if(pf)
	{
		CakParser paserInterval;
		paserInterval.process(pIntervalRef, " ");

		const int nBufSize = 2048;
		char buffer[nBufSize];
		int nStrLen, nWritePoint;
		const char* pStr;

		int nRowNum = getRowCount();
		int nColNum = getColCount();

		for(int y=0; y<nRowNum; y++)
		{
			memset(buffer, ' ', sizeof(char)*nBufSize);
			for(int x=0; x<nColNum; x++)
			{
				pStr = getItemText(y,x);
				nStrLen = (int)strlen(pStr);
				nWritePoint = paserInterval.getTokPos(x);
				memcpy(&buffer[nWritePoint], pStr, sizeof(char)*nStrLen);
				
				if(nWritePoint > 0)
				{
					buffer[nWritePoint-1] = ' '; //바로 직전에 공백으로 표시
				}
			}
			buffer[strlen(pIntervalRef)] = 0;
			fprintf(pf, "%s", buffer);
			if(y < nRowNum-1) fprintf(pf, "\n");
		}

		fclose(pf);
		return true;
	}

	
	return false;
}

bool CakTextMatrix::ExportFile( char* pFileName, char* pDevideFlag/*=","*/ )
{
	//한줄을 메모리에 적고 최종적으로 파일로 쓰는게 더 빠르겠지?? 태현[2017/12/7]
	FILE* pf = fopen(pFileName, "w");
	if(pf)
	{
		char buffer[2048]={};

		int nRowNum = getRowCount();
		int nColNum = getColCount();

		for(int y=0; y<nRowNum; y++)
		{
			memset(buffer, 0, sizeof(char)*2048);
			for(int x=0; x<nColNum; x++)
			{
				strcat(buffer, getItemText(y,x));
				if(x < nColNum-1) strcat(buffer, pDevideFlag);
			}
			
			if(y < nRowNum-1) strcat(buffer, "\n");
			fprintf(pf, "%s", buffer);
		}

		fclose(pf);
		return true;
	}

	//한줄한줄 파일에 쓰는 방식 태현[2017/12/7]
	/*
	FILE* pf = fopen(pFileName, "w");
	if(pf)
	{
		int nRowNum = getRowCount();
		int nColNum = getColCount();

		for(int y=0; y<nRowNum; y++)
		{
			for(int x=0; x<nColNum; x++)
			{
				fprintf(pf, "%s", getItemText(y,x));
				if(x < nColNum-1) fprintf(pf, "%s", pDevideFlag);
			}
			if(y < nRowNum-1) fprintf(pf, "\n");
		}

		fclose(pf);
		return true;
	}
	*/ 

	return false;
}
bool CakTextMatrix::printLine( int nRowIndex, char* pBuf, int nLen, char* pDevideFlag/*=","*/ )
{
	int nRowNum = getRowCount();
	int nColNum = getColCount();


	if(nRowIndex < nRowNum)
	{
		memset(pBuf, 0, sizeof(char)*nLen);

		for(int x=0; x<nColNum; x++)
		{
			strcat(pBuf, getItemText(nRowIndex,x));
			if(x < nColNum-1) strcat(pBuf, pDevideFlag);
		}

		return true;
	}


	return false;
}


bool CakTextMatrix::printLineInterval( int nRowIndex, char* pBuf, int nLen )
{
	int nRowNum = getRowCount();

	if(nRowIndex < nRowNum && m_nIntervalLength != 0)
	{
		int nColNum = getColCount();

		int nStrLen, nWritePoint;
		const char* pStr;
		
		memset(pBuf, ' ', sizeof(char)*nLen);
		for(int x=0; x<nColNum; x++)
		{
			pStr = getItemText(nRowIndex,x);
			nStrLen = (int)strlen(pStr);
			nWritePoint = m_vecIntervalPos[x];
			memcpy(&pBuf[nWritePoint], pStr, sizeof(char)*nStrLen);

			if(nWritePoint > 0)
			{
				pBuf[nWritePoint-1] = ' '; //바로 직전에 공백으로 표시
			}
		}
		pBuf[m_nIntervalLength] = 0;


		return true;
	}
	
	return false;
}

void CakTextMatrix::setIntervalRef( char* pIntervalRef )
{
	m_nIntervalLength = 0;
	m_vecIntervalPos.clear();

	if(pIntervalRef == NULL) return;
	
	CakParser paserInterval;
	paserInterval.process(pIntervalRef, " ");

	int nNum = paserInterval.getTokNum();
	for(int i=0; i<nNum; i++)
	{
		m_vecIntervalPos.push_back(paserInterval.getTokPos(i));
	}

	m_nIntervalLength = (int)strlen(pIntervalRef);

}

