//#include "muehle.h"
#include "gui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Muehle w;
    gui w;
    w.show();
    return a.exec();
}
