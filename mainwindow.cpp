#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&timer, SIGNAL(timeout()), this, SLOT(UpdateTimer())); // подключение слота обновления таймера к сигналу таймера
    connect(ui->openButton, SIGNAL(clicked()), this, SLOT(Open())); // подключение openButton к слоту открытия файла
    connect(ui->infoButton, SIGNAL(clicked()), this, SLOT(Info()));
    ui->instructionsBox->setHtml("Загрузите файл, нажав кнопку 'Открыть файл'.");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) // обработчик событий клавиатуры, срабатывающий при нажатии любой кнопки
{
    if (event->key())
    {
        if (loaded) // если файл загружен
        {
            if (!started) // если тест не начат
            {
                started = true; // начало теста
                ui->instructionsBox->setHtml("Нажмите любую кнопку, чтобы завершить."); // установка подсказки
                startTime = time(NULL); // запуск таймеров
                UpdateTimer();
                timer.start(1000);
            }
            else if (started) // если тест начат
            {
                timer.stop(); // остановка таймер
                finishTime = time(NULL);
                started = false; // конец теста
                ResultWindow *result = new ResultWindow(wordNumber, finishTime-startTime); // создание объекта класса ResultWindow и передача ему количества слов в тексте и затраченного времени
                result->show(); // открытие окна
                ui->lcdNumber->display(0); // обнуление таймера в основном окне
                ui->instructionsBox->setHtml("Нажмите любую кнопку, чтобы начать."); // установка подсказки
            }
        }
        else if (!loaded) // если файл не загружен
        {
            ui->instructionsBox->setHtml("Сначала загрузите файл, нажав кнопку 'Открыть файл'."); // установка подсказки
        }
    }
}

void MainWindow::Open() // слот открытия файла
{
    QString fname = QFileDialog::getOpenFileName(this, "Открытие файла", "Тексты", "Текстовые файлы(*.txt)"); // вызов диалога открытия файла
    QFile file(fname); // инициализация объекта-файла по имени, возвращенному диалогом открытия
    file.open(QFile::ReadOnly | QFile::Text); // открытие файла для чтения, как текст
    if (file.isOpen())
    {
        QTextStream ReadFile(&file); // инициализация текстового потока
        ui->textBrowser->setText(ReadFile.readAll()); // вывод текста из файла в textBrowser
        wordNumber = ui->textBrowser->toPlainText().split(' ').count(); // подсчет количества слов в тексте
        loaded = true; // файл загружен
        ui->instructionsBox->setHtml("Нажмите любую кнопку, чтобы начать."); // установка подсказки
    }
}
void MainWindow::on_fontComboBox_currentFontChanged(const QFont &f) // изменение шрифта
{
    QFont fnt = f; // объявление объекта-шрифта
    fnt.setPointSize(ui->spinBox->value()); // изменение его размера в соответствии со значение spinBox
    ui->textBrowser->setFont(fnt); // установка шрифта для textBrowser
}

void MainWindow::on_spinBox_valueChanged(const QString &arg1) // изменение размера шрифта
{
    QFont font = ui->fontComboBox->currentFont();
    font.setPointSize(arg1.toInt());
    ui->textBrowser->setFont(font);
}

void MainWindow::UpdateTimer() // обновление таймера
{
    ui->lcdNumber->display(ui->lcdNumber->value() + 1);
}

void MainWindow::Info()
{
    infoWindow *wnd = new infoWindow();
    wnd->show();
}
