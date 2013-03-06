#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) // main-функция программы
{
    QApplication a(argc, argv); // объявление класса-приложения
    MainWindow w; // объявление объекта класса MainWindow
    w.show(); // и передача ему управления
    
    return a.exec();
}
