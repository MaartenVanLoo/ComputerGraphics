cmake_minimum_required(VERSION 3.17)
project(I_ComputerGraphics)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} C:/Program Files/opencv/build)

#find opencv
set (OpenCV_DIR C:/Program Files/opencv/build/x64/vs15)
set(OpenCV_STATIC ON)
find_package( OpenCV REQUIRED)# PATH C:/Program Files/opencv/build/ NO_DEFAULT_PATH )
include_directories( ${OpenCV_INCLUDE_DIRS} )


set(ProjectSourceFiles
        ${CMAKE_SOURCE_DIR}/src/Ray.cpp
        ${CMAKE_SOURCE_DIR}/src/Vector.cpp
        ${CMAKE_SOURCE_DIR}/src/Objects/Sphere.cpp
        ${CMAKE_SOURCE_DIR}/src/Objects/Box.cpp
        ${CMAKE_SOURCE_DIR}/src/Camera/Camera.cpp
        ${CMAKE_SOURCE_DIR}/src/Scene/Scene.cpp
        ${CMAKE_SOURCE_DIR}/src/Camera/CameraUtils.cpp
        ${CMAKE_SOURCE_DIR}/src/Screen/Screen.cpp
        ${CMAKE_SOURCE_DIR}/src/Transform/Transform.cpp
        ${CMAKE_SOURCE_DIR}/src/Matrix.cpp
        )
add_subdirectory(tests)

set(CMAKE_CXX_STANDARD 17)


#resource files
set (APP_ICON_RESOURCE_WINDOWS "resources.rc")


add_executable(I_ComputerGraphics main.cpp ${ProjectSourceFiles} ${APP_ICON_RESOURCE_WINDOWS})
target_include_directories(I_ComputerGraphics PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries( I_ComputerGraphics PRIVATE  ${OpenCV_LIBS} )
#target_link_options(I_ComputerGraphics PRIVATE /nodefaultlib)