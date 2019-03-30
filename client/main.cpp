#include "mainwindow.h"
#include <QApplication>
#include <QCheckBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle(QString::fromUtf8("NTU Big Eater"));

    w.show();

    return a.exec();
}
