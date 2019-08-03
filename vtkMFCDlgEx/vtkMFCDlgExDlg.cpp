
// vtkMFCDlgExDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "vtkMFCDlgEx.h"
#include "vtkMFCDlgExDlg.h"
#include "afxdialogex.h"

#include <vtkRendererCollection.h>
#include <vtkCamera.h>
#include <vtkLight.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkArrowSource.h>
#include <vtkSTLReader.h>
#include <vtkSTLWriter.h>
#include <vtkProperty.h>
#include <vtkCleanPolyData.h>
#include <vtkPolyDataNormals.h>
#include <vtkDecimatePro.h>
#include <vtkQuadricClustering.h>
#include <vtkWindowedSincPolyDataFilter.h>
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkPlane.h>
#include <vtkClipPolyData.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkLandmarkTransform.h>
#include <vtkIterativeClosestPointTransform.h>
#include <vtkFileOutputWindow.h>
#include <vtkDICOMImageReader.h>
#include <vtkImageViewer2.h>
#include <vtkMarchingCubes.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkVolumeProperty.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkVolume.h>
#include <vtkExtractVOI.h>
#include <vtkImageData.h>
#include <vtkCallbackCommand.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCellPicker.h>
#include <vtkCaptionActor2D.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <vtkAnnotatedCubeActor.h>

// Test
#include <vtkSphereSource.h>
#include <vtkTriangleFilter.h>
#include <list>
#include <vtkDataSetMapper.h>
#include <vtkSelectionNode.h>
#include <vtkSelection.h>
#include <vtkExtractSelection.h>
#include <vtkAlgorithmOutput.h>
#include <vtkUnstructuredGrid.h>
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkRendererCollection.h>
#include <vtkDataSetMapper.h>
#include <vtkUnstructuredGrid.h>
#include <vtkIdTypeArray.h>
#include <vtkTriangleFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCommand.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPlaneSource.h>
#include <vtkCellPicker.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkProperty.h>
#include <vtkSelectionNode.h>
#include <vtkSelection.h>
#include <vtkExtractSelection.h>
#include <vtkObjectFactory.h>
#include <vtkDataObject.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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

// CvtkMFCDlgExDlg ��ȭ ����
CvtkMFCDlgExDlg::CvtkMFCDlgExDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CvtkMFCDlgExDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

BEGIN_MESSAGE_MAP(CvtkMFCDlgExDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CvtkMFCDlgExDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_START2, &CvtkMFCDlgExDlg::OnBnClickedButtonStart2)
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CvtkMFCDlgExDlg::OnBnClickedButtonTest)
	ON_BN_CLICKED(IDC_BUTTON_EXAMPLE_HOLEFILLING, &CvtkMFCDlgExDlg::OnBnClickedButtonExampleHolefilling)
END_MESSAGE_MAP()

// CvtkMFCDlgExDlg �޽��� ó����
BOOL CvtkMFCDlgExDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	if (this->GetDlgItem(IDC_STATIC_FRAME))
	{
		this->InitVtkWindow(this->GetDlgItem(IDC_STATIC_FRAME)->GetSafeHwnd());	// Initialize VTK window
		this->ResizeVtkWindow();
	}

	// Warning Off
	vtkObject::GlobalWarningDisplayOff();

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.
void CvtkMFCDlgExDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

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
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
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
	// vtk Render Window ����
	if (m_vtkWindow == NULL)
	{
		// Interactor ����
		vtkSmartPointer<vtkRenderWindowInteractor> interactor =
			vtkSmartPointer<vtkRenderWindowInteractor>::New();
		// Trackball Camera ���ͷ��� ��Ÿ�� ����
		interactor->SetInteractorStyle(
			vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New());

		// Renderer ����
		vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
		renderer->SetBackground(0.0, 0.0, 0.0);		// ������ ���

		// RenderWindow ���� �� Dialog �ڵ�, Renderer ����
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

void PickCallbackFunction(vtkObject* caller, long unsigned int eventId,
	void* clientData, void* callData)
{
	// Interactor ��������
	vtkSmartPointer<vtkRenderWindowInteractor> interactor = 
		vtkRenderWindowInteractor::SafeDownCast(caller);
	if (interactor == NULL)
		return;

	// ���콺 Ŭ�� ��ġ
	int pos[2];
	interactor->GetLastEventPosition(pos);

	// ���콺 Ŭ�� ��ġ���� Picking ����
	vtkSmartPointer<vtkCellPicker> picker =
		vtkSmartPointer<vtkCellPicker>::New();
	picker->SetTolerance(0.005);		// picking ���� ����
	picker->Pick(pos[0], pos[1], 0,
		interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());

	vtkIdType cellId = picker->GetCellId();	// -1�̸� picking ���� ����
	if (cellId != -1)
		MessageBox(NULL, _T("Pick Event"), _T("Pop-up"), MB_OK);
}

void PickCallbackFunction2(vtkObject* caller, long unsigned int eventId,
	void* clientData, void* callData)
{
	// Interactor ��������
	vtkSmartPointer<vtkRenderWindowInteractor> interactor =
		vtkRenderWindowInteractor::SafeDownCast(caller);
	if (interactor == NULL)
		return;

	// ���콺 Ŭ�� ��ġ
	int pos[2];
	interactor->GetLastEventPosition(pos);

	// ���콺 Ŭ�� ��ġ���� Picking ����
	vtkSmartPointer<vtkCellPicker> picker =
		vtkSmartPointer<vtkCellPicker>::New();
	picker->SetTolerance(0.005);		// picking ���� ����
	picker->Pick(pos[0], pos[1], 0,
		interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());

	// cellId1 = Face Idx
	vtkIdType cellId1 = picker->GetCellId();	// -1�̸� picking ���� ����
	if (cellId1 != -1)
	{
		vtkSmartPointer<vtkRenderWindowInteractor> itr =
		reinterpret_cast<vtkRenderWindowInteractor*>(caller);

		vtkSmartPointer<vtkRenderer> renderer =
		itr->GetRenderWindow()->GetRenderers()->GetFirstRenderer();

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

		// Find all cells connected to point 0
		vtkIdType cellId = cellId1;

		vtkSmartPointer<vtkIdList> cellPointIds =
			vtkSmartPointer<vtkIdList>::New();
		// Get Vertex Ids From Face Id
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
			vtkIdType temp = cellPointIds->GetId(i);	// Vertex Id
			idList->InsertNextId(temp);
		
			//get the neighbors of the cell
			vtkSmartPointer<vtkIdList> neighborCellIds =
				vtkSmartPointer<vtkIdList>::New();

			triangleFilter->GetOutput()->GetCellNeighbors(cellId, idList, 
														  neighborCellIds);

			for (vtkIdType j = 0; j < neighborCellIds->GetNumberOfIds(); j++)
				neighbors.push_back(neighborCellIds->GetId(j));
		}

		OutputDebugString(L"\n Point neighbor ids are: ");
		for (std::list<vtkIdType>::iterator it1 = neighbors.begin(); it1 != neighbors.end(); it1++)
		{
			CString strDebug;
			strDebug.Format(L" %d", *it1);
			::OutputDebugString(strDebug);
		}
		OutputDebugString(L"\n");

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
			extractSelection->SetInputConnection(0, triangleFilter->GetOutputPort());
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
			extractSelection->SetInputConnection(0, triangleFilter->GetOutputPort());
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

		//Add the actors to the scene
		renderer->RemoveAllViewProps();
		renderer->AddActor(actor);
		renderer->AddActor(mainCellActor);
		renderer->AddActor(neighborCellsActor);
		renderer->SetBackground(.3, .2, .1); // Background color dark red

		itr->GetRenderWindow()->Render();
	}
}

