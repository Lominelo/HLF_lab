cmake_minimum_required(VERSION 3.16)
project(labwork4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(labwork4
    main.cpp
    real_matrix.cpp
    complex_array.cpp
)

# Optional: FFTW3
set(FFTW3_ROOT "C:/lib/fftw64")
find_library(FFTW3_LIB NAMES fftw3-3 libfftw3-3 PATHS ${FFTW3_ROOT})
find_path(FFTW3_INCLUDE fftw3.h PATHS ${FFTW3_ROOT})
if(FFTW3_LIB AND FFTW3_INCLUDE)
    message(STATUS "FFTW3 found: ${FFTW3_LIB}")
    target_include_directories(labwork4 PRIVATE ${FFTW3_INCLUDE})
    target_link_libraries(labwork4 PRIVATE ${FFTW3_LIB})
    target_compile_definitions(labwork4 PRIVATE FFTW_AVAILABLE)
else()
    message(STATUS "FFTW3 not found — building without FFT support")
endif()

# Optional: Boost
set(BOOST_ROOT "C:/lib/boost_1_90_0")
find_package(Boost)
if(Boost_FOUND)
    message(STATUS "Boost found: ${Boost_INCLUDE_DIRS}")
    target_include_directories(labwork4 PRIVATE ${Boost_INCLUDE_DIRS})
    target_compile_definitions(labwork4 PRIVATE BOOST_AVAILABLE)
else()
    message(STATUS "Boost not found — building without Boost support")
endif()
