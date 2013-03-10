#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&timer, SIGNAL(timeout()), this, SLOT(UpdateTimer())); // подключение слота обновления таймера к сигналу таймера
    connect(ui->openButton, SIGNAL(clicked()), this, SLOT(Open())); // подключение openButton к слоту открытия файла
    ui->instructionsBox->setHtml("Загрузите файл,<br> нажав кнопку 'Открыть файл'.");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) // обработчик событий клавиатуры, срабатывающий при нажатии любой кнопки
{
    if (loaded) // если файл загружен
    {
        if (!started) // если тест не начат
        {
            started = true; // начало теста
            ui->instructionsBox->setHtml("Нажмите любую кнопку, <br> чтобы завершить."); // установка подсказки
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
            ui->instructionsBox->setHtml("Нажмите любую кнопку, <br> чтобы начать."); // установка подсказки
        }
    }
    else if (!loaded) // если файл не загружен
    {
        ui->instructionsBox->setHtml("Сначала загрузите файл,<br> нажав кнопку 'Открыть файл'."); // установка подсказки
    }
}

void MainWindow::Open() // слот открытия файла
{
    QString fname = QFileDialog::getOpenFileName(this, "Открытие файла", "Тексты", "Текстовые файлы(*.txt)"); // вызов диалога открытия файла
    QFile file(fname); // инициализация объекта-файла по имени, возвращенному диалогом открытия
    file.open(QFile::ReadOnly | QFile::Text); // открытие файла для чтения, как текст
    QTextStream ReadFile(&file); // инициализация текстового потока
    ui->textBrowser->setText(ReadFile.readAll()); // вывод текста из файла в textBrowser
    wordNumber = ui->textBrowser->toPlainText().split(' ').count(); // подсчет количества слов в тексте
    loaded = true; // файл загружен
    ui->instructionsBox->setHtml("Нажмите любую кнопку, <br> чтобы начать."); // установка подсказки
}
void MainWindow::on_fontComboBox_currentFontChanged(const QFont &f) // изменение шрифта
{
    QFont fnt = f; // объявление объекта-шрифта
    fnt.setPointSize(ui->spinBox->value()); // изменение его размера в соответствии со значение spinBox
    ui->textBrowser->setFont(fnt); // установка шрифта для textBrowser
}

void MainWindow::on_spinBox_valueChanged(const QString &arg1) // изменение размера шрифта
{
    QFont font = ui->textBrowser->currentFont(); // инициализация объекта-шрифта равного текущему шрифту textBrowser
    font.setPointSize(arg1.toInt()); // изменение его размера в соответствии с текущим значением spinBox
    ui->textBrowser->setFont(font); // установка шрифта для textBrowser
}

void MainWindow::UpdateTimer() // обновление таймера
{
    ui->lcdNumber->display(ui->lcdNumber->value() + 1);
}