void CvtkMFCDlgExDlg::OnBnClickedButtonStart()
{
	// <#0> �ʱ�ȭ 
	vtkSmartPointer<vtkRenderer> prevRenderer = m_vtkWindow->GetRenderers()->GetFirstRenderer();
	if (prevRenderer != NULL)
		m_vtkWindow->RemoveRenderer(prevRenderer);

	// <#1> STL Load
	vtkSmartPointer<vtkSTLReader> m_pSTLReader = vtkSmartPointer<vtkSTLReader>::New();
	m_pSTLReader->SetFileName("../data/cast3br.stl");
	m_pSTLReader->Update();

	// <#2> STL�� PolyData�� ��ȯ ����
	m_pPolyData = m_pSTLReader->GetOutput();

	// <#3> Mapper �����
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(m_pPolyData);

	// <#4> Actor �����
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->SetEdgeColor(0, 0, 0);
	actor->GetProperty()->EdgeVisibilityOn();

	// <#5> Renderer �����
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->SetBackground(.1, .2, .3);
	renderer->ResetCamera();

	// <#6> ȭ�鿡 �׸���
	m_vtkWindow->AddRenderer(renderer);
	m_vtkWindow->Render();
}

void CvtkMFCDlgExDlg::OnBnClickedButtonStart2()
{
	// <#0> �ʱ�ȭ 
	vtkSmartPointer<vtkRenderer> prevRenderer = 
		m_vtkWindow->GetRenderers()->GetFirstRenderer();
	if (prevRenderer != NULL)
		m_vtkWindow->RemoveRenderer(prevRenderer);

	// <#1> STL Load
	vtkSmartPointer<vtkSTLReader> m_pSTLReader = 
		vtkSmartPointer<vtkSTLReader>::New();
	m_pSTLReader->SetFileName("../data/cast3br.stl");
	m_pSTLReader->Update();

	// <#2> STL�� PolyData�� ��ȯ ����
	m_pPolyData = m_pSTLReader->GetOutput();
	//vtkPolyData* temp = m_pSTLReader->GetOutput();

	// <#3> Mapper �����
	vtkSmartPointer<vtkPolyDataMapper> mapper = 
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(m_pPolyData);
	
	// <#4> Actor �����
	vtkSmartPointer<vtkActor> actor = 
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->SetEdgeColor(0, 0, 0);
	actor->GetProperty()->EdgeVisibilityOn();

	// <#5> Renderer �����
	vtkSmartPointer<vtkRenderer> renderer = 
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->SetBackground(.1, .2, .3);
	renderer->ResetCamera();

	// <#6> ȭ�鿡 �׸���
	m_vtkWindow->AddRenderer(renderer);
	m_vtkWindow->Render();

	// <#7> CallBack �Լ� ����
	vtkSmartPointer<vtkCallbackCommand> pickCallback = 
		vtkSmartPointer<vtkCallbackCommand>::New();
	pickCallback->SetCallback(PickCallbackFunction2);

	// <#8> Interactor ����
	m_vtkWindow->GetInteractor()->
		AddObserver(vtkCommand::LeftButtonPressEvent, pickCallback);
}

void CvtkMFCDlgExDlg::OnBnClickedButtonTest()
{
	// <#0> �ʱ�ȭ 
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

										 //Render and interact
	renderWindow->Render();
	renderWindowInteractor->Start();
}

void CvtkMFCDlgExDlg::OnBnClickedButtonExampleHolefilling()
{
	// TODO: Add your control notification handler code here
}
