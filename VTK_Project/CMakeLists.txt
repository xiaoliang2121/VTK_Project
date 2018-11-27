cmake_minimum_required(VERSION 2.8)

project(Chap01)

set(VTK_DIR "D:/3rdParty/VTK-Default/lib/cmake/vtk-6.3")
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(${PROJECT_NAME} "1.3_TestVTKInstall.cpp")
target_link_libraries(${PROJECT_NAME} ${VTK_LIBRARIES})
