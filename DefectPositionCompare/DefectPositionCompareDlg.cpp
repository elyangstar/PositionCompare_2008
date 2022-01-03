
// DefectPositionCompareDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "DefectPositionCompare.h"
#include "DefectPositionCompareDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDefectPositionCompareDlg ��ȭ ����




CDefectPositionCompareDlg::CDefectPositionCompareDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDefectPositionCompareDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nDistance = 0;
	m_strRstFile1 = "";
	m_strRstFile2 = "";
	m_strCompDirectory = "";
	m_bNoneFileCompare = TRUE;
	m_bUseUnitUm = TRUE;
}

void CDefectPositionCompareDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DEFECT_POS1, m_GridDefectPosData1);
	DDX_Text(pDX, IDC_EDIT_DISTANCE, m_nDistance);
	DDV_MinMaxInt(pDX, m_nDistance, 1, 1000000);
	DDX_Text(pDX, IDC_EDIT_RSTFILE1_PATH, m_strRstFile1);
	DDX_Text(pDX, IDC_EDIT_RSTFILE2_PATH, m_strRstFile2);
	DDX_Text(pDX, IDC_EDIT_COMPFILE_PATH, m_strCompDirectory);
	DDX_Control(pDX, IDC_DEFECT_POS2, m_GridDefectPosData2);
	DDX_Check(pDX, IDC_NONE_FILE_COMPARE, m_bNoneFileCompare);
	DDX_Check(pDX, IDC_NONE_FILE_COMPARE2, m_bUseUnitUm);
}

BEGIN_MESSAGE_MAP(CDefectPositionCompareDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_FIND1, &CDefectPositionCompareDlg::OnBnClickedBtnFind1)
	ON_BN_CLICKED(IDC_BTN_FIND2, &CDefectPositionCompareDlg::OnBnClickedBtnFind2)
	ON_BN_CLICKED(IDC_BTN_FIND3, &CDefectPositionCompareDlg::OnBnClickedBtnFind3)
	ON_BN_CLICKED(ID_BTN_COMPARE, &CDefectPositionCompareDlg::OnBnClickedBtnCompare)
	ON_BN_CLICKED(IDC_NONE_FILE_COMPARE, &CDefectPositionCompareDlg::OnBnClickedNoneFileCompare)
	ON_BN_CLICKED(IDC_BUTTON1, &CDefectPositionCompareDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDefectPositionCompareDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDefectPositionCompareDlg �޽��� ó����

BOOL CDefectPositionCompareDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_mapDefectInfo1.clear();
	m_mapDefectInfo2.clear();
	m_nDistance = 2000;

	m_bNoneFileCompare = TRUE;
	m_bUseUnitUm = TRUE;

	SetInitGridCoordiDefection1();
	SetInitGridCoordiDefection2();
	UpdateData(FALSE);

	if (m_bNoneFileCompare == FALSE)
	{	
		GetDlgItem( IDC_EDIT_RSTFILE1_PATH )->EnableWindow(TRUE);
		GetDlgItem( IDC_BTN_FIND1 )->EnableWindow(TRUE);
		GetDlgItem( IDC_EDIT_RSTFILE2_PATH )->EnableWindow(TRUE);
		GetDlgItem( IDC_BTN_FIND2)->EnableWindow(TRUE);
	}
	else
	{	
		GetDlgItem( IDC_EDIT_RSTFILE1_PATH )->EnableWindow(FALSE);
		GetDlgItem( IDC_BTN_FIND1 )->EnableWindow(FALSE);
		GetDlgItem( IDC_EDIT_RSTFILE2_PATH )->EnableWindow(FALSE);
		GetDlgItem( IDC_BTN_FIND2)->EnableWindow(FALSE);
	}

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CDefectPositionCompareDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CDefectPositionCompareDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDefectPositionCompareDlg::OnBnClickedBtnFind1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//char currentDir[ 256 ]; // ������ ���
	//GetCurrentDirectory( NAME_MAX_SIZE, currentDir );
	//strcat( currentDir, "\Data\" );

	CFileDialog	fieldlg( TRUE, "*.dat", "D:\\*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Text file (*.*)|*.*|", NULL );
	if(IDCANCEL == fieldlg.DoModal())
		return;

	m_strRstFile1 = fieldlg.GetPathName();
	UpdateData(FALSE);

	m_mapDefectInfo1.clear();
}

