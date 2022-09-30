cmake_minimum_required(VERSION 3.17)
project(I_ComputerGraphics_tests)
find_package(Catch2 3 REQUIRED)

add_executable(I_ComputerGraphics_tests tests.cpp ${ProjectSourceFiles} Objects/TSphere.cpp)
target_include_directories(I_ComputerGraphics_tests PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(I_ComputerGraphics_tests PRIVATE Catch2::Catch2WithMain)