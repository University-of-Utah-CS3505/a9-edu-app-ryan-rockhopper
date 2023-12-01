#include "mainwindow.h"
#include "statsmodel.h"

#include <QApplication>
#include <QWindow>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    statsModel model;
    MainWindow w(model, &a);
    w.show();
    return a.exec();
}
