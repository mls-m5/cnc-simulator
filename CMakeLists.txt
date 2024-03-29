
cmake_minimum_required(VERSION 3.16)
project(cnc-sim)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(
    cnc-sim
    src/main.cpp
    src/makebottle.cpp
    src/viewer.cpp
    src/step.cpp
    src/assembly.cpp
    )

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})

# Find Open CASCADE package (assumes that OCCT_DIR is set)
find_package(OpenCASCADE REQUIRED)

# Include directories for Open CASCADE
include_directories(${OpenCASCADE_INCLUDE_DIR})

file(
    COPY data
    DESTINATION .
)

target_compile_features(
    cnc-sim
    PRIVATE
    cxx_std_17
    )

find_package(Threads)
target_link_libraries(
    cnc-sim
    PRIVATE
    ${CMAKE_THREAD_LIBS_INIT}
    TKernel TKGeomBase TKPrim TKSTEP TKSTEPBase TKSTEPAttr TKSTEP209

    TKernel TKGeomBase TKPrim TKBool TKBO TKFillet TKOffset TKTopAlgo TKShHealing TKG3d TKG2d TKBRep

    TKernel TKGeomBase TKPrim TKSTEP TKSTEPBase TKSTEPAttr TKSTEP209
    TKernel TKGeomBase TKPrim TKBool TKBO TKFillet TKOffset TKTopAlgo TKShHealing TKG3d TKG2d TKBRep
    TKV3d TKService TKOpenGl
    # Add X11 libraries if needed
    ${X11_LIBRARIES}

    Qt5::Widgets
    )
