cmake_minimum_required(VERSION 3.16)
project(labwork8 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

# Unit tests (no Qt needed)
add_executable(run_tests
    tests.cpp
    ../labwork4/real_matrix.cpp
    ../labwork4/complex_array.cpp
    ../labwork5/fourier_params.cpp
)
target_include_directories(run_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)

set(FFTW3_ROOT "C:/lib/fftw64")   # или ваш путь
find_library(FFTW3_LIB NAMES fftw3-3 libfftw3-3 PATHS ${FFTW3_ROOT})
find_path(FFTW3_INCLUDE fftw3.h PATHS ${FFTW3_ROOT})

if(BUILD_APP)
    set(CMAKE_AUTOMOC ON)

    find_package(Qt6 REQUIRED COMPONENTS Widgets PrintSupport)

    set(UI_FILES ../labwork7/viewer_window.ui)

    # Сгенерировать заголовочные файлы из .ui
    qt6_wrap_ui(UI_HEADERS ${UI_FILES})
    add_executable(fourier_app
        ../labwork7/main.cpp
        ../labwork7/viewer_window.cpp
        ../labwork7/optimized_fft.cpp
        ../labwork6/qcustomplot.cpp
        ../labwork5/fourier_params.cpp
        app.rc
        ${UI_HEADERS}
    )
    target_include_directories(fourier_app PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/..
        ${CMAKE_CURRENT_BINARY_DIR}
        ${FFTW3_INCLUDE}          # <-- добавляем путь к заголовкам FFTW
    )
    target_link_libraries(fourier_app PRIVATE 
        Qt6::Widgets 
        Qt6::PrintSupport 
        ${FFTW3_LIB}              # <-- используем найденную библиотеку
    )
endif()
