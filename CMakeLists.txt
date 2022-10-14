cmake_minimum_required(VERSION 3.17)
project(I_ComputerGraphics)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} C:/Program Files/opencv/build)

#find opencv
set ("OpenCV_DIR" "C:/Program Files/opencv/build")
set(OpenCV_STATIC ON)
find_package( OpenCV REQUIRED)# PATH C:/Program Files/opencv/build/ NO_DEFAULT_PATH )
include_directories( ${OpenCV_INCLUDE_DIRS} )
link_directories(${CMAKE_BINARY_DIR}/lib)

set(CMAKE_CXX_STANDARD 17)

#resource files
set (APP_ICON_RESOURCE_WINDOWS "resources.rc" include/Textures/Checkerboard.h include/Textures/Texture.h src/Render/RenderEngine.cpp)

add_library(MRay STATIC)
set_target_properties(MRay PROPERTIES CXX_STANDARD 17)
target_include_directories(MRay PUBLIC ${CMAKE_SOURCE_DIR}/include)
add_subdirectory(src)


add_executable(I_ComputerGraphics main.cpp ${APP_ICON_RESOURCE_WINDOWS})
target_include_directories(I_ComputerGraphics PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(I_ComputerGraphics PRIVATE ${OpenCV_LIBS})
target_link_libraries(I_ComputerGraphics PRIVATE MRay)
set_target_properties(I_ComputerGraphics PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/$<CONFIG>)

add_subdirectory(tests)
#Optimization flags
message("Build type: ${CMAKE_BUILD_TYPE}")
if (CMAKE_BUILD_TYPE MATCHES "Release" OR CMAKE_BUILD_TYPE MATCHES "RelWithDebInfo ")
    target_compile_options(MRay  PRIVATE
            $<$<CXX_COMPILER_ID:MSVC>:/W3 /WX- /Oi /Ot /O2 /Zi /GL /MP>
            $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -O3>)
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

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

#override the AVX.h file to use AVX
#target_compile_definitions(I_ComputerGraphics PUBLIC SSE_AVX_EXTENSIONS=true)


