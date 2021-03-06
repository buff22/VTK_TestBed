#include "stdafx.h"
#include "vtkMFCDlgEx.h"
#include "vtkMFCDlgExDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CvtkMFCDlgExDlg 대화 상자
CvtkMFCDlgExDlg::CvtkMFCDlgExDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CvtkMFCDlgExDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

BEGIN_MESSAGE_MAP(CvtkMFCDlgExDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_FILELOAD, &CvtkMFCDlgExDlg::OnClickedBtnFileLoad)
	ON_BN_CLICKED(IDC_BTN_NEIGHBOR_RING, &CvtkMFCDlgExDlg::OnBnClickedBtnNeighborRing)
	ON_BN_CLICKED(IDC_BTN_NEIGHBOR_AREA, &CvtkMFCDlgExDlg::OnBnClickedBtnNeighborArea)
	ON_BN_CLICKED(IDC_BTN_DELETE_SELECTEDFACE, &CvtkMFCDlgExDlg::OnBnClickedBtnDeleteSelectedface)
	ON_BN_CLICKED(IDC_BTN_FILLHOLE, &CvtkMFCDlgExDlg::OnBnClickedBtnFillhole)
	ON_BN_CLICKED(IDC_BTN_EXAMPLE_NEIGHBORFACE, &CvtkMFCDlgExDlg::OnBnClickedBtnExampleNeighborFace)
	ON_BN_CLICKED(IDC_BTN_EXAMPLE_HOLEFILLING, &CvtkMFCDlgExDlg::OnBnClickedButtonExampleHolefilling)
END_MESSAGE_MAP()

// CvtkMFCDlgExDlg 메시지 처리기
BOOL CvtkMFCDlgExDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.
	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	if (this->GetDlgItem(IDC_STATIC_FRAME))
	{
		this->InitVtkWindow(this->GetDlgItem(IDC_STATIC_FRAME)->GetSafeHwnd());	// Initialize VTK window
		this->ResizeVtkWindow();
	}

	// Warning Off
	vtkObject::GlobalWarningDisplayOff();

	// comboNeighborDepth 설정
	{
		// <#> Resource값 가져오기
		m_cbNeighborDepth = (CComboBox*)this->GetDlgItem(IDC_COMBO_NEIGHBORDEPTH);
		
		// <#> ComboBox 등록
		m_cbNeighborDepth->AddString(_T("01"));
		m_cbNeighborDepth->AddString(_T("02"));
		m_cbNeighborDepth->AddString(_T("03"));
		m_cbNeighborDepth->AddString(_T("04"));
		m_cbNeighborDepth->AddString(_T("05"));
		m_cbNeighborDepth->AddString(_T("06"));
		m_cbNeighborDepth->AddString(_T("07"));
		m_cbNeighborDepth->AddString(_T("08"));
		m_cbNeighborDepth->AddString(_T("09"));
		m_cbNeighborDepth->AddString(_T("10"));

		// <#> ComboBox 최초 선택
		m_cbNeighborDepth->SelectString(0, _T("01"));
	}

	// General Infoamtion Init
	SetGeneralInfo(nullptr, true);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CvtkMFCDlgExDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.
void CvtkMFCDlgExDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CvtkMFCDlgExDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CvtkMFCDlgExDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	this->ResizeVtkWindow();
}

void CvtkMFCDlgExDlg::InitVtkWindow(void* hWnd)
{
	// vtk Render Window 생성
	if (m_vtkWindow == NULL)
	{
		// Interactor 생성
		vtkSmartPointer<vtkRenderWindowInteractor> interactor =
			vtkSmartPointer<vtkRenderWindowInteractor>::New();
		// Trackball Camera 인터랙션 스타일 적용
		interactor->SetInteractorStyle(
			vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New());

		// Renderer 생성
		vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
		renderer->SetBackground(0.0, 0.0, 0.0);		// 검은색 배경

		// RenderWindow 생성 후 Dialog 핸들, Renderer 설정
		m_vtkWindow = vtkSmartPointer<vtkRenderWindow>::New();
		m_vtkWindow->SetParentId(hWnd);
		m_vtkWindow->SetInteractor(interactor);
		m_vtkWindow->AddRenderer(renderer);
		m_vtkWindow->Render();
	}
}

void CvtkMFCDlgExDlg::ResizeVtkWindow()
{
	CRect rc;
	GetDlgItem(IDC_STATIC_FRAME)->GetClientRect(rc);
	m_vtkWindow->SetSize(rc.Width(), rc.Height());
}

