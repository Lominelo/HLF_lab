#include <QApplication>
#include "viewer_window.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    ViewerWindow w;
    w.show();
    return app.exec();
}
