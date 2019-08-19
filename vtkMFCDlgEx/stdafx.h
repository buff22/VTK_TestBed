
// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������ 
// ��� �ִ� ���� �����Դϴ�.

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // �Ϻ� CString �����ڴ� ��������� ����˴ϴ�.

// MFC�� ���� �κа� ���� ������ ��� �޽����� ���� ����⸦ �����մϴ�.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC �ٽ� �� ǥ�� ���� ����Դϴ�.
#include <afxext.h>         // MFC Ȯ���Դϴ�.


#include <afxdisp.h>        // MFC �ڵ�ȭ Ŭ�����Դϴ�.



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC�� ���� �� ��Ʈ�� ���� ����









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


// vtk header
#include <vtkAutoInit.h>
#define vtkRenderingCore_AUTOINIT \
4(vtkRenderingOpenGL,vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingContextOpenGL)
#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL)

// <#> VTK Header
#include <vtkSmartPointer.h>
#include <vtkCamera.h>
//#include <vtkLight.h>	// ���� Light ��� ���ϰ� ���� (2019-08-20)

#include <vtkSTLReader.h>
//#include <vtkSTLWriter.h>	// ���� Hole ���� STL ���� ��� �ʿ�
#include <vtkPolyData.h>

#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>

// call back
#include <vtkCallbackCommand.h>
#include <vtkRendererCollection.h>
#include <vtkCellPicker.h>

// neighbor
#include <vtkProperty.h>

// Fill Hole
#include <vtkPolyDataNormals.h>



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
#include <vtkIdTypeArray.h>
#include <vtkCommand.h>
#include <vtkPlaneSource.h>
#include <vtkObjectFactory.h>
#include <vtkDataObject.h>
#include <vtkNamedColors.h>
#include <vtkFillHolesFilter.h>