#include "mainwindow.h"
#include "gamemodel.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gameModel model;
    MainWindow w(model);
    w.show();
    return a.exec();
}