void cbMouseoverFace(vtkObject* caller, long unsigned int eventId,
	void* clientData, void* callData)
{
	// Interactor 가져오기
	vtkSmartPointer<vtkRenderWindowInteractor> interactor =
		vtkRenderWindowInteractor::SafeDownCast(caller);
	if (interactor == NULL)
		return;

	// ClientData 가져오기
	CvtkMFCDlgExDlg* dlg = (CvtkMFCDlgExDlg*)clientData;
	if (dlg == NULL)
		return;

	// 마우스 클릭 위치
	int pos[2];
	interactor->GetLastEventPosition(pos);

	// 마우스 클릭 위치에서 Picking 수행
	vtkSmartPointer<vtkCellPicker> picker =
		vtkSmartPointer<vtkCellPicker>::New();
	picker->SetTolerance(0.005);		// picking 감도 설정
	picker->Pick(pos[0], pos[1], 0,
		interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());

	vtkIdType mouseoverFaceIdx = picker->GetCellId();	// -1이면 picking 되지 않음
	if (mouseoverFaceIdx != -1)
	{
		// polyData 찾기
		vtkSmartPointer<vtkRenderer> renderer =
			interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer();

		vtkSmartPointer<vtkActorCollection> actorCollection =
			renderer->GetActors();
		actorCollection->InitTraversal();

		vtkSmartPointer<vtkActor> actor =
			actorCollection->GetNextActor();

		vtkSmartPointer<vtkMapper> mapper =
			actor->GetMapper();

		vtkSmartPointer<vtkPolyData> polyData = (vtkPolyData*)mapper->GetInput();

		vtkSmartPointer<vtkTriangleFilter> triangleFilter =
			vtkSmartPointer<vtkTriangleFilter>::New();
		triangleFilter->SetInputData(polyData);
		triangleFilter->Update();

		// <#> MouseOverFace 색칠하기
		vtkSmartPointer<vtkDataSetMapper> mapperPickingFace =
			vtkSmartPointer<vtkDataSetMapper>::New();
		{
			vtkSmartPointer<vtkIdTypeArray> ids =
				vtkSmartPointer<vtkIdTypeArray>::New();
			ids->SetNumberOfComponents(1);
			ids->InsertNextValue(mouseoverFaceIdx);

			vtkSmartPointer<vtkSelectionNode> selectionNode =
				vtkSmartPointer<vtkSelectionNode>::New();
			selectionNode->SetFieldType(vtkSelectionNode::CELL);
			selectionNode->SetContentType(vtkSelectionNode::INDICES);
			selectionNode->SetSelectionList(ids);

			vtkSmartPointer<vtkSelection> selection =
				vtkSmartPointer<vtkSelection>::New();
			selection->AddNode(selectionNode);

			vtkSmartPointer<vtkExtractSelection> extractSelection =
				vtkSmartPointer<vtkExtractSelection>::New();
			extractSelection->SetInputConnection(0, triangleFilter->GetOutputPort());
			extractSelection->SetInputData(1, selection);
			extractSelection->Update();

			mapperPickingFace->SetInputConnection(extractSelection->GetOutputPort());
		}
		vtkSmartPointer<vtkActor> actorMouseoverFace =
			vtkSmartPointer<vtkActor>::New();
		actorMouseoverFace->SetMapper(mapperPickingFace);
		actorMouseoverFace->GetProperty()->SetColor(0, 0, 1);

		// <#> 화면에 뿌리기
		{
			//Add the actors to the scene
			renderer->RemoveAllViewProps();
			renderer->AddActor(actor);
			renderer->AddActor(actorMouseoverFace);
			renderer->SetBackground(.3, .2, .1); // Background color dark red

			interactor->GetRenderWindow()->Render();
		}
	}
}

void cbNeighborRingFace(vtkObject* caller, long unsigned int eventId,
	void* clientData, void* callData)
{
	// Interactor 가져오기
	vtkSmartPointer<vtkRenderWindowInteractor> interactor =
		vtkRenderWindowInteractor::SafeDownCast(caller);
	if (interactor == NULL)
		return;

	// ClientData 가져오기
	CvtkMFCDlgExDlg* dlg = (CvtkMFCDlgExDlg*)clientData;
	if (dlg == NULL)
		return;

	// 마우스 클릭 위치
	int pos[2];
	interactor->GetLastEventPosition(pos);

	// 마우스 클릭 위치에서 Picking 수행
	vtkSmartPointer<vtkCellPicker> picker =
		vtkSmartPointer<vtkCellPicker>::New();
	picker->SetTolerance(0.005);		// picking 감도 설정
	picker->Pick(pos[0], pos[1], 0,
		interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());

	vtkIdType pikingFaceIdx = picker->GetCellId();	// -1이면 picking 되지 않음
	if (pikingFaceIdx != -1)
	{
		// polyData 찾기
		vtkSmartPointer<vtkRenderer> renderer =
		interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer();

		vtkSmartPointer<vtkActorCollection> actorCollection =
		renderer->GetActors();
		actorCollection->InitTraversal();

		vtkSmartPointer<vtkActor> actor =
		actorCollection->GetNextActor();

		vtkSmartPointer<vtkMapper> mapper =
		actor->GetMapper();

		vtkSmartPointer<vtkPolyData> polyData = (vtkPolyData*) mapper->GetInput();
		
		vtkSmartPointer<vtkTriangleFilter> triangleFilter =
			vtkSmartPointer<vtkTriangleFilter>::New();
		triangleFilter->SetInputData(polyData);
		triangleFilter->Update();

		// m_vecNeighborFace 초기화
		dlg->m_vecNeighborFace.clear();

		// Find all cells connected to point 0
		std::vector<vtkIdType> vec;
		vec.push_back(pikingFaceIdx);
		dlg->m_vecNeighborFace.push_back(vec);
		vec.clear();
		dlg->m_vecNeighborFace.push_back(vec);

		// call GenerateNeighborFace
		int nCntDepth = dlg->m_cbNeighborDepth->GetCurSel() + 1;
		for (int i = 0; i < nCntDepth; ++i)
		{
			dlg->GenerateNeighborList(dlg->m_vecNeighborFace.at(i + 1),
				dlg->m_vecNeighborFace.at(i),
				triangleFilter);

			// 찾은 vec 정리
			dlg->Deduplication(dlg->m_vecNeighborFace.at(i + 1));

			vec.clear();
			dlg->m_vecNeighborFace.push_back(vec);

			// <#> Debug 출력
			OutputDebugString(L"\n Point neighbor ids are: ");
			for (std::vector<vtkIdType>::iterator it1 = dlg->m_vecNeighborFace.at(i + 1).begin(); it1 != dlg->m_vecNeighborFace.at(i + 1).end(); it1++)
			{
				CString strDebug;
				strDebug.Format(L" %d", *it1);
				::OutputDebugString(strDebug);
			}
			OutputDebugString(L"\n");
		}

		// <#> PickingFace 색칠하기
		vtkSmartPointer<vtkDataSetMapper> mapperPickingFace =
			vtkSmartPointer<vtkDataSetMapper>::New();
		{
			vtkSmartPointer<vtkIdTypeArray> ids =
				vtkSmartPointer<vtkIdTypeArray>::New();
			ids->SetNumberOfComponents(1);
			ids->InsertNextValue(dlg->m_vecNeighborFace.at(0).at(0));

			vtkSmartPointer<vtkSelectionNode> selectionNode =
				vtkSmartPointer<vtkSelectionNode>::New();
			selectionNode->SetFieldType(vtkSelectionNode::CELL);
			selectionNode->SetContentType(vtkSelectionNode::INDICES);
			selectionNode->SetSelectionList(ids);

			vtkSmartPointer<vtkSelection> selection =
				vtkSmartPointer<vtkSelection>::New();
			selection->AddNode(selectionNode);

			vtkSmartPointer<vtkExtractSelection> extractSelection =
				vtkSmartPointer<vtkExtractSelection>::New();
			extractSelection->SetInputConnection(0, triangleFilter->GetOutputPort());
			extractSelection->SetInputData(1, selection);
			extractSelection->Update();

			mapperPickingFace->SetInputConnection(extractSelection->GetOutputPort());
		}
		vtkSmartPointer<vtkActor> actorPickingFace =
			vtkSmartPointer<vtkActor>::New();
		actorPickingFace->SetMapper(mapperPickingFace);
		actorPickingFace->GetProperty()->SetColor(1, 0, 0);
		
		// <#> NeighborFace 색칠하기
		vtkSmartPointer<vtkDataSetMapper> mapperNeighborFace =
			vtkSmartPointer<vtkDataSetMapper>::New();
		{
			// GenerateNeighborRing 
			std::vector<vtkIdType> vecNeighborRing;
			dlg->GenerateNeighborRing(vecNeighborRing,
				dlg->m_vecNeighborFace.at(nCntDepth),
				dlg->m_vecNeighborFace.at(nCntDepth - 1),
				dlg->m_vecNeighborFace.at(0));

			vtkSmartPointer<vtkIdTypeArray> ids =
				vtkSmartPointer<vtkIdTypeArray>::New();
			ids->SetNumberOfComponents(1);
			dlg->m_vecSelectedFace.clear();
			for (std::vector<vtkIdType>::iterator it1 = vecNeighborRing.begin(); it1 != vecNeighborRing.end(); it1++)
			{
				ids->InsertNextValue(*it1);
				dlg->m_vecSelectedFace.push_back(*it1);
			}

			vtkSmartPointer<vtkSelectionNode> selectionNode =
				vtkSmartPointer<vtkSelectionNode>::New();
			selectionNode->SetFieldType(vtkSelectionNode::CELL);
			selectionNode->SetContentType(vtkSelectionNode::INDICES);
			selectionNode->SetSelectionList(ids);

			vtkSmartPointer<vtkSelection> selection =
				vtkSmartPointer<vtkSelection>::New();
			selection->AddNode(selectionNode);

			vtkSmartPointer<vtkExtractSelection> extractSelection =
				vtkSmartPointer<vtkExtractSelection>::New();
			extractSelection->SetInputConnection(0, triangleFilter->GetOutputPort());
			extractSelection->SetInputData(1, selection);
			extractSelection->Update();

			mapperNeighborFace->SetInputConnection(extractSelection->GetOutputPort());
		}
		vtkSmartPointer<vtkActor> actorNeighborFace =
			vtkSmartPointer<vtkActor>::New();
		actorNeighborFace->SetMapper(mapperNeighborFace);
		actorNeighborFace->GetProperty()->SetColor(0, 1, 0);

		// <#> 화면에 뿌리기
		{
			//Add the actors to the scene
			renderer->RemoveAllViewProps();
			renderer->AddActor(actor);
			renderer->AddActor(actorPickingFace);
			renderer->AddActor(actorNeighborFace);
			renderer->SetBackground(.3, .2, .1); // Background color dark red

			interactor->GetRenderWindow()->Render();
		}
	}
}