void CDefectPositionCompareDlg::OnBnClickedBtnFind2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CFileDialog	filedlg( TRUE, "*.ans", "C:\\AOIServer\\NFS\\RAW\\Stack\\*.ans", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Text file (*.ans)|*.ans|", NULL );
	CFileDialog	filedlg( TRUE, "*.dat", "C:\\*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Text file (*.*)|*.*|", NULL );
	if(IDCANCEL == filedlg.DoModal())
		return;

	m_strRstFile2 = filedlg.GetPathName();
	UpdateData(FALSE);
	m_mapDefectInfo2.clear();
}

void CDefectPositionCompareDlg::OnBnClickedBtnFind3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//���丮�� ������ �� �ִ� ���̾�αװ� ��µȴ�.
	char sBuffer[MAX_PATH];
	LPITEMIDLIST pDirList;
	BROWSEINFO browseInfo;

	browseInfo.hwndOwner = m_hWnd; 
	browseInfo.pidlRoot = NULL;
	browseInfo.lpszTitle = "Input Compare Result File Save Directory.";
	browseInfo.pszDisplayName = sBuffer;
	browseInfo.ulFlags = BIF_RETURNONLYFSDIRS;
	browseInfo.lpfn = NULL;
	browseInfo.lParam = 0;


	// ���丮 ���� ���̾�α� ���
	pDirList = SHBrowseForFolder(&browseInfo);

	if( pDirList != NULL )
	{
		//����ڰ� ������ ��θ� buffer�� ����
		SHGetPathFromIDList(pDirList, sBuffer);
		m_strCompDirectory = sBuffer;

		UpdateData(FALSE);
	}
}

void CDefectPositionCompareDlg::OnBnClickedBtnCompare()
{
	UpdateData(TRUE);
	m_mapDefectInfo1.clear();
	m_mapDefectInfo2.clear();

	if (m_bNoneFileCompare == FALSE)
		FileCompare();
	else
		DefectPositionCompare();
}
void CDefectPositionCompareDlg::SetInitGridCoordiDefection1()
{
	CGridCtrl* pGrid = &m_GridDefectPosData1;
	const int nRowNum = GRID_MAX_COUNT_ROW;
	const int nColNum = 3;

	CString strTemp = "";
	pGrid->DeleteAllItems();
	pGrid->GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(242,242,242));
	pGrid->SetFixedBkColor(RGB(215,228,188));
	pGrid->SetFixedTextColor(RGB(0,0,0));
	pGrid->SetGridLineColor(RGB(80,80,80));
	pGrid->SetGridLines(GVL_BOTH);

	pGrid->SetColumnCount(nColNum);
	pGrid->SetRowCount(nRowNum+1);
	pGrid->SetFixedRowCount(1);
	pGrid->SetFixedColumnCount(1);
	pGrid->SetColumnWidth(0,35);
	pGrid->ExpandColumnsToFit();

	pGrid->SetEditable(TRUE);
	pGrid->EnableSelection(TRUE);

	//header
	{
		GV_ITEM Item;
		Item.mask = GVIF_TEXT;

		Item.row = 0;
		Item.col = 0;
		Item.strText = "Index";
		pGrid->SetItem(&Item);
		Item.col = 1;
		Item.strText = "Defect Pos X";
		pGrid->SetItem(&Item);
		Item.col = 2;
		Item.strText = "Defect Pos Y";
		pGrid->SetItem(&Item);
	}

	for (int i = 0 ; i<GRID_MAX_COUNT_ROW ; i++)
	{
		GV_ITEM Item;
		Item.mask = GVIF_TEXT;
		Item.col = 0;
		Item.row = i+1;
		strTemp.Format("%d",i+1);
		Item.strText = strTemp;
		pGrid->SetItem(&Item);
	}

	pGrid->Invalidate(FALSE);
}

