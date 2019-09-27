#ifndef DESCRWINDOW_H
#define DESCRWINDOW_H

#include <QMainWindow>

namespace Ui {
class DescrWindow;
}

class DescrWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DescrWindow(QWidget *parent = 0);
    ~DescrWindow();

signals:
    void firstWindow();

public slots:
    void on_pushButton_clicked();  //слот-функция нажатия кнопки вернуться к форме 1

private:
    Ui::DescrWindow *ui;
};

#endif // DESCRWINDOW_H