void cbNeighborAreaFace(vtkObject* caller, long unsigned int eventId,
	void* clientData, void* callData)
{
	// Interactor 가져오기
	vtkSmartPointer<vtkRenderWindowInteractor> interactor =
		vtkRenderWindowInteractor::SafeDownCast(caller);
	if (interactor == NULL)
		return;

	// ClientData 가져오기
	CvtkMFCDlgExDlg* dlg = (CvtkMFCDlgExDlg*)clientData;
	if (dlg == NULL)
		return;

	// 마우스 클릭 위치
	int pos[2];
	interactor->GetLastEventPosition(pos);

	// 마우스 클릭 위치에서 Picking 수행
	vtkSmartPointer<vtkCellPicker> picker =
		vtkSmartPointer<vtkCellPicker>::New();
	picker->SetTolerance(0.005);		// picking 감도 설정
	picker->Pick(pos[0], pos[1], 0,
		interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());

	vtkIdType pikingFaceIdx = picker->GetCellId();	// -1이면 picking 되지 않음
	if (pikingFaceIdx != -1)
	{
		// polyData 찾기
		vtkSmartPointer<vtkRenderer> renderer =
			interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer();

		vtkSmartPointer<vtkActorCollection> actorCollection =
			renderer->GetActors();
		actorCollection->InitTraversal();

		vtkSmartPointer<vtkActor> actor =
			actorCollection->GetNextActor();

		vtkSmartPointer<vtkMapper> mapper =
			actor->GetMapper();

		vtkSmartPointer<vtkPolyData> polyData = (vtkPolyData*)mapper->GetInput();

		vtkSmartPointer<vtkTriangleFilter> triangleFilter =
			vtkSmartPointer<vtkTriangleFilter>::New();
		triangleFilter->SetInputData(polyData);
		triangleFilter->Update();

		// m_vecNeighborFace 초기화
		dlg->m_vecNeighborFace.clear();

		// Find all cells connected to point 0
		std::vector<vtkIdType> vec;
		vec.push_back(pikingFaceIdx);
		dlg->m_vecNeighborFace.push_back(vec);
		vec.clear();
		dlg->m_vecNeighborFace.push_back(vec);

		// call GenerateNeighborFace
		int nCntDepth = dlg->m_cbNeighborDepth->GetCurSel() + 1;
		for (int i = 0; i < nCntDepth; ++i)
		{
			dlg->GenerateNeighborList(dlg->m_vecNeighborFace.at(i + 1),
				dlg->m_vecNeighborFace.at(i),
				triangleFilter);

			// 찾은 vec 정리
			dlg->Deduplication(dlg->m_vecNeighborFace.at(i + 1));

			vec.clear();
			dlg->m_vecNeighborFace.push_back(vec);

			// <#> Debug 출력
			OutputDebugString(L"\n Point neighbor ids are: ");
			for (std::vector<vtkIdType>::iterator it1 = dlg->m_vecNeighborFace.at(i + 1).begin(); it1 != dlg->m_vecNeighborFace.at(i + 1).end(); it1++)
			{
				CString strDebug;
				strDebug.Format(L" %d", *it1);
				::OutputDebugString(strDebug);
			}
			OutputDebugString(L"\n");
		}

		// <#> PickingFace 색칠하기
		vtkSmartPointer<vtkDataSetMapper> mapperPickingFace =
			vtkSmartPointer<vtkDataSetMapper>::New();
		{
			vtkSmartPointer<vtkIdTypeArray> ids =
				vtkSmartPointer<vtkIdTypeArray>::New();
			ids->SetNumberOfComponents(1);
			ids->InsertNextValue(dlg->m_vecNeighborFace.at(0).at(0));

			vtkSmartPointer<vtkSelectionNode> selectionNode =
				vtkSmartPointer<vtkSelectionNode>::New();
			selectionNode->SetFieldType(vtkSelectionNode::CELL);
			selectionNode->SetContentType(vtkSelectionNode::INDICES);
			selectionNode->SetSelectionList(ids);

			vtkSmartPointer<vtkSelection> selection =
				vtkSmartPointer<vtkSelection>::New();
			selection->AddNode(selectionNode);

			vtkSmartPointer<vtkExtractSelection> extractSelection =
				vtkSmartPointer<vtkExtractSelection>::New();
			extractSelection->SetInputConnection(0, triangleFilter->GetOutputPort());
			extractSelection->SetInputData(1, selection);
			extractSelection->Update();

			mapperPickingFace->SetInputConnection(extractSelection->GetOutputPort());
		}
		vtkSmartPointer<vtkActor> actorPickingFace =
			vtkSmartPointer<vtkActor>::New();
		actorPickingFace->SetMapper(mapperPickingFace);
		actorPickingFace->GetProperty()->SetColor(1, 0, 0);

		// <#> NeighborFace 색칠하기
		vtkSmartPointer<vtkDataSetMapper> mapperNeighborFace =
			vtkSmartPointer<vtkDataSetMapper>::New();
		{
			// GenerateNeighborArea 
			std::vector<vtkIdType> vecNeighborRing;
			dlg->GenerateNeighborArea(vecNeighborRing,
				dlg->m_vecNeighborFace.at(nCntDepth),
				dlg->m_vecNeighborFace.at(0));

			vtkSmartPointer<vtkIdTypeArray> ids =
				vtkSmartPointer<vtkIdTypeArray>::New();
			ids->SetNumberOfComponents(1);
			dlg->m_vecSelectedFace.clear();
			dlg->m_vecSelectedFace.push_back(pikingFaceIdx);
			for (std::vector<vtkIdType>::iterator it1 = vecNeighborRing.begin(); it1 != vecNeighborRing.end(); it1++)
			{
				ids->InsertNextValue(*it1);
				dlg->m_vecSelectedFace.push_back(*it1);
			}

			vtkSmartPointer<vtkSelectionNode> selectionNode =
				vtkSmartPointer<vtkSelectionNode>::New();
			selectionNode->SetFieldType(vtkSelectionNode::CELL);
			selectionNode->SetContentType(vtkSelectionNode::INDICES);
			selectionNode->SetSelectionList(ids);

			vtkSmartPointer<vtkSelection> selection =
				vtkSmartPointer<vtkSelection>::New();
			selection->AddNode(selectionNode);

			vtkSmartPointer<vtkExtractSelection> extractSelection =
				vtkSmartPointer<vtkExtractSelection>::New();
			extractSelection->SetInputConnection(0, triangleFilter->GetOutputPort());
			extractSelection->SetInputData(1, selection);
			extractSelection->Update();

			mapperNeighborFace->SetInputConnection(extractSelection->GetOutputPort());
		}
		vtkSmartPointer<vtkActor> actorNeighborFace =
			vtkSmartPointer<vtkActor>::New();
		actorNeighborFace->SetMapper(mapperNeighborFace);
		actorNeighborFace->GetProperty()->SetColor(0, 1, 0);

		// <#> 화면에 뿌리기
		{
			//Add the actors to the scene
			renderer->RemoveAllViewProps();
			renderer->AddActor(actor);
			renderer->AddActor(actorPickingFace);
			renderer->AddActor(actorNeighborFace);
			renderer->SetBackground(.3, .2, .1); // Background color dark red

			interactor->GetRenderWindow()->Render();
		}
	}
}

