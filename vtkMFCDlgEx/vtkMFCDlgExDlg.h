
// vtkMFCDlgExDlg.h : ��� ����
//

#pragma once
#include "afxmenubutton.h"
#include <vtkSTLReader.h>


// CvtkMFCDlgExDlg ��ȭ ����
class CvtkMFCDlgExDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CvtkMFCDlgExDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_VTKMFCDLGEX_DIALOG };

	protected:
//	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

// �����Դϴ�.
public:
	vtkSmartPointer<vtkRenderWindow>  		m_vtkWindow;

	void InitVtkWindow(void* hWnd);	// Initialize VTK Window 
	void ResizeVtkWindow();	// Resize VTK window

protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
