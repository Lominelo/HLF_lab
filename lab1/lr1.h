// Реализация ввода координат с клавиатуры
void Keyboard_input(double &x, double &y);
// Функция определения принадлежности точки кругу
bool Circle(double x, double y);
// Функция определения принадлежности точки квадрату
bool Square(double x, double y);
// Реализация ввода координат извлечением из файла
void File_input(double* x, double* y);
// Реализация вывода результата в терминал
void Terminal_output(double x, double y, int shape);
// Реализация вывода результата в файл
void File_output(double x, double y, int shape);
