#include <iostream>
#include <fstream>
using namespace std;
#include "lr1.h"


// Реализация ввода координат с клавиатуры
void Keyboard_input(double &x, double &y)
{
    cout<<"Input x ";
    cin>>x;
    cout<<"Input y ";
    cin>>y;
} 

// Функция определения принадлежности точки кругу
bool Circle(double x, double y)
{
    if ((x * x + y * y) < 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Функция определения принадлежности точки квадрату
bool Square(double x, double y)
{
    if (abs(x) < 1 && abs(y) < 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Реализация ввода координат извлечением из файла
void File_input(double* x, double* y)
{
    ifstream input_file("./input_coord.txt");
    input_file >> *x >> *y;
}

// Реализация вывода результата в терминал
void Terminal_output(double x, double y, int shape)
{
    bool output;
    switch (shape)
    {
        case 1:
        {
            output = Circle(x, y);
            break;
        }
        case 2:
        {
            output = Square(x, y);
            break;
        }
    }

    cout << "Point x = " << x << ", y = "<< y <<" ";
    if (output)
    {
        cout << "in ";
    }
    else
    {
        cout << "out of ";
    }
    if (shape == 1){
        cout << "Circle" << endl;
    }
    else
    {
        cout << "Square" << endl;
    }
}

// Реализация вывода результата в файл
void File_output(double x, double y, int shape)
{
    bool output;
    switch (shape)
    {
        case 1:
        {
            output = Circle(x, y);
            break;
        }
        case 2:
        {
            output = Square(x, y);
            break;
        }
    }

    ofstream output_file;
    output_file.open("./output_coord.txt", std::ios::app);
    cout<<"Results saved in output_coord.txt"<<endl;
    output_file << "Point x = " << x << ", y = "<< y <<" ";
    if (output)
    {
        output_file << "in ";
    }
    else
    {
        output_file << "out of ";
    }
    if (shape == 1){
        output_file << "Circle" << endl;
    }
    else
    {
        output_file << "Square" << endl;
    }
    output_file.close();
}

int main()
{
    double x, y;
    int input_mode;
    int shape_mode;
    int output_mode;
    bool flag = true;

    while (flag)
    {
        // Меню выбора фигуры
        cout<<"Choose shape mode: "<<endl;
        cout<<"1. Circle"<<endl;
        cout<<"2. Square"<<endl;
        cout<<"3. Escape"<<endl;
        cin>>shape_mode;
        while (shape_mode != 1 && shape_mode != 2 && shape_mode != 3){
            cout<<"Incorrect option"<<endl;
            cin>>shape_mode;
        }
        if (shape_mode == 3)
        {
            cout<<"Exit from programm"<<endl;
            break;
        }

        // Меню выбора режима ввода
        cout<<"Choose input mode: "<<endl;
        cout<<"1. from keybord"<<endl;
        cout<<"2. from file"<<endl;
        cin>>input_mode;
        while (input_mode != 1 && input_mode != 2){
            cout << "Incorrect option";
            cin>>input_mode;
        }
        switch (input_mode){
            case 1:
            {
                Keyboard_input(x, y);
                break;
            }
            case 2:
            {
                File_input(&x, &y);
                break;
            }
        }

        // Меню выбора режима вывода
        cout<<"Choose output mode: "<<endl;
        cout<<"1. in terminal"<<endl;
        cout<<"2. in file"<<endl;
        cin>>output_mode;
        while (output_mode != 1 && output_mode != 2){
            cout << "Incorrect option";
            cin>>output_mode;
        }
        switch (output_mode){
            case 1:
            {
                Terminal_output(x, y, shape_mode);
                break;
            }
            case 2:
            {
                File_output(x, y, shape_mode);
                break;
            }
        }
    }
    return 0;
}
