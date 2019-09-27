#include "remontwindow.h"
#include "ui_remontwindow.h"

RemontWindow::RemontWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RemontWindow)
{
    ui->setupUi(this);
    descWindow = new DescWindow();
    connect(descWindow, &DescWindow::firstWindow, this, &RemontWindow::show);
}

RemontWindow::~RemontWindow()
{
    delete ui;
}

void RemontWindow::on_pushButton_clicked()
{
    InitValues();
    CalculateParametrs();
}

void RemontWindow::on_pushButton_2_clicked()
{
    descWindow->show();  //Показываем второе окно
    this->close();
}

void RemontWindow::ClearInputParameters()
{
     m_tno = 0;
     m_tr = 0;
     m_N = 0;
     m_C = 0;
     m_salary = 0;
     m_loss = 0;
}

void RemontWindow::ClearOutputParameters()
{
     m_P0 = 0;
     m_Q = 0;
     m_L = 0;
     m_W = 0;
     m_U = 0;
     m_p0 = 0;
     m_n = 0;
     m_pe = 0;
     m_Tp = 0;
     m_Tc = 0;
     m_pep0 = 0;
     m_ubtk = 0;
}


long double RemontWindow::fact(int N)
{
    if(N < 0)       // если пользователь ввел отрицательное число
        return 0;   // возвращаем ноль
    else if (N == 0)     // если пользователь ввел ноль,
        return 1;   // возвращаем факториал от нуля = 1
    else            // Во всех остальных случаях рекурсия.
        return (long double)N * (long double)(fact(N - 1));
}

void RemontWindow::CalculateParametrs()
{
    double Mno = 1/m_tno; //интенсивность отказа одного компьютера
    double Mo = 1/m_tr;   //интенсивность ремонта компьютера
    double fi = Mno/Mo;   //коэффициент отношения интенсивности наработки на отказ к интенсивности восстановления работоспособности компьютера
    long double P01 = 0, P02 = 0; //вероятности состояния рассматриваемой СМО
    long double N = fact(m_N);

    for (unsigned int k = 0; k <= m_C; k++)
    {
        P01 += (N * pow(fi, (double)k))/(fact(k) * fact((double)m_N - (double)k));
    }

    for(unsigned int k = m_C+1; k <= m_N; k++)
    {
        P02 += (N * pow(fi, (double)k)) / (pow(m_C, ((double)k - (double)m_C)) * fact(m_C) * fact((double)m_N -(double) k));
    }

    m_P0 = pow((P01 + P02), -1);

    double P[m_N] = {0};
    for(unsigned int k = 1; k <= m_C; k++)
    {
        P[k] = ((N * pow(fi, (double)k))/(fact(k) * fact((double)m_N - (double)k))) * m_P0;
    }

    for(unsigned int k = m_C+1; k <= m_N; k++)
    {
        P[k] = ((N * pow(fi, (double)k))/(pow(m_C, ((double)k - (double)m_C)) * fact((double)m_C) * fact((double)m_N - (double)k))) * m_P0;
    }

    for(unsigned int k = m_C; k <= m_N; k++)
    {
       m_Q += (double)((double)k - (double)m_C) * P[k];
    }

    for(unsigned int k = 1; k <= m_N; k++)
    {
        m_L += (double)k * P[k];
    }

    m_U = m_L - m_Q;
    m_p0 = m_U / m_C;
    m_Tp = (m_L * m_tno)/(double)((double)m_N - m_L);
    m_W = m_Tp - m_tr;
    m_Tc = m_Tp + m_tno;
    m_pe = m_tno / m_Tc;
    m_n = m_N - m_L;
    m_pep0 = (m_C * m_tno)/(m_N * m_tr);
    m_ubtk = m_C * m_salary + m_L * m_loss;

    ShowOutputData();
}

void RemontWindow::ShowOutputData()
{
    ui->P0->setText(QString::number(m_P0,'f',4));
    ui->Q->setText(QString::number(m_Q,'f',4));
    ui->L->setText(QString::number(m_L,'f',4));
    ui->U->setText(QString::number(m_U,'f',4));
    ui->p0->setText(QString::number(m_p0,'f',4));
    ui->Tp->setText(QString::number(m_Tp,'f',4));
    ui->W->setText(QString::number(m_W,'f',4));
    ui->Tc->setText(QString::number(m_Tc,'f',4));
    ui->pe->setText(QString::number(m_pe,'f',4));
    ui->n->setText(QString::number(m_n,'f',4));
    ui->pep0->setText(QString::number(m_pep0,'f',4));
    ui->ubtk->setText(QString::number(m_ubtk,'f',4));
}

void RemontWindow::InitValues()
{
    m_tno = ui->tno->value();
    m_tr = ui->tr->value();
    m_N = ui->N->value();
    m_C = ui->C->value();
    m_salary = ui->salary->value();
    m_loss = ui->loss->value();

    ClearOutputParameters();
}

void RemontWindow::on_cleanAreaDiskLoading_clicked()
{
    ui->tno->setValue(0.00);
    ui->tr->setValue(0.00);
    ui->N->setValue(25);
    ui->C->setValue(2);
    ui->salary->setValue(100);
    ui->loss->setValue(100);

    ui->P0->clear();
    ui->Q->clear();
    ui->L->clear();
    ui->U->clear();
    ui->p0->clear();
    ui->Tp->clear();
    ui->W->clear();
    ui->Tc->clear();
    ui->pe->clear();
    ui->n->clear();
    ui->pep0->clear();
    ui->ubtk->clear();

    ClearOutputParameters();
    ClearInputParameters();
}