void CvtkMFCDlgExDlg::OnClickedBtnFileLoad()
{
	try
	{
		// <#> FileDialog Filter 설정
		TCHAR szFilter[] = _T("STL (*.stl)|*.stl|All Files (*.*)|*.*||");

		// <#> FileDialog 생성
		CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);

		// <#> Data 폴더 경로 설정
		{
			// 실행된 appPath 가져오기
			TCHAR appPath[MAX_PATH];
			GetCurrentDirectory(MAX_PATH, appPath);

			// appPath 분리하기
			CString strDefaultPath;
			CString strSubPath;
			int nCount = 0;
			while (AfxExtractSubString(strSubPath, appPath, nCount, _T('\\')) == TRUE)
			{
				CString strTemp;
				BOOL bRtn = AfxExtractSubString(strTemp, appPath, nCount + 1, _T('\\'));
				if (bRtn == FALSE)
					break;

				strDefaultPath.Format(_T("%s%s\\"), strDefaultPath, strSubPath);
				++nCount;
			}
			strDefaultPath.Format(_T("%s%s"), strDefaultPath, _T("data"));

			// CString to TCHAR[]
			TCHAR szDataFolder[MAX_PATH];
			memset(szDataFolder, 0x00, sizeof(TCHAR) * MAX_PATH);
			_tcscpy_s(szDataFolder, MAX_PATH, strDefaultPath.GetBuffer(0));
			strDefaultPath.ReleaseBuffer();

			// Default Folder 설정
			dlg.m_ofn.lpstrInitialDir = szDataFolder;
		}

		if (dlg.DoModal() == IDOK)
		{
			// stl만 처리가능
			CString strFilePath = dlg.GetPathName();
			CString strExtention = PathFindExtension(strFilePath);
			if (strExtention.Compare(_T(".stl")) != 0)
			{
				MessageBox(_T("Only Load STL Files"), _T("ERROR"), MB_OK);
				throw 1;
			}

			RenderingSTLFile(strFilePath);
		}
	}
	catch (...)
	{
		return;
	}

	return;
}

