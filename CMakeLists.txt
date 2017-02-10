# Make command:
# /opt/local/bin/cmake -DVTK_DIR:PATH=/Users/dillon/Downloads/VTK-build/ .

cmake_minimum_required(VERSION 2.8)
 
PROJECT(trimesh)

SET(EXTRA_CXX_COMPILE_FLAGS "-std=c++11 -I./src -I./test -I/opt/local/include -O2")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${EXTRA_CXX_COMPILE_FLAGS}")
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(trimesh MACOSX_BUNDLE main parse_stl)
 
if(VTK_LIBRARIES)
  target_link_libraries(trimesh ${VTK_LIBRARIES})
else()
  target_link_libraries(trimesh vtkHybrid vtkWidgets)
endif()
