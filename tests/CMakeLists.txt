cmake_minimum_required(VERSION 3.17)
project(I_ComputerGraphics_tests)
find_package(Catch2 3 REQUIRED)


set(testSources
        ${CMAKE_CURRENT_SOURCE_DIR}/Objects/TSphere.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Objects/TBox.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Camera/TCamera.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Transform/TTransform.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinearAlgebra/TVector.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinearAlgebra/TMatrix.cpp)

add_executable(I_ComputerGraphics_tests tests.cpp ${ProjectSourceFiles} ${testSources})
target_include_directories(I_ComputerGraphics_tests PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(I_ComputerGraphics_tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries( I_ComputerGraphics_tests PRIVATE  ${OpenCV_LIBS} )