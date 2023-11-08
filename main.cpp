#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    qDebug()<< "translation loaded = "<<translator.load(QLocale::Russian, "puzzle", "_");
    a.installTranslator(&translator);


    MainWindow w;
    w.show/*FullScreen*/();
//    w. setFixedSize(w.size());
    return a.exec();
}
