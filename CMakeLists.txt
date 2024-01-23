
cmake_minimum_required(VERSION 3.23)
project(nc-sim)

add_executable(
    nc-sim
    src/main.cpp
    src/makebottle.cpp
    src/showwindow.cpp
    )


set(OpenCASCADE_DIR "/usr/local/lib/cmake/")


# Find Open CASCADE package (assumes that OCCT_DIR is set)
find_package(OpenCASCADE REQUIRED)

# Include directories for Open CASCADE
include_directories(${OpenCASCADE_INCLUDE_DIR})

target_compile_features(
    nc-sim
    PRIVATE
    cxx_std_17
    )

find_package(Threads)
target_link_libraries(
    nc-sim
    PRIVATE
    ${CMAKE_THREAD_LIBS_INIT}
    TKernel TKGeomBase TKPrim TKSTEP TKSTEPBase TKSTEPAttr TKSTEP209

    TKernel TKGeomBase TKPrim TKBool TKBO TKFillet TKOffset TKTopAlgo TKShHealing TKG3d TKG2d TKBRep
    )
