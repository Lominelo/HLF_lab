cmake_minimum_required(VERSION 3.16)
project(labwork5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(labwork5
    main.cpp
    param_window.cpp
    fourier_params.cpp
    param_window.ui
)

target_link_libraries(labwork5 PRIVATE Qt6::Widgets)
