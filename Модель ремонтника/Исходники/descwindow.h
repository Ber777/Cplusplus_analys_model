#ifndef DESCWINDOW_H
#define DESCWINDOW_H

#include <QMainWindow>

namespace Ui {
class DescWindow;
}

class DescWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DescWindow(QWidget *parent = 0);
    ~DescWindow();

signals:
    void firstWindow();

private slots:
    void on_pushButton_clicked();  //слот-функция нажатия кнопки вернуться к форме 1

private:
    Ui::DescWindow *ui;
};

#endif // DESCWINDOW_H