void CvtkMFCDlgExDlg::OnBnClickedBtnNeighborRing()
{
	// <#1> Interactor
	vtkSmartPointer<vtkRenderWindowInteractor> newIntoractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	newIntoractor->SetInteractorStyle(
		vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New());
	m_vtkWindow->SetInteractor(newIntoractor);

	// <#2> CallBack 함수 설정
	vtkSmartPointer<vtkCallbackCommand> pickCallback =
		vtkSmartPointer<vtkCallbackCommand>::New();
	pickCallback->SetCallback(cbNeighborRingFace);
	pickCallback->SetClientData(this);

	// <#3> Interactor에 Callback 함수 연결
	m_vtkWindow->GetInteractor()->
		AddObserver(vtkCommand::LeftButtonPressEvent, pickCallback);

	// <#3> 화면에 그리기
	m_vtkWindow->Render();
}

void CvtkMFCDlgExDlg::OnBnClickedBtnNeighborArea()
{
	// <#1> Interactor
	vtkSmartPointer<vtkRenderWindowInteractor> newIntoractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	newIntoractor->SetInteractorStyle(
		vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New());
	m_vtkWindow->SetInteractor(newIntoractor);

	// <#2> CallBack 함수 설정
	vtkSmartPointer<vtkCallbackCommand> pickCallback =
		vtkSmartPointer<vtkCallbackCommand>::New();
	pickCallback->SetCallback(cbNeighborAreaFace);
	pickCallback->SetClientData(this);

	// <#3> Interactor에 Callback 함수 연결
	m_vtkWindow->GetInteractor()->
		AddObserver(vtkCommand::LeftButtonPressEvent, pickCallback);

	// <#3> 화면에 그리기
	m_vtkWindow->Render();
}

void CvtkMFCDlgExDlg::OnBnClickedBtnDeleteSelectedface()
{
	// <#1> Mark a cell as deleted.
	for (std::vector<vtkIdType>::iterator iter = m_vecSelectedFace.begin(); iter != m_vecSelectedFace.end(); ++iter)
		m_pPolyData->DeleteCell(*iter);
	
	// <#2> Remove the marked cell.
	m_pPolyData->RemoveDeletedCells();

	// <#3> STL FaceCnt & VertexCnt 정보 반영
	SetGeneralInfo(m_pPolyData);

	// <#4> Mapper 만들기
	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(m_pPolyData);
	mapper->Update();

	// <#5> Actor 만들기
	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->SetEdgeColor(0, 0, 0);
	actor->GetProperty()->EdgeVisibilityOn();

	// <#6> Camera 찾기
	vtkSmartPointer<vtkCamera> camera = 
		m_vtkWindow->GetRenderers()->GetFirstRenderer()->GetActiveCamera();

	// <#7> Renderer 만들기
	vtkSmartPointer<vtkRenderer> prevRenderer =
		m_vtkWindow->GetRenderers()->GetFirstRenderer();
	if (prevRenderer != NULL)
		m_vtkWindow->RemoveRenderer(prevRenderer);

	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->SetBackground(.1, .2, .3);
	renderer->SetActiveCamera(camera);
	m_vtkWindow->AddRenderer(renderer);

	// <#8> 화면에 그리기
	m_vtkWindow->Render();
}