void CDefectPositionCompareDlg::SetInitGridCoordiDefection2()
{
	CGridCtrl* pGrid = &m_GridDefectPosData2;
	const int nRowNum = GRID_MAX_COUNT_ROW;
	const int nColNum = 3;

	CString strTemp = "";
	pGrid->DeleteAllItems();
	pGrid->GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(242,242,242));
	pGrid->SetFixedBkColor(RGB(215,228,188));
	pGrid->SetFixedTextColor(RGB(0,0,0));
	pGrid->SetGridLineColor(RGB(80,80,80));
	pGrid->SetGridLines(GVL_BOTH);

	pGrid->SetColumnCount(nColNum);
	pGrid->SetRowCount(nRowNum+1);
	pGrid->SetFixedRowCount(1);
	pGrid->SetFixedColumnCount(1);
	pGrid->SetColumnWidth(0,35);
	pGrid->ExpandColumnsToFit();

	pGrid->SetEditable(TRUE);
	pGrid->EnableSelection(TRUE);

	//header
	{
		GV_ITEM Item;
		Item.mask = GVIF_TEXT;

		Item.row = 0;
		Item.col = 0;
		Item.strText = "Index";
		pGrid->SetItem(&Item);
		Item.col = 1;
		Item.strText = "Defect Pos X";
		pGrid->SetItem(&Item);
		Item.col = 2;
		Item.strText = "Defect Pos Y";
		pGrid->SetItem(&Item);
	}

	for (int i = 0 ; i<GRID_MAX_COUNT_ROW; i++)
	{
		GV_ITEM Item;
		Item.mask = GVIF_TEXT;
		Item.col = 0;
		Item.row = i+1;
		strTemp.Format("%d",i+1);
		Item.strText = strTemp;
		pGrid->SetItem(&Item);
	}

	pGrid->Invalidate(FALSE);
}

BOOL CDefectPositionCompareDlg::ParsingAOIResultFile( CString strFileFath, DEFECTINFO_CONTAINER &mapDefectInfo )
{
	if(strFileFath.GetLength() == 0) return FALSE;
	//if(m_mapDefectInfo1.empty() == FALSE) return TRUE; // ������ �Ľ��� ������ ������ SKIP

	std::ifstream	file;
	char			sLine[1024] = {0,}, sTemp[1024] = {0,};
	int				nCellCnt = 0, nDefectCnt = 0, nCount = 0;
	int				i, j;
	CakParser		Parser;
	int nmaxDefectCount = 0;
	file.open(strFileFath.GetBuffer(0), std::ios::in /*| std::ios::nocreate*/);
	if(!file.is_open())
	{
		file.close();
		AfxMessageBox("Parsing AOIResultFile Fail!: File not exist");
		return FALSE;
	}

	mapDefectInfo.clear();

	// 1 line "00,1,0000/00/00,00:00:00,2018/06/07,17:52:30,101,16,14400,AAAAAA;"
	file.getline(sLine, sizeof(sLine));
	Parser.getTokStr(1, sTemp, sizeof(sTemp));
	nmaxDefectCount = atoi(sLine);

	for(j = 0; j < nmaxDefectCount; j++)
	{
		// 5 line "50,PJALN,703.588,369.166,14.64,S,N,AA,2441.68,6.54,13.10,9999.999,9999.999,99999,99999,0,AAAAA,N_HPANELID_0402_703.588_369.166.jpg,,,57,*;"
		file.getline(sLine, sizeof(sLine));
		if(strlen(sLine) <= 0)
			continue;

		Parser.process(sLine);

		DEFECTINFO defectInfo;

		defectInfo.nIndex = nCount;

		// X ��ǥ
		Parser.getTokStr(0, sTemp, sizeof(sTemp));
		defectInfo.nX = static_cast<int>(atof(sTemp)*1000);

		// Y ��ǥ
		Parser.getTokStr(1, sTemp, sizeof(sTemp));
		defectInfo.nY = static_cast<int>(atof(sTemp)*1000);

		mapDefectInfo.insert(std::make_pair(defectInfo.nX, defectInfo));

		nCount++;
	}

	file.close();

	return TRUE;
}

