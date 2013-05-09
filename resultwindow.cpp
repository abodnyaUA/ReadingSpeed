#include "resultwindow.h"
#include "ui_resultwindow.h"

ResultWindow::ResultWindow(int words, int time):
    QWidget(),
    ui(new Ui::ResultWindow)
{
    ui->setupUi(this);
    // запрет отображения лишних системных кнопок
    setWindowFlags(Qt::Widget | Qt::CustomizeWindowHint);
    setWindowFlags(Qt::Widget | Qt::WindowTitleHint);
    setWindowFlags(Qt::Widget | Qt::WindowCloseButtonHint);
    setWindowFlags(Qt::Widget | Qt::WindowSystemMenuHint);
    setAttribute(Qt::WA_DeleteOnClose, true); // при закрытии окна удалять объект
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(close())); // подключение closeButton к слоту закрытия окна
    ui->wordCount->setText(QString::number(words)); // отображения количества слов в тексте
    ui->timeCount->setText(QString::number(time)+" сек"); // отображение затраченного времени
    if (time != 0)
        ui->readingSpeed->setText(QString::number(words/time*60)+" сл/мин"); // отображение скорости чтения
    else
        ui->readingSpeed->setText(QString::number(0)); // защита от вылета, если тест завершается сразу
}

ResultWindow::~ResultWindow()
{
    delete ui;
}
