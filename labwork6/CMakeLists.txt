cmake_minimum_required(VERSION 3.16)
project(labwork6 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets PrintSupport)

# Find FFTW3
find_library(FFTW3_LIB fftw3 HINTS /opt/homebrew/opt/fftw/lib)
find_path(FFTW3_INCLUDE fftw3.h HINTS /opt/homebrew/opt/fftw/include)

add_executable(labwork6
    main.cpp
    spectrum_window.cpp
    fft_processor.cpp
    ../labwork5/fourier_params.cpp
    ../labwork4/complex_array.cpp
    qcustomplot.cpp
    spectrum_window.ui
)

target_include_directories(labwork6 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${FFTW3_INCLUDE}
)

target_link_libraries(labwork6 PRIVATE
    Qt6::Widgets
    Qt6::PrintSupport
    ${FFTW3_LIB}
)