void CDefectPositionCompareDlg::FileCompare()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(UpdateData(TRUE) == FALSE)	return;

	CString strSaveFile1, strSaveFile2, strBuffer;
	int nMatchCnt1 = 0, nMatchCnt2 = 0;

	// File load
	//if(ParsingAOIResultFile(m_strRstFile1, m_mapDefectInfo1) == FALSE || ParsingCPStackFile() == FALSE)	return;
	if(ParsingAOIResultFile(m_strRstFile1, m_mapDefectInfo1) == FALSE || ParsingAOIResultFile(m_strRstFile2, m_mapDefectInfo2) == FALSE)	
		return;

	// Matching (�� um��)
	if(CompareDefectPosition() == FALSE) return;

	// Compare Report Save
	if(m_strCompDirectory.IsEmpty())
	{
		strSaveFile1.Format(".\\CompareReport_Source.csv");
		strSaveFile2.Format(".\\CompareReport_Target.csv");
	}
	else
	{
		strSaveFile1.Format("%s\\CompareReport_Source.csv", m_strCompDirectory);
		strSaveFile2.Format("%s\\CompareReport_Target.csv", m_strCompDirectory);
	}

	std::ofstream file;

	// Result file Source report save
	file.open(strSaveFile1.GetBuffer(0), std::ios::out | std::ios::trunc);
	if(!file.is_open())
	{
		file.close();
		AfxMessageBox("Compare Report File save fail! (CompareReport_Source)");
		return;
	}

	if(m_mapDefectInfo1.empty() == FALSE)
	{
		strBuffer.Format("Index,X,Y,Result\n");
		file.write(strBuffer.GetBuffer(0), strBuffer.GetLength());

		DEFECTINFO_CONTAINER_IT it;
		int i;

		for(it = m_mapDefectInfo1.begin(), i = 0; it != m_mapDefectInfo1.end(); ++it, i++)
		{
			strBuffer.Format("%d,%0.3f,%0.3f,%d\n", i, it->second.nX*0.001, it->second.nY*0.001, it->second.nMatch);
			file.write(strBuffer.GetBuffer(0), strBuffer.GetLength());
			if(it->second.nMatch > 0)
			{
				nMatchCnt1++;
			}
		}
	}

	file.close();

	// Result file Target report save
	file.open(strSaveFile2.GetBuffer(0), std::ios::out | std::ios::trunc);
	if(!file.is_open())
	{
		file.close();
		AfxMessageBox("Compare Report File save fail! (CompareReport_Target)");
		return;
	}

	if(m_mapDefectInfo2.empty() == FALSE)
	{
		strBuffer.Format("Index,X,Y,Result\n");
		file.write(strBuffer.GetBuffer(0), strBuffer.GetLength());

		DEFECTINFO_CONTAINER_IT it;
		int i;

		for(it = m_mapDefectInfo2.begin(), i = 0; it != m_mapDefectInfo2.end(); ++it, i++)
		{
			strBuffer.Format("%d,%0.3f,%0.3f,%d\n", i, it->second.nX*0.001, it->second.nY*0.001, it->second.nMatch);
			file.write(strBuffer.GetBuffer(0), strBuffer.GetLength());
			if(it->second.nMatch > 0)
			{
				nMatchCnt2++;
			}
		}
	}

	file.close();

	CString strMsg;
	strMsg.Format("Source Defect : %d / %d (%0.2f%%)\nTarget Defect : %d / %d (%0.2f%%)\n", nMatchCnt1, m_mapDefectInfo1.size(), ((double)nMatchCnt1/(double)m_mapDefectInfo1.size())*100,
		nMatchCnt2, m_mapDefectInfo2.size(), ((double)nMatchCnt2/(double)m_mapDefectInfo2.size())*100);
	MessageBox(strMsg.GetBuffer(0), "Compare Report");
}

