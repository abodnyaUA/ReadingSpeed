#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// подключение необходимых библиотек
#include <QWidget>
#include <QTimer>
#include <QTextCodec>
#include <QFont>
#include <QTextStream>
#include <QFile>
#include <ctime>
#include <QFileDialog>
#include <resultwindow.h> // заголовок класса окна для вывода результатов
#include <infowindow.h>
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    // прототипы слотов класса
    void Info();
    void Open(); // загрузка файла
    void on_fontComboBox_currentFontChanged(const QFont &f); // изменение шрифта
    void UpdateTimer(); // обновление таймера в главном окне
    void on_spinBox_valueChanged(const QString &arg1); // изменение размера шрифта

private:
    QTimer timer; // таймер
    Ui::MainWindow *ui;
    bool started = false; // переменная, определяющая, был ли запущен тест
    bool loaded = false; // переменная, определяющая, был ли загружен файл
    int wordNumber; // количество слов в тексте
    time_t startTime; // время начала отсчета
    time_t finishTime; // время конца отсчета

protected:
    virtual void keyReleaseEvent(QKeyEvent* event); // прототип обработчика событий клавиатуры
};

#endif // MAINWINDOW_H
