set(vtkRenderingContextOpenGL_LOADED 1)
set(vtkRenderingContextOpenGL_DEPENDS "vtkCommonCore;vtkCommonDataModel;vtkCommonMath;vtkCommonTransforms;vtkRenderingContext2D;vtkRenderingContext2D;vtkRenderingCore;vtkRenderingFreeType;vtkRenderingOpenGL")
set(vtkRenderingContextOpenGL_LIBRARIES "vtkRenderingContextOpenGL")
set(vtkRenderingContextOpenGL_INCLUDE_DIRS "${VTK_INSTALL_PREFIX}/include/vtk-8.0")
set(vtkRenderingContextOpenGL_LIBRARY_DIRS "")
set(vtkRenderingContextOpenGL_RUNTIME_LIBRARY_DIRS "${VTK_INSTALL_PREFIX}/bin")
set(vtkRenderingContextOpenGL_WRAP_HIERARCHY_FILE "${CMAKE_CURRENT_LIST_DIR}/vtkRenderingContextOpenGLHierarchy.txt")
set(vtkRenderingContextOpenGL_KIT "vtkOpenGL")
set(vtkRenderingContextOpenGL_IMPLEMENTS "vtkRenderingContext2D")