void CDefectPositionCompareDlg::DefectPositionCompare()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(UpdateData(TRUE) == FALSE)	return;

	CString strSaveFile1, strSaveFile2, strBuffer;
	CString strFileName1, strFileName2;
	int nMatchCnt1 = 0, nMatchCnt2 = 0;

	CTime time = CTime::GetCurrentTime();
	CString strTime = "";
	strTime.Format("%04d%02d%02d_%02d%02d%02d", time.GetYear(), time.GetMonth(), time.GetDay(),time.GetHour(), time.GetMinute(),time.GetSecond());

	// File load
	//Grid Data�� map�� �����ؼ� ó������.
	if(GetDefectDataFromGrid(0) == FALSE || GetDefectDataFromGrid(1) == FALSE)	
		return;
	
	if (m_mapDefectInfo1.size() <= 0 || m_mapDefectInfo2.size() <= 0)
		return;
		
	// Matching (�� um��)
	if(CompareDefectPosition() == FALSE) return;

	// Compare Report Save
	if(m_strCompDirectory.IsEmpty())
	{
		strSaveFile1.Format(".\\CompareReport_Source.csv");
		strSaveFile2.Format(".\\CompareReport_Target.csv");
	}
	else
	{
		strSaveFile1.Format("%s\\CompareReport_Source.csv", m_strCompDirectory);
		strSaveFile2.Format("%s\\CompareReport_Target.csv", m_strCompDirectory);
	}

	std::ofstream file;

	// Result file Source report save
	file.open(strSaveFile1.GetBuffer(0), std::ios::out | std::ios::trunc);
	if(!file.is_open())
	{
		file.close();
		AfxMessageBox("Compare Report File save fail! (CompareReport_Source)");
		return;
	}

	if(m_mapDefectInfo1.empty() == FALSE)
	{
		strBuffer.Format("Index,X,Y,Result\n");
		file.write(strBuffer.GetBuffer(0), strBuffer.GetLength());

		DEFECTINFO_CONTAINER_IT it;
		int i;

		for(it = m_mapDefectInfo1.begin(), i = 0; it != m_mapDefectInfo1.end(); ++it, i++)
		{
			strBuffer.Format("%d,%0.3f,%0.3f,%d\n", i, it->second.nX*0.001, it->second.nY*0.001, it->second.nMatch);
			file.write(strBuffer.GetBuffer(0), strBuffer.GetLength());
			if(it->second.nMatch > 0)
			{
				nMatchCnt1++;
			}
		}
	}

	file.close();

	// Result file Target report save
	file.open(strSaveFile2.GetBuffer(0), std::ios::out | std::ios::trunc);
	if(!file.is_open())
	{
		file.close();
		AfxMessageBox("Compare Report File save fail! (CompareReport_Target)");
		return;
	}

	if(m_mapDefectInfo2.empty() == FALSE)
	{
		strBuffer.Format("Index,X,Y,Result\n");
		file.write(strBuffer.GetBuffer(0), strBuffer.GetLength());

		DEFECTINFO_CONTAINER_IT it;
		int i;

		for(it = m_mapDefectInfo2.begin(), i = 0; it != m_mapDefectInfo2.end(); ++it, i++)
		{
			strBuffer.Format("%d,%0.3f,%0.3f,%d\n", i, it->second.nX*0.001, it->second.nY*0.001, it->second.nMatch);
			file.write(strBuffer.GetBuffer(0), strBuffer.GetLength());
			if(it->second.nMatch > 0)
			{
				nMatchCnt2++;
			}
		}
	}

	file.close();

	CString strMsg;
	strMsg.Format("Source Defect : %d / %d (%0.2f%%)\nTarget Defect : %d / %d (%0.2f%%)\n", nMatchCnt1, m_mapDefectInfo1.size(), ((double)nMatchCnt1/(double)m_mapDefectInfo1.size())*100,
		nMatchCnt2, m_mapDefectInfo2.size(), ((double)nMatchCnt2/(double)m_mapDefectInfo2.size())*100);

	if(m_strCompDirectory.IsEmpty())
	{
		strFileName1.Format(".\\CompareReport_Source_%d_%d_%0.2f_%s.csv",nMatchCnt1, m_mapDefectInfo1.size(), ((double)nMatchCnt1/(double)m_mapDefectInfo1.size())*100,strTime);
		strFileName2.Format(".\\CompareReport_Target_%d_%d_%0.2f_%s.csv",nMatchCnt2, m_mapDefectInfo2.size(), ((double)nMatchCnt2/(double)m_mapDefectInfo2.size())*100,strTime);
	}
	else
	{
		strFileName1.Format("%s\\CompareReport_Source_%d_%d_%0.2f_%s.csv", m_strCompDirectory,nMatchCnt1, m_mapDefectInfo1.size(), ((double)nMatchCnt1/(double)m_mapDefectInfo1.size())*100,strTime);
		strFileName2.Format("%s\\CompareReport_Target_%d_%d_%0.2f_%s.csv", m_strCompDirectory,nMatchCnt2, m_mapDefectInfo2.size(), ((double)nMatchCnt2/(double)m_mapDefectInfo2.size())*100,strTime);
	}

	CopyFile(strSaveFile1,strFileName1,FALSE);
	CopyFile(strSaveFile2,strFileName2,FALSE);

	MessageBox(strMsg.GetBuffer(0), "Compare Report");
}

