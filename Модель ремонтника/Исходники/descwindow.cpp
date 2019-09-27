#include "descwindow.h"
#include "ui_descwindow.h"

DescWindow::DescWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DescWindow)
{
    ui->setupUi(this);
}

DescWindow::~DescWindow()
{
    delete ui;
}

void DescWindow::on_pushButton_clicked()
{
    this->close();
    emit firstWindow();
}