void CvtkMFCDlgExDlg::OnBnClickedBtnExampleNeighborFace()
{
	// <#0> 초기화 
	vtkSmartPointer<vtkRenderer> prevRenderer = m_vtkWindow->GetRenderers()->GetFirstRenderer();
	if (prevRenderer != NULL)
		m_vtkWindow->RemoveRenderer(prevRenderer);

	// <#1> STL Load
	vtkSmartPointer<vtkSTLReader> pSTLReader = vtkSmartPointer<vtkSTLReader>::New();
	pSTLReader->SetFileName("../data/cast3br.stl");
	pSTLReader->Update();

	vtkSmartPointer<vtkTriangleFilter> triangleFilter =
		vtkSmartPointer<vtkTriangleFilter>::New();
	triangleFilter->SetInputConnection(pSTLReader->GetOutputPort());
	triangleFilter->Update();

	// Find all cells connected to point 0
	vtkIdType cellId = 30000;

	vtkSmartPointer<vtkIdList> cellPointIds =
		vtkSmartPointer<vtkIdList>::New();
	triangleFilter->GetOutput()->GetCellPoints(cellId, cellPointIds);

	// neighbor cells may be listed multiple times
	// use std::set instead of std::list if you want a unique list of neighbors
	std::list<vtkIdType> neighbors;

	/*For each vertice of the cell, we calculate which cells uses that point.
	So if we make this, for each vertice, we have all the neighbors.
	In the case we use ''cellPointIds'' as a parameter of ''GeteCellNeighbors'',
	we will obtain an empty set. Because the only cell that is using that set of points
	is the current one. That is why we have to make each vertice at time.*/

	for (vtkIdType i = 0; i < cellPointIds->GetNumberOfIds(); i++)
	{
		vtkSmartPointer<vtkIdList> idList =
			vtkSmartPointer<vtkIdList>::New();
		idList->InsertNextId(cellPointIds->GetId(i));

		//get the neighbors of the cell
		vtkSmartPointer<vtkIdList> neighborCellIds =
			vtkSmartPointer<vtkIdList>::New();

		triangleFilter->GetOutput()->GetCellNeighbors(cellId, idList, neighborCellIds);

		for (vtkIdType j = 0; j < neighborCellIds->GetNumberOfIds(); j++)
		{
			neighbors.push_back(neighborCellIds->GetId(j));
		}

	}

	std::cout << "Point neighbor ids are: " << std::endl;

	for (std::list<vtkIdType>::iterator it1 = neighbors.begin(); it1 != neighbors.end(); it1++)
	{
		std::cout << " " << *it1;
	}
	std::cout << std::endl;


	vtkSmartPointer<vtkDataSetMapper> sphereMapper =
		vtkSmartPointer<vtkDataSetMapper>::New();
	sphereMapper->SetInputConnection(pSTLReader->GetOutputPort());
	vtkSmartPointer<vtkActor> sphereActor =
		vtkSmartPointer<vtkActor>::New();
	sphereActor->SetMapper(sphereMapper);
	sphereActor->GetProperty()->SetEdgeColor(0, 0, 0);
	sphereActor->GetProperty()->EdgeVisibilityOn();

	vtkSmartPointer<vtkDataSetMapper> mainCellMapper =
		vtkSmartPointer<vtkDataSetMapper>::New();

	vtkSmartPointer<vtkDataSetMapper> neighborCellsMapper =
		vtkSmartPointer<vtkDataSetMapper>::New();

	// Create a dataset with the cell of interest
	{
		vtkSmartPointer<vtkIdTypeArray> ids =
			vtkSmartPointer<vtkIdTypeArray>::New();
		ids->SetNumberOfComponents(1);
		ids->InsertNextValue(cellId);

		vtkSmartPointer<vtkSelectionNode> selectionNode =
			vtkSmartPointer<vtkSelectionNode>::New();
		selectionNode->SetFieldType(vtkSelectionNode::CELL);
		selectionNode->SetContentType(vtkSelectionNode::INDICES);
		selectionNode->SetSelectionList(ids);

		vtkSmartPointer<vtkSelection> selection =
			vtkSmartPointer<vtkSelection>::New();
		selection->AddNode(selectionNode);

		vtkSmartPointer<vtkExtractSelection> extractSelection =
			vtkSmartPointer<vtkExtractSelection>::New();
		extractSelection->SetInputConnection(0, pSTLReader->GetOutputPort());
#if VTK_MAJOR_VERSION <= 5
		extractSelection->SetInput(1, selection);
#else
		extractSelection->SetInputData(1, selection);
#endif
		extractSelection->Update();

		mainCellMapper->SetInputConnection(extractSelection->GetOutputPort());

	}

	vtkSmartPointer<vtkActor> mainCellActor =
		vtkSmartPointer<vtkActor>::New();
	mainCellActor->SetMapper(mainCellMapper);
	mainCellActor->GetProperty()->SetColor(1, 0, 0);

	// Create a dataset with the neighbor cells
	{
		vtkSmartPointer<vtkIdTypeArray> ids =
			vtkSmartPointer<vtkIdTypeArray>::New();
		ids->SetNumberOfComponents(1);
		for (std::list<vtkIdType>::iterator it1 = neighbors.begin(); it1 != neighbors.end(); it1++)
		{
			ids->InsertNextValue(*it1);
		}

		vtkSmartPointer<vtkSelectionNode> selectionNode =
			vtkSmartPointer<vtkSelectionNode>::New();
		selectionNode->SetFieldType(vtkSelectionNode::CELL);
		selectionNode->SetContentType(vtkSelectionNode::INDICES);
		selectionNode->SetSelectionList(ids);

		vtkSmartPointer<vtkSelection> selection =
			vtkSmartPointer<vtkSelection>::New();
		selection->AddNode(selectionNode);

		vtkSmartPointer<vtkExtractSelection> extractSelection =
			vtkSmartPointer<vtkExtractSelection>::New();
		extractSelection->SetInputConnection(0, pSTLReader->GetOutputPort());
#if VTK_MAJOR_VERSION <= 5
		extractSelection->SetInput(1, selection);
#else
		extractSelection->SetInputData(1, selection);
#endif
		extractSelection->Update();

		neighborCellsMapper->SetInputConnection(extractSelection->GetOutputPort());

	}

	vtkSmartPointer<vtkActor> neighborCellsActor =
		vtkSmartPointer<vtkActor>::New();
	neighborCellsActor->SetMapper(neighborCellsMapper);
	neighborCellsActor->GetProperty()->SetColor(0, 1, 0);

	//Create a renderer, render window, and interactor
	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	//Add the actors to the scene
	renderer->AddActor(sphereActor);
	renderer->AddActor(mainCellActor);
	renderer->AddActor(neighborCellsActor);
	renderer->SetBackground(.3, .2, .1); // Background color dark red

	renderWindow->Render();
	renderWindowInteractor->Start();
}

