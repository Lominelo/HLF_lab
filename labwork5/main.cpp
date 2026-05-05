#include <QApplication>
#include "param_window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ParamWindow win;
    win.resize(360, 420);
    win.show();
    return app.exec();
}
