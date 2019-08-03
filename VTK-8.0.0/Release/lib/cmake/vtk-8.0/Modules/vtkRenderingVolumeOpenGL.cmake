set(vtkRenderingVolumeOpenGL_LOADED 1)
set(vtkRenderingVolumeOpenGL_DEPENDS "vtkCommonCore;vtkCommonDataModel;vtkCommonMath;vtkCommonSystem;vtkCommonTransforms;vtkFiltersCore;vtkFiltersGeneral;vtkFiltersGeometry;vtkFiltersSources;vtkImagingCore;vtkRenderingCore;vtkRenderingOpenGL;vtkRenderingVolume;vtkRenderingVolume;vtksys")
set(vtkRenderingVolumeOpenGL_LIBRARIES "vtkRenderingVolumeOpenGL")
set(vtkRenderingVolumeOpenGL_INCLUDE_DIRS "${VTK_INSTALL_PREFIX}/include/vtk-8.0")
set(vtkRenderingVolumeOpenGL_LIBRARY_DIRS "")
set(vtkRenderingVolumeOpenGL_RUNTIME_LIBRARY_DIRS "${VTK_INSTALL_PREFIX}/bin")
set(vtkRenderingVolumeOpenGL_WRAP_HIERARCHY_FILE "${CMAKE_CURRENT_LIST_DIR}/vtkRenderingVolumeOpenGLHierarchy.txt")
set(vtkRenderingVolumeOpenGL_KIT "vtkOpenGL")
set(vtkRenderingVolumeOpenGL_IMPLEMENTS "vtkRenderingVolume")


