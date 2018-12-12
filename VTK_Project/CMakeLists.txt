cmake_minimum_required(VERSION 2.8)

project(Chap01)

if(CMAKE_HOST_WIN32)
    set(VTK_DIR "D:/3rdParty/VTK-Default/lib/cmake/vtk-6.3")
elseif(CMAKE_HOST_UNIX)
    # ~/opt/3rdParty/vtk/vtk_8.1.2/lib
    set(VTK_DIR "~/opt/3rdParty/vtk/vtk_8.1.2/lib/cmake/vtk-8.1")
endif()

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} ${VTK_LIBRARIES})
