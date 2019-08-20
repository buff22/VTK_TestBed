#pragma once
#include "vtkMFCDlgEx.h"
#include "afxmenubutton.h"

class CvtkMFCDlgExDlg : public CDialogEx
{

public:
	CvtkMFCDlgExDlg(CWnd* pParent = NULL);	// 표준 생성자
	enum { IDD = IDD_VTKMFCDLGEX_DIALOG };

protected:
	HICON m_hIcon;
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);

public:
	void InitVtkWindow(void* hWnd);	// Initialize VTK Window 
	void ResizeVtkWindow();	// Resize VTK window

public:
	afx_msg void OnClickedBtnFileLoad();
	afx_msg void OnBnClickedBtnNeighborRing();
	afx_msg void OnBnClickedBtnNeighborArea();
	afx_msg void OnBnClickedBtnExampleNeighborFace();
	afx_msg void OnBnClickedButtonExampleHolefilling();
	void RenderingSTLFile(CString& strSTLPath);
	void SetGeneralInfo(vtkPolyData* inputData = nullptr,
		bool bIsInit = false);
	void GenerateNeighborList(OUT std::vector<vtkIdType>& vecOut,
		IN std::vector<vtkIdType>& vecIn, IN vtkSmartPointer<vtkTriangleFilter>& triangleFilter);
	void Deduplication(std::vector<vtkIdType>& vec);
	void GenerateNeighborRing(OUT std::vector<vtkIdType>& vecOut,
		IN std::vector<vtkIdType>& vecMax,
		IN std::vector<vtkIdType>& vecMin,
		IN std::vector<vtkIdType>& vecPickFace);
	void GenerateNeighborArea(OUT std::vector<vtkIdType>& vecOut,
		IN std::vector<vtkIdType>& vecMax,
		IN std::vector<vtkIdType>& vecPickFace);

public:
	vtkSmartPointer<vtkRenderWindow>  		m_vtkWindow;
	vtkSmartPointer<vtkPolyData>			m_pPolyData;
	CComboBox*								m_cbNeighborDepth;
	std::vector<std::vector<vtkIdType>>		m_vecNeighborFace;
	std::vector<vtkIdType>					m_vecSelectedFace;
};