BOOL CDefectPositionCompareDlg::GetDefectDataFromGrid( int nIndex )
{
	UpdateData(TRUE);

	CGridCtrl* pGrid;;
	CString strTempX = "",strTempY = "";
	int nUnit = 0;

	if (m_bUseUnitUm == TRUE)
		nUnit = 1;
	else
		nUnit = 1000;

	if (nIndex == 0)
	{
		pGrid = &m_GridDefectPosData1;
		
		for (int i =1;i<GRID_MAX_COUNT_ROW+1;i++)
		{
			DEFECTINFO defectInfo;

			defectInfo.nIndex = i;

			// X ��ǥ
			strTempX = pGrid->GetItemText(i,1);
			defectInfo.nX = static_cast<int>(atof(strTempX)*nUnit);
			
			// Y ��ǥ
			strTempY = pGrid->GetItemText(i,2);
			defectInfo.nY = static_cast<int>(atof(strTempY)*nUnit);

			if (strTempX == "" || strTempY == "")
				return TRUE;

			m_mapDefectInfo1.insert(std::make_pair(defectInfo.nX, defectInfo));
		}
	}
	else
	{
		pGrid = &m_GridDefectPosData2;

		for (int i =1;i<GRID_MAX_COUNT_ROW+1;i++)
		{
			DEFECTINFO defectInfo;

			defectInfo.nIndex = i;
			
			// X ��ǥ
			strTempX = pGrid->GetItemText(i,1);
			defectInfo.nX = static_cast<int>(atof(strTempX)*nUnit);

			// Y ��ǥ
			strTempY = pGrid->GetItemText(i,2);
			defectInfo.nY = static_cast<int>(atof(strTempY)*nUnit);

			if (strTempX == "" || strTempY == "")
				return TRUE;

			m_mapDefectInfo2.insert(std::make_pair(defectInfo.nX, defectInfo));
		}
	}
	
	return TRUE;
}

