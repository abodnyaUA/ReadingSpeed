#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H

#include <QWidget>

namespace Ui {
class ResultWindow;
}

class ResultWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit ResultWindow(int words, int time); // конструктор класса, получающий количество слов и затраченное время
    ~ResultWindow();
    
private:
    Ui::ResultWindow *ui;
};

#endif // RESULTWINDOW_H
