# Лабораторная 7

Оптимизированная версия лабораторной 6.

Сборка (CMake + Qt6 + FFTW3):
  mkdir build && cd build
  cmake .. -DCMAKE_PREFIX_PATH=C:/Qt/6.x.x/msvc2022_64
  cmake --build .

Сборка (qmake):
  qmake labwork7.pro
  make

Оптимизации:
1. Кэширование плана FFTW (FFTW_MEASURE вместо FFTW_ESTIMATE)
2. Переиспользование буферов (без повторных аллокаций)
3. Оптимизация генерации круга (симметрия по квадрантам)
4. std::norm() для интенсивности (без sqrt)
5. Логарифмическая шкала спектра

Файлы:
- app_settings.h — структура параметров
- optimized_fft.h/cpp — оптимизированный FFT-процессор
- viewer_window.h/cpp — окно с логарифмической шкалой и таймером
- viewer_window.ui — форма Qt Designer для главного окна
- labwork7.pro — проектный файл qmake
- qcustomplot.h/cpp — библиотека QCustomPlot
- main.cpp — точка входа
- CMakeLists.txt — конфигурация сборки CMake