void CvtkMFCDlgExDlg::OnBnClickedButtonExampleHolefilling()
{
	// <#0> 초기화 
	vtkSmartPointer<vtkRenderer> prevRenderer =
		m_vtkWindow->GetRenderers()->GetFirstRenderer();
	if (prevRenderer != NULL)
		m_vtkWindow->RemoveRenderer(prevRenderer);

	// <#1> STL Load
	vtkSmartPointer<vtkSTLReader> m_pSTLReader =
		vtkSmartPointer<vtkSTLReader>::New();
	m_pSTLReader->SetFileName("../data/(2019-05-02) [MeshDefect] Hole.stl");
	m_pSTLReader->Update();

	vtkSmartPointer<vtkNamedColors> colors =
		vtkSmartPointer<vtkNamedColors>::New();

	vtkSmartPointer<vtkFillHolesFilter> fillHolesFilter =
		vtkSmartPointer<vtkFillHolesFilter>::New();
	fillHolesFilter->SetInputData(m_pSTLReader->GetOutput());
	fillHolesFilter->SetHoleSize(100000.0);
	fillHolesFilter->Update();

	// Make the triangle winding order consistent
	vtkSmartPointer<vtkPolyDataNormals> normals =
		vtkSmartPointer<vtkPolyDataNormals>::New();
	normals->SetInputData(fillHolesFilter->GetOutput());
	normals->ConsistencyOn();
	normals->SplittingOff();
	normals->Update();

#if 0
	// Restore the original normals
	normals->GetOutput()->GetPointData()->
		SetNormals(input->GetPointData()->GetNormals());
#endif
	// Visualize
	// Define viewport ranges
	// (xmin, ymin, xmax, ymax)
	double leftViewport[4] = { 0.0, 0.0, 0.5, 1.0 };
	double rightViewport[4] = { 0.5, 0.0, 1.0, 1.0 };

	// Create a mapper and actor
	vtkSmartPointer<vtkPolyDataMapper> originalMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	originalMapper->SetInputData(m_pSTLReader->GetOutput());

	vtkSmartPointer<vtkProperty> backfaceProp =
		vtkSmartPointer<vtkProperty>::New();
	backfaceProp->SetDiffuseColor(colors->GetColor3d("Banana").GetData());

	vtkSmartPointer<vtkActor> originalActor =
		vtkSmartPointer<vtkActor>::New();
	originalActor->SetMapper(originalMapper);
	originalActor->SetBackfaceProperty(backfaceProp);
	originalActor->GetProperty()->SetDiffuseColor(
		colors->GetColor3d("Flesh").GetData());

	vtkSmartPointer<vtkPolyDataMapper> filledMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	filledMapper->SetInputData(fillHolesFilter->GetOutput());

	vtkSmartPointer<vtkActor> filledActor =
		vtkSmartPointer<vtkActor>::New();
	filledActor->SetMapper(filledMapper);
	filledActor->GetProperty()->SetDiffuseColor(
		colors->GetColor3d("Flesh").GetData());
	filledActor->SetBackfaceProperty(backfaceProp);

	// Create a renderer, render window, and interactor
	vtkSmartPointer<vtkRenderer> leftRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	leftRenderer->SetViewport(leftViewport);

	vtkSmartPointer<vtkRenderer> rightRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	rightRenderer->SetViewport(rightViewport);

	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->SetSize(800, 600);

	renderWindow->AddRenderer(leftRenderer);
	renderWindow->AddRenderer(rightRenderer);

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetInteractorStyle(
		vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New());
	renderWindowInteractor->SetRenderWindow(renderWindow);

	// Add the actor to the scene
	leftRenderer->AddActor(originalActor);
	rightRenderer->AddActor(filledActor);
	leftRenderer->SetBackground(colors->GetColor3d("PaleGreen").GetData());

	leftRenderer->GetActiveCamera()->SetPosition(0, -1, 0);
	leftRenderer->GetActiveCamera()->SetFocalPoint(0, 0, 0);
	leftRenderer->GetActiveCamera()->SetViewUp(0, 0, 1);
	leftRenderer->GetActiveCamera()->Azimuth(30);
	leftRenderer->GetActiveCamera()->Elevation(30);

	leftRenderer->ResetCamera();

	rightRenderer->SetBackground(colors->GetColor3d("LightGreen").GetData());

	// Share the camera

	rightRenderer->SetActiveCamera(leftRenderer->GetActiveCamera());
	// Render and interact
	renderWindow->Render();

	renderWindowInteractor->Start();
}

void CvtkMFCDlgExDlg::RenderingSTLFile(CString& strSTLPath)
{
	// <#0> 초기화 
	vtkSmartPointer<vtkRenderer> prevRenderer =
		m_vtkWindow->GetRenderers()->GetFirstRenderer();
	if (prevRenderer != NULL)
		m_vtkWindow->RemoveRenderer(prevRenderer);

	// <#1> STL Load
	vtkSmartPointer<vtkSTLReader> STLReader =
		vtkSmartPointer<vtkSTLReader>::New();
	STLReader->SetFileName(CT2A(strSTLPath));
	STLReader->Update();

	// <#2> STL을 PolyData로 변환 저장
	m_pPolyData = STLReader->GetOutput();

	// <#3> STL FaceCnt & VertexCnt 정보 반영
	SetGeneralInfo(m_pPolyData);

	// <#4> Mapper 만들기
	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(m_pPolyData);
	mapper->Update();

	// <#5> Actor 만들기
	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->SetEdgeColor(0, 0, 0);
	actor->GetProperty()->EdgeVisibilityOn();

	// <#6> Renderer 만들기
	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->SetBackground(.1, .2, .3);
	renderer->ResetCamera();
	m_vtkWindow->AddRenderer(renderer);

	// <#7> Interactor
	vtkSmartPointer<vtkRenderWindowInteractor> newIntoractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	newIntoractor->SetInteractorStyle(
		vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New());
	m_vtkWindow->SetInteractor(newIntoractor);

	// <#8> CallBack 함수 설정
	vtkSmartPointer<vtkCallbackCommand> mouseoverCallback =
		vtkSmartPointer<vtkCallbackCommand>::New();
	mouseoverCallback->SetCallback(cbMouseoverFace);
	mouseoverCallback->SetClientData(this);

	//m_vtkWindow->GetInteractor()->
	//	AddObserver(vtkCommand::MouseMoveEvent, mouseoverCallback);

	// <#9> 화면에 그리기
	m_vtkWindow->Render();
}

void CvtkMFCDlgExDlg::SetGeneralInfo(vtkPolyData* inputData,
	bool bIsInit)
{
	CString strFaceCnt;
	CString strVertexCnt;

	if (bIsInit == true)
	{
		strFaceCnt = _T("");
		GetDlgItem(IDC_Text_Face_Value)->SetWindowTextW(strFaceCnt);

		strVertexCnt = _T("");
		GetDlgItem(IDC_Text_Vertex_Value)->SetWindowTextW(strVertexCnt);
		return;
	}

	if (inputData == nullptr)
		return;

	strFaceCnt.Format(_T("%d"), inputData->GetNumberOfCells());
	GetDlgItem(IDC_Text_Face_Value)->SetWindowTextW(strFaceCnt);
	
	strVertexCnt.Format(_T("%d"), inputData->GetNumberOfPoints());
	GetDlgItem(IDC_Text_Vertex_Value)->SetWindowTextW(strVertexCnt);
}

void CvtkMFCDlgExDlg::GenerateNeighborList(OUT std::vector<vtkIdType>& vecOut,
	IN std::vector<vtkIdType>& vecIn, IN vtkSmartPointer<vtkTriangleFilter>& triangleFilter)
{
	for (std::vector<vtkIdType>::iterator iter = vecIn.begin(); iter != vecIn.end(); ++iter)
	{
		vtkIdType cellId = *(iter);

		vtkSmartPointer<vtkIdList> cellPointIds =
			vtkSmartPointer<vtkIdList>::New();
		// Get Vertex Ids From Face Id
		triangleFilter->GetOutput()->GetCellPoints(cellId, cellPointIds);

		for (vtkIdType i = 0; i < cellPointIds->GetNumberOfIds(); i++)
		{
			vtkSmartPointer<vtkIdList> idList =
				vtkSmartPointer<vtkIdList>::New();
			vtkIdType temp = cellPointIds->GetId(i);	// Vertex Id
			idList->InsertNextId(temp);

			//get the neighbors of the cell
			vtkSmartPointer<vtkIdList> neighborCellIds =
				vtkSmartPointer<vtkIdList>::New();

			triangleFilter->GetOutput()->GetCellNeighbors(cellId, idList,
				neighborCellIds);

			for (vtkIdType j = 0; j < neighborCellIds->GetNumberOfIds(); j++)
				vecOut.push_back(neighborCellIds->GetId(j));
		}
	}
}

