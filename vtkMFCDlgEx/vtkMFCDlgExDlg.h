
// vtkMFCDlgExDlg.h : 헤더 파일
//

#pragma once
#include "afxmenubutton.h"
#include <vtkSTLReader.h>


// CvtkMFCDlgExDlg 대화 상자
class CvtkMFCDlgExDlg : public CDialogEx
{
// 생성입니다.
public:
	CvtkMFCDlgExDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_VTKMFCDLGEX_DIALOG };

	protected:
//	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.
public:
	vtkSmartPointer<vtkRenderWindow>  		m_vtkWindow;

	void InitVtkWindow(void* hWnd);	// Initialize VTK Window 
	void ResizeVtkWindow();	// Resize VTK window

protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStart2();
	afx_msg void OnBnClickedButtonTest();
	afx_msg void OnBnClickedButtonExampleHolefilling();

public:
	vtkSmartPointer<vtkSTLReader> m_pSTLReader;
	vtkSmartPointer<vtkPolyData> m_pPolyData;
	vtkIdType m_cellID;
};
