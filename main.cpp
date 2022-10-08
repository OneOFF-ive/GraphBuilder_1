#include "mainWindow/mainwindow.h"

#include <QApplication>
#include "lineItem/lineitem.h"
#include "myGraphicsView/mygraphicsview.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
