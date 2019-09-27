#include "descrwindow.h"
#include "ui_descrwindow.h"

DescrWindow::DescrWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DescrWindow)
{
    ui->setupUi(this);
}

DescrWindow::~DescrWindow()
{
    delete ui;
}

void DescrWindow::on_pushButton_clicked()
{
    this->close();
    emit firstWindow();
}