BOOL CDefectPositionCompareDlg::CompareDefectPosition()
{
	if(m_mapDefectInfo1.empty() || m_mapDefectInfo2.empty())
		return FALSE;

	////////////////////////////////////////////////////////////////////////// Stack Flag ����
	//���������� ���� ���� nIdx = 0. ���� ��, 1. ���� ��, 2. �ݻ� ��, 3. �ݻ� ��, 4. ����ũ ����, 5. ���Ӱ���
	// ���� �������� ����� ������ SD�� �ƴ�.
	//BOOL bIsTD = FALSE;
	//int i = 0, j = 0, k = 0, nCurStepCount = 0;
	int nDistY;
	//int nStackDistance = 10000; // um//g_pSetting->GetStackDefectSize();

	DEFECTINFO_CONTAINER_IT itSour;
	DEFECTINFO_CONTAINER_IT itDestUp, itDestDown;

	for(itSour = m_mapDefectInfo1.begin(); itSour != m_mapDefectInfo1.end(); ++itSour)
	{
		itDestUp = m_mapDefectInfo2.upper_bound(itSour->first - m_nDistance);
		itDestDown = m_mapDefectInfo2.lower_bound(itSour->first + m_nDistance);

		while(itDestUp != itDestDown)
		{
			if (itDestUp->second.nX - m_nDistance > itSour->first)
				break;

			nDistY = abs(itDestUp->second.nY - itSour->second.nY);

			if(nDistY > m_nDistance)
			{
				++itDestUp;
				continue;
			}

			itSour->second.nMatch++;
			itDestUp->second.nMatch++;

			++itDestUp;
		}
	}

	return TRUE;
}


void CDefectPositionCompareDlg::OnBnClickedNoneFileCompare()
{
	UpdateData(TRUE);
	if (m_bNoneFileCompare == FALSE)
	{	
		GetDlgItem( IDC_EDIT_RSTFILE1_PATH )->EnableWindow(TRUE);
		GetDlgItem( IDC_BTN_FIND1 )->EnableWindow(TRUE);
		GetDlgItem( IDC_EDIT_RSTFILE2_PATH )->EnableWindow(TRUE);
		GetDlgItem( IDC_BTN_FIND2)->EnableWindow(TRUE);
	}
	else
	{	
		GetDlgItem( IDC_EDIT_RSTFILE1_PATH )->EnableWindow(FALSE);
		GetDlgItem( IDC_BTN_FIND1 )->EnableWindow(FALSE);
		GetDlgItem( IDC_EDIT_RSTFILE2_PATH )->EnableWindow(FALSE);
		GetDlgItem( IDC_BTN_FIND2)->EnableWindow(FALSE);
	}
}

void CDefectPositionCompareDlg::OnBnClickedButton1()
{
	CGridCtrl* pGrid = &m_GridDefectPosData1;
	int nRowCnt = m_mapDefectInfo1.size();

	for (int i = 1 ; i<= nRowCnt; i++)
	{
		pGrid->SetItemText(i,1, "");
		pGrid->SetItemText(i,2, "");
	}

	m_mapDefectInfo1.clear();

	pGrid->Invalidate(FALSE);
}

void CDefectPositionCompareDlg::OnBnClickedButton2()
{
	CGridCtrl* pGrid = &m_GridDefectPosData2;
	int nRowCnt = m_mapDefectInfo2.size();

	for (int i = 1 ; i<= nRowCnt; i++)
	{
		pGrid->SetItemText(i,1, "");
		pGrid->SetItemText(i,2, "");
	}

	m_mapDefectInfo2.clear();

	pGrid->Invalidate(FALSE);
}
