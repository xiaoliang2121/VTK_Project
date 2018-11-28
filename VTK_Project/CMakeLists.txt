cmake_minimum_required(VERSION 2.8)

project(Chap02)

if(CMAKE_HOST_WIN32)
    # D:\3rdParty\VTK-Default\bin 运行环境path添加之前路径
    set(VTK_DIR "D:/3rdParty/VTK-Default/lib/cmake/vtk-6.3")
elseif(CMAKE_HOST_UNIX)
    # /home/xiaoliang/opt/3rdParty/vtk/lib 添加到 LD_LIBRARY_PATH
    set(VTK_DIR "/home/xiaoliang/opt/3rdParty/vtk/lib/cmake/vtk-6.3")
endif()

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} ${VTK_LIBRARIES})
