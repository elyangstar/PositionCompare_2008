
// DefectPositionCompare.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CDefectPositionCompareApp:
// �� Ŭ������ ������ ���ؼ��� DefectPositionCompare.cpp�� �����Ͻʽÿ�.
//

class CDefectPositionCompareApp : public CWinAppEx
{
public:
	CDefectPositionCompareApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CDefectPositionCompareApp theApp;