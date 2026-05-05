# Лабораторная 4

Наследование. Классы RealMatrix и ComplexArray, наследники Array2D.

Сборка (g++ / MSVC):
  g++ -std=c++17 -o lab4.exe main.cpp real_matrix.cpp complex_array.cpp

Файлы:
- array2d.h — базовый шаблонный класс двумерного массива
- real_matrix.h/cpp — матрица: умножение, транспонирование, единичная матрица
- complex_array.h/cpp — комплексный массив: амплитуда, фаза, интенсивность
- main.cpp — тесты
