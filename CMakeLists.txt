cmake_minimum_required(VERSION 3.17)
project(I_ComputerGraphics)

set(ProjectSourceFiles
        ${CMAKE_SOURCE_DIR}/src/Ray.cpp
        ${CMAKE_SOURCE_DIR}/src/Vector.cpp
        ${CMAKE_SOURCE_DIR}/src/Objects/Sphere.cpp
        ${CMAKE_SOURCE_DIR}/src/Objects/Box.cpp
        ${CMAKE_SOURCE_DIR}/src/Camera/Camera.cpp
        ${CMAKE_SOURCE_DIR}/src/Scene/Scene.cpp
        ${CMAKE_SOURCE_DIR}/src/Camera/CameraUtils.cpp
        )
add_subdirectory(tests)

set(CMAKE_CXX_STANDARD 17)

add_executable(I_ComputerGraphics main.cpp ${ProjectSourceFiles})
target_include_directories(I_ComputerGraphics PUBLIC ${CMAKE_SOURCE_DIR}/include)