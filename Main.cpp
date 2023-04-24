#include <QApplication>

#include "ViewGL/GLMainWindow.hh"
#include "Controller.hh"

// initializing instancePtr with NULL
Controller* Controller ::instancePtr = NULL;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GLMainWindow w;

    w.show();
    return a.exec();
}
