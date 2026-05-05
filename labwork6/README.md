# Лабораторная 6

2D преобразование Фурье с визуализацией через QCustomPlot.

Сборка (CMake + Qt6 + FFTW3):
  mkdir build && cd build
  cmake .. -DCMAKE_PREFIX_PATH=C:/Qt/6.x.x/msvc2022_64
  cmake --build .

Сборка (qmake):
  qmake labwork6.pro
  make

Файлы:
- fft_processor.h/cpp — вычисление БПФ через FFTW
- spectrum_window.h/cpp — окно с цветовыми картами и сечениями
- spectrum_window.ui — форма Qt Designer для главного окна
- labwork6.pro — проектный файл qmake
- qcustomplot.h/cpp — библиотека QCustomPlot (скачать с qcustomplot.com)
- main.cpp — точка входа
- CMakeLists.txt — конфигурация сборки CMake
