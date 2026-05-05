# Лабораторная 5

Qt-интерфейс для параметров преобразования Фурье.

Сборка (CMake + Qt6):
  mkdir build && cd build
  cmake .. -DCMAKE_PREFIX_PATH=C:/Qt/6.x.x/msvc2022_64
  cmake --build .

Сборка (qmake):
  qmake labwork5.pro
  make

Файлы:
- fourier_params.h/cpp — класс параметров с пересчетом шагов
- param_window.h/cpp — главное окно с элементами управления
- param_window.ui — форма Qt Designer для главного окна
- labwork5.pro — проектный файл qmake
- main.cpp — точка входа
- CMakeLists.txt — конфигурация сборки CMake
