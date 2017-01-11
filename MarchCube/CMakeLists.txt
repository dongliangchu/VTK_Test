cmake_minimum_required(VERSION 2.8.9)
project (MarchCube)
find_package(VTK REQUIRED) # /apps/visit/thirdparty/VTK-6.1.0-build)

#find_package(ADIOS REQUIRED PATHS /apps/adios/etc)
set(VTK_Modules
  vtkCommonCore
  vtkFiltersSources
  vtkIOInfovis
  vtkIOSQL
  vtkInfovisLayout
  vtkInteractionStyle
  vtkRenderingLabel
  vtkViewsInfovis
)
vtk_module_config(VTK
  ${VTK_Modules}
  vtkRendering${VTK_RENDERING_BACKEND}
)
include(${VTK_USE_FILE})
#find_package(OpenMP REQUIRED)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")

add_executable(MarchCubeDemo MACOSX_BUNDLE MarchCubeDemo.cxx)
#add_executable(choppy choppy.C)
#add_executable(pmerge pmerge.C)
#add_executable(makeB makeB.C)
#add_executable(decimate MACOSX_BUNDLE decimate.C)

include_directories(${VTK_INCLUDE_DIRS})
link_directories(${VTK_LIBRARY_DIRS})
target_link_libraries(MarchCubeDemo ${VTK_LIBRARY} vtkIOCore vtkIOLegacy vtkFiltersCore)

