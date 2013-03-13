#include "infowindow.h"
#include "ui_infowindow.h"

infoWindow::infoWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::infoWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Widget | Qt::CustomizeWindowHint);
    setWindowFlags(Qt::Widget | Qt::WindowTitleHint);
    setWindowFlags(Qt::Widget | Qt::WindowCloseButtonHint);
    setWindowFlags(Qt::Widget | Qt::WindowSystemMenuHint);
    setAttribute(Qt::WA_DeleteOnClose, true); // при закрытии окна удалять объект
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(close())); // подключение closeButton к слоту закрытия окна
}

infoWindow::~infoWindow()
{
    delete ui;
}
