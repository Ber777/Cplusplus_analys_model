#ifndef REMONTWINDOW_H
#define REMONTWINDOW_H

#include <QMainWindow>
#include <descwindow.h>
#include <QtMath>

namespace Ui {
class RemontWindow;
}

class RemontWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RemontWindow(QWidget *parent = 0);
    ~RemontWindow();

private slots:
    void on_pushButton_clicked();            //слот-функция нажатия кнопки начать моделирование
    void on_pushButton_2_clicked();          //слот-функция нажатия кнопки расшифровки параметров
    void on_cleanAreaDiskLoading_clicked();  //слот-функция очистки формы



private:
    Ui::RemontWindow *ui;
    DescWindow *descWindow;
    double m_tno;           //cреднее время наработки на отказ одного компьютера
    double m_tr;            //среднее время ремонта одного компьютера
    unsigned int m_N;       //количество компьютеров
    unsigned int m_C;       //количество специалистов, занятых ремонтом компьютеров
    int m_salary;           //заработная плата работника за один час
    int m_loss;             //финансовые потери организации от неисправного компьютера за один час

    long double m_P0;       //вероятность состояния рассматриваемой замкннутой СМО
    long double m_Q;        //среднее количество компьютеров, находящихся в очереди на ремонт
    long double m_L;        //среднее количество компьютеров, находящихся в неисправном состоянии (в очереди на ремонт + в процессе ремонта)
    long double m_W;        //среднее время нахождения компьютера в очереди на ремонт
    long double m_U;        //среднее количество компьютеров, которое непосредственно ремонтируются специалистами
    long double m_p0;       //коэффициент загрузки одного специалиста
    long double m_n;        //среднее количество исправных компьютеров
    long double m_pe;       //коэффициент загрузки компьютера (время, когда он находится в исправном состоянии)
    long double m_Tp;       //среднее время пребывания компьютера в неисправном состоянии (в очереди на ремонт и на ремонте)
    long double m_Tc;       //среднее время цикла для компьютера
    long double m_pep0;     //состояние системы
    long double m_ubtk;     //убытки организации

    void InitValues();             //инициализация входных параметров
    long double fact(int N);       //получение факториала числа
    void CalculateParametrs();     //вычисление искомых параметров
    void ShowOutputData();         //показать вычисленные значения
    void ClearInputParameters();   //очистка входных полей параметров в форме
    void ClearOutputParameters();  //очистка выходных параметров в форме

};

#endif // REMONTWINDOW_H