void CvtkMFCDlgExDlg::Deduplication(std::vector<vtkIdType>& vec)
{
	std::sort(vec.begin(), vec.end());
	std::vector<vtkIdType>::iterator iter = std::unique(vec.begin(), vec.end());
	vec.erase(iter, vec.end());
}

void CvtkMFCDlgExDlg::GenerateNeighborRing(OUT std::vector<vtkIdType>& vecOut,
	IN std::vector<vtkIdType>& vecMax,
	IN std::vector<vtkIdType>& vecMin,
	IN std::vector<vtkIdType>& vecPickFace)
{
	std::vector<vtkIdType> vecRef = vecMin;
	vecRef.push_back(vecPickFace.at(0));
	for (std::vector<vtkIdType>::iterator iterMax = vecMax.begin(); iterMax != vecMax.end(); ++iterMax)
	{
		bool bIsSame = false;
		for (std::vector<vtkIdType>::iterator iterMin = vecRef.begin(); iterMin != vecRef.end(); ++iterMin)
		{
			if ((*iterMax) == (*iterMin))
			{
				bIsSame = true;
				break;
			}
		}

		if (bIsSame == false)
			vecOut.push_back((*iterMax));
	}
}

void CvtkMFCDlgExDlg::GenerateNeighborArea(OUT std::vector<vtkIdType>& vecOut,
	IN std::vector<vtkIdType>& vecMax,
	IN std::vector<vtkIdType>& vecPickFace)
{
	for (std::vector<vtkIdType>::iterator iterMax = vecMax.begin(); iterMax != vecMax.end(); ++iterMax)
	{
		if ((*iterMax) == vecPickFace.at(0))
			continue;
		
		vecOut.push_back((*iterMax));
	}
}

void CvtkMFCDlgExDlg::OnBnClickedBtnFillhole()
{
	// <#> Filter 설정
	vtkSmartPointer<vtkFillHolesFilter> fillHolesFilter =
		vtkSmartPointer<vtkFillHolesFilter>::New();
	fillHolesFilter->SetInputData(m_pPolyData);
	fillHolesFilter->SetHoleSize(100000.0);
	fillHolesFilter->Update();

	// Make the triangle winding order consistent
	auto normals = vtkSmartPointer<vtkPolyDataNormals>::New();
	normals->SetInputConnection(fillHolesFilter->GetOutputPort());
	normals->ConsistencyOn();
	normals->SplittingOff();
	normals->Update();
	normals->GetOutput()->GetPointData()->SetNormals(
		m_pPolyData->GetPointData()->GetNormals());


	//// Generate normals
	//vtkSmartPointer<vtkPolyDataNormals> normalGenerator = 
	//	vtkSmartPointer<vtkPolyDataNormals>::New();

	//normalGenerator->SetInputData(fillHolesFilter->GetOutput());
	//normalGenerator->ComputePointNormalsOff();
	//normalGenerator->ComputeCellNormalsOn();
	//normalGenerator->Update();

	// <#> Mapper 설정
	vtkSmartPointer<vtkPolyDataMapper> filledMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	filledMapper->SetInputData(fillHolesFilter->GetOutput());
	filledMapper->Update();

	vtkSmartPointer<vtkPolyDataMapper> normalMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	normalMapper->SetInputData(normals->GetOutput());
	normalMapper->Update();

	// <#> 색 설정
	vtkSmartPointer<vtkNamedColors> colors =
		vtkSmartPointer<vtkNamedColors>::New();

	// <#> original에서는 backFace가 맞으나, FillHole에서는 FilledFace 색상임.
	// FillHole에서 색상을 구분하기 위해 normal을 뒤짚어서 채운게 아닌지 확인해 봐야함.
	vtkSmartPointer<vtkProperty> backfaceProp =
		vtkSmartPointer<vtkProperty>::New();
	backfaceProp->SetDiffuseColor(colors->GetColor3d("red").GetData());

	// <#> Actor 설정
	vtkSmartPointer<vtkActor> filledActor =
		vtkSmartPointer<vtkActor>::New();
	filledActor->SetMapper(filledMapper);
	filledActor->SetBackfaceProperty(backfaceProp);
	filledActor->GetProperty()->SetDiffuseColor(
		colors->GetColor3d("white").GetData());
	filledActor->GetProperty()->SetEdgeColor(0, 0, 0);
	filledActor->GetProperty()->EdgeVisibilityOn();

	vtkSmartPointer<vtkActor> normalActor =
		vtkSmartPointer<vtkActor>::New();
	normalActor->SetMapper(normalMapper);
	//normalActor->GetProperty()->SetDiffuseColor(colors->GetColor3d("blue").GetData());

	// <#> Renderer 설정
	vtkSmartPointer<vtkRenderer> prevRenderer =
		m_vtkWindow->GetRenderers()->GetFirstRenderer();
	if (prevRenderer != NULL)
		m_vtkWindow->RemoveRenderer(prevRenderer);

	vtkSmartPointer<vtkRenderer> Renderer =
		vtkSmartPointer<vtkRenderer>::New();
	Renderer->AddActor(filledActor);
	//Renderer->AddActor(normalActor);
	Renderer->SetBackground(colors->GetColor3d("PaleGreen").GetData());
	m_vtkWindow->AddRenderer(Renderer);

	// <#> intoractor
	vtkSmartPointer<vtkRenderWindowInteractor> newIntoractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	newIntoractor->SetInteractorStyle(
		vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New());
	m_vtkWindow->SetInteractor(newIntoractor);

	// <#> 화면에 그리기
	m_vtkWindow->Render();

	// <#> m_pPolyData 변경해주기
	m_pPolyData = fillHolesFilter->GetOutput();
}
