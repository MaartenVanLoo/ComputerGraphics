cmake_minimum_required(VERSION 3.17)
project(I_ComputerGraphics)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} C:/Program Files/opencv/build)

#find opencv
set ("OpenCV_DIR" "C:/Program Files/opencv/build")
set(OpenCV_STATIC ON)
find_package( OpenCV REQUIRED)# PATH C:/Program Files/opencv/build/ NO_DEFAULT_PATH )
include_directories( ${OpenCV_INCLUDE_DIRS} )


set(ProjectSourceFiles
        ${CMAKE_SOURCE_DIR}/src/Ray.cpp
        ${CMAKE_SOURCE_DIR}/src/LinearAlgebra/Vector.cpp
        ${CMAKE_SOURCE_DIR}/src/Objects/Object.cpp
        ${CMAKE_SOURCE_DIR}/src/Objects/Sphere.cpp
        ${CMAKE_SOURCE_DIR}/src/Objects/Box.cpp
        ${CMAKE_SOURCE_DIR}/src/Objects/Plane.cpp
        ${CMAKE_SOURCE_DIR}/src/Camera/Camera.cpp
        ${CMAKE_SOURCE_DIR}/src/Scene/Scene.cpp
        ${CMAKE_SOURCE_DIR}/src/Camera/CameraUtils.cpp
        ${CMAKE_SOURCE_DIR}/src/Screen/Screen.cpp
        ${CMAKE_SOURCE_DIR}/src/Transform/Transform.cpp
        ${CMAKE_SOURCE_DIR}/src/LinearAlgebra/Matrix.cpp
        ${CMAKE_SOURCE_DIR}/src/Light/Light.cpp
        ${CMAKE_SOURCE_DIR}/src/Light/PointLight.cpp
        ${CMAKE_SOURCE_DIR}/src/Light/Color3.cpp
        ${CMAKE_SOURCE_DIR}/src/Utils/Intersection.cpp)
add_subdirectory(tests)

set(CMAKE_CXX_STANDARD 17)


#resource files
set (APP_ICON_RESOURCE_WINDOWS "resources.rc" include/Light/LightCore.h)


add_executable(I_ComputerGraphics main.cpp ${ProjectSourceFiles} ${APP_ICON_RESOURCE_WINDOWS})
target_include_directories(I_ComputerGraphics PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries( I_ComputerGraphics PRIVATE  ${OpenCV_LIBS} )
#target_link_options(I_ComputerGraphics PRIVATE /nodefaultlib)

#Optimization flags
message("Build type: ${CMAKE_BUILD_TYPE}")
if (CMAKE_BUILD_TYPE MATCHES "Release")
    target_compile_options(I_ComputerGraphics  PRIVATE
            $<$<CXX_COMPILER_ID:MSVC>:/W3 /WX- /Oi /Ot /O2 /Zi /GL /MP>
            $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -O3>)
    target_link_options(I_ComputerGraphics PRIVATE "$<$<CONFIG:Release>:/DEBUG>")
    target_link_options(I_ComputerGraphics PRIVATE "$<$<CONFIG:Release>:/OPT:REF>")
    target_link_options(I_ComputerGraphics PRIVATE "$<$<CONFIG:Release>:/OPT:ICF>")
    target_link_options(I_ComputerGraphics PRIVATE "$<$<CONFIG:Release>:/LTCG>")

    #enable profiling option for visual studio
    SET_TARGET_PROPERTIES(I_ComputerGraphics PROPERTIES LINK_FLAGS "/PROFILE")
    SET_TARGET_PROPERTIES(I_ComputerGraphics PROPERTIES LINK_FLAGS "/DEBUG")
endif()

#override the AVX.h file to use AVX
#target_compile_definitions(I_ComputerGraphics PUBLIC SSE_AVX_EXTENSIONS=true)


