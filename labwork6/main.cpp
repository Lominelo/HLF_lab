#include <QApplication>
#include "spectrum_window.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    SpectrumWindow w;
    w.show();
    return app.exec();
}
