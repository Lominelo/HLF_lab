# Лабораторная 8

Юнит-тесты и упаковка приложения.

Запуск тестов (без Qt):
  g++ -std=c++17 -I.. -o run_tests.exe tests.cpp ../labwork4/real_matrix.cpp ../labwork4/complex_array.cpp ../labwork5/fourier_params.cpp
  run_tests.exe

Или через CMake:
  mkdir build && cd build
  cmake ..
  cmake --build .
  run_tests.exe

Файлы:
- tests.cpp — юнит-тесты для Array2D, RealMatrix, ComplexArray, FourierParams
- app.rc — ресурсный файл для иконки приложения (Windows)
- deploy.sh — скрипт упаковки
- CMakeLists.txt — конфигурация сборки
