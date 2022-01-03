
// DefectPositionCompareDlg.h : ��� ����
//

#pragma once
#include "GridCtrl.h"
#include "akGridData.h"
#include <map>
#include <fstream>
#define GRID_MAX_COUNT_ROW 20000

typedef struct _DefectInfo {
	int nIndex;
	int nX;
	int nY;
	int nMatch;

	_DefectInfo()
	{
		Reset();
	}

	void Reset()
	{
		nIndex = 0;
		nX = 0;
		nY = 0;
		nMatch = 0;
	}
} DEFECTINFO, *PDEFECTINFO;

typedef std::multimap<int, DEFECTINFO>			  DEFECTINFO_CONTAINER;
typedef std::multimap<int, DEFECTINFO>::iterator  DEFECTINFO_CONTAINER_IT;


// CDefectPositionCompareDlg ��ȭ ����
class CDefectPositionCompareDlg : public CDialog
{
// �����Դϴ�.
public:
	CDefectPositionCompareDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DEFECTPOSITIONCOMPARE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	DEFECTINFO_CONTAINER m_mapDefectInfo1;
	DEFECTINFO_CONTAINER m_mapDefectInfo2;


public:
	CGridCtrl m_GridDefectPosData1;
	int m_nDistance;
	CString m_strRstFile1;
	CString m_strRstFile2;
	CString m_strCompDirectory;


	afx_msg void OnBnClickedBtnFind1();
	afx_msg void OnBnClickedBtnFind2();
	afx_msg void OnBnClickedBtnFind3();
	afx_msg void OnBnClickedBtnCompare();

	BOOL CompareDefectPosition();

	void FileCompare();
	BOOL ParsingAOIResultFile(CString strFileFath, DEFECTINFO_CONTAINER &mapDefectInfo);

	BOOL GetDefectDataFromGrid(int nIndex);
	void DefectPositionCompare();

	void SetInitGridCoordiDefection1();
	void SetInitGridCoordiDefection2();

	CGridCtrl m_GridDefectPosData2;
	BOOL m_bNoneFileCompare;
	afx_msg void OnBnClickedNoneFileCompare();
	BOOL m_bUseUnitUm;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
