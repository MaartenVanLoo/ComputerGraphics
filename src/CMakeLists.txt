target_sources(MRay
        PUBLIC
        Ray.cpp
        )
#[[target_sources(I_ComputerGraphics
        PUBLIC
        Ray.cpp
        )]]

add_subdirectory(Camera)
add_subdirectory(Light)
add_subdirectory(LinearAlgebra)
add_subdirectory(Materials)
add_subdirectory(Objects)
add_subdirectory(Render)
add_subdirectory(Scene)
add_subdirectory(Screen)
add_subdirectory(Textures)
add_subdirectory(Transform)
add_subdirectory(Utils)

set_target_properties(MRay
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/$<CONFIG>
        PDB_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/$<CONFIG>)

if (CMAKE_BUILD_TYPE MATCHES "Release")
    target_compile_options(MRay  PRIVATE
            $<$<CXX_COMPILER_ID:MSVC>:/W3 /WX- /Oi /Ot /O2 /Zi /GL /MP>
            $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -O3>)
    target_link_options(MRay PRIVATE "$<$<CONFIG:Release>:/DEBUG>")
    target_link_options(MRay PRIVATE "$<$<CONFIG:Release>:/OPT:REF>")
    target_link_options(MRay PRIVATE "$<$<CONFIG:Release>:/OPT:ICF>")
    target_link_options(MRay PRIVATE "$<$<CONFIG:Release>:/LTCG>")

    #enable profiling option for visual studio
    SET_TARGET_PROPERTIES(MRay PROPERTIES LINK_FLAGS "/PROFILE")
    SET_TARGET_PROPERTIES(MRay PROPERTIES LINK_FLAGS "/DEBUG")
endif()

