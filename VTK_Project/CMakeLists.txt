cmake_minimum_required(VERSION 2.8)

project(Chap02)

# D:\3rdParty\VTK-Default\bin 运行环境path添加之前路径
set(VTK_DIR "D:/3rdParty/VTK-Default/lib/cmake/vtk-6.3")
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} ${VTK_LIBRARIES})
