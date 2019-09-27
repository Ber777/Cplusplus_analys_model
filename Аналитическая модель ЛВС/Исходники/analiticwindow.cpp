#include "analiticwindow.h"
#include "ui_analiticwindow.h"
#include <math.h>

AnaliticWindow::AnaliticWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AnaliticWindow)
{
    ui->setupUi(this);
    descWindow = new DescrWindow();
    connect(descWindow, &DescrWindow::firstWindow, this, &AnaliticWindow::show);
}

AnaliticWindow::~AnaliticWindow()
{
    delete ui;
}

void AnaliticWindow::on_modeling_clicked()
{
    InitializeValue();
    CalculateOutputParametrs();
    ShowOutputData();
}

void AnaliticWindow::on_request_clicked()
{
    unsigned int numberDisk = ui->numberDisk->value();
    if(numberDisk <= m_quantityDisk)
    {
        ui->listDisks->setText("Загрузка диска " + QString::number(numberDisk, 10) +
                               " = " +  QString::number(m_loadingDisks,'f',4) + "\n");
    }
    else
    {
        QMessageBox::warning(this,"Внимание","Запрошенный диск не существует\n");
    }
}

void AnaliticWindow::on_cleaning_clicked()
{
     //выходные параметры
     ui->listDisks->clear();
     ui->tCycle->clear();
     ui->reactSys->clear();
     ui->loadingPC->clear();
     ui->loadingClient->clear();
     ui->loadingChanel->clear();
     ui->loadingCPU->clear();
     ui->U->clear();
     ui->lf0->clear();
     ui->lf->clear();
     ui->iteration->clear();

     ClearOutPutParameters();

     //входные пареметры
     ui->quantityCPU->clear();
     ui->quantityPC ->clear();
     ui->tDoProcessing-> clear();
     ui->tGenerationRequest -> clear();
     ui->tTransmitForward -> clear();
     ui->tTransmitOpposite -> clear();
     ui->tProcessingOnCPU -> clear();
     ui->tProcessingOnDisk -> clear();
     ui->quantityDisk -> clear();
     ui->pAfterProcessingOnDiskToCPU -> clear();
     ui->K1 -> clear();
     ui->K2 -> clear();
     ui->delta->clear();

     ClearInputParameters();
}

bool AnaliticWindow::GetValueStringToDouble(QString str, double& value)
{
   bool result = false;
   value = str.toDouble(&result);
   return result;
}

void AnaliticWindow::CalculateOutputParametrs()
{
    double pi; // вероятность обращения к i-му диску
    double betta; // среднее количество проходов запроса по тракту процессор-диски
    double tk; // среднее значение времени обработки запроса в канале передачи

    try
    {
        betta = 1/(1-m_pAfterProcessingOnDiskToCPU);
        pi = ((double) 1/(double) m_quantityDisk);
        tk = 0.5*(m_tTransmitForward + m_tTransmitOpposite);

        std::vector<double>m(2);
        // m[0] = 1/(2*tk);
        m[0] = m_quantityCPU/(betta*m_tProcessingOnCPU);
        m[1] = 1/(betta*pi*m_tProcessingOnDisk);
        double minM = *std::min_element(m.begin(), m.end());
        double lf1 = m_k1*minM*((m_quantityPC-1)/m_quantityPC);

        unsigned int iterate = 0;
        double lf = 0; //интенсивность потока
       do
        {
            iterate++;
            m_tReqInChanel = (2*tk)/(1-(2*lf1*tk));
            m_tReqInCPU = (betta*m_tProcessingOnCPU)/(1-pow((betta*lf1*m_tProcessingOnCPU/m_quantityCPU),(double)m_quantityCPU));
            m_tReqInDisk = (betta*m_tProcessingOnDisk)/(1-(betta*pi*lf1*m_tProcessingOnDisk));

            m_tCycle = m_tDoProcessing + m_tGenerationRequest + m_tReqInChanel + m_tReqInCPU + m_tReqInDisk;
            lf = (m_quantityPC-1)/m_tCycle;
            if((fabs(lf1 - lf)/lf) < m_delta)
            {
                break;
            }
            else
            {
                lf1 = lf1 - ((lf1 - lf)/m_k2);
            }
        }while(true);
        m_lf1 = lf1;
        m_lf = lf;
        m_iter = iterate;
        m_loadingPC = (m_tDoProcessing + m_tGenerationRequest)/m_tCycle;
        m_loadingClient = m_tGenerationRequest/m_tCycle;
        double lymda = m_quantityPC/m_tCycle;
        m_loadingChanel = 2 * lymda * tk;
        m_loadingCPU = betta * lymda * m_tProcessingOnCPU / m_quantityCPU;
        m_loadingDisks = betta * lymda * pi * m_tProcessingOnDisk;
        m_U = m_loadingPC * m_quantityPC;
        m_reactSys = m_tReqInChanel+m_tReqInCPU+m_tReqInDisk+m_tDoProcessing;
    }
    catch(...)
    {
       QMessageBox::warning(this,"Внимание","Ошибка при вычислении модели. Проверьте параметры\n");
       exit(1);
    }

    ShowOutputData();

}

void AnaliticWindow::ShowOutputData()
{
    ui->tCycle->setText(QString::number(m_tCycle,'f',4));
    ui->loadingPC->setText(QString::number(m_loadingPC,'f',4));
    ui->loadingClient->setText(QString::number(m_loadingClient,'f',4));
    ui->loadingChanel->setText(QString::number(m_loadingChanel,'f',4));
    ui->loadingCPU->setText(QString::number(m_loadingCPU,'f',4));
    ui->U->setText(QString::number(m_U,'f',4));
    ui->reactSys->setText(QString::number(m_reactSys,'f',4));
    ui->lf0->setText(QString::number(m_lf1,'f',4));
    ui->lf->setText(QString::number(m_lf,'f',4));
    ui->iteration->setText(QString::number(m_iter,'f',4));
}

void AnaliticWindow::InitializeValue()
{
    QString stringVal;

    m_quantityCPU = ui->quantityCPU->value();
    m_quantityPC = ui->quantityPC->value();

    stringVal = ui->tDoProcessing->text();
    if(!GetValueStringToDouble(stringVal,m_tDoProcessing))
    {
        QMessageBox::warning(this,"Внимание","Ошибка в параметре среднее врямя дообработки запроса на ПК\n");
    }

    stringVal = ui->tGenerationRequest->text();
    if(!GetValueStringToDouble(stringVal,m_tGenerationRequest))
    {
        QMessageBox::warning(this,"Внимание","Ошибка в параметре среднее время формирования запроса на ПК\n");
    }

    stringVal = ui->tTransmitForward->text();

    if(!GetValueStringToDouble(stringVal,m_tTransmitForward))
    {
        QMessageBox::warning(this,"Внимание","Ошибка в параметре среднее врямя передачи черз канал на сервер\n");
    }

    stringVal = ui->tTransmitOpposite->text();

    if(!GetValueStringToDouble(stringVal,m_tTransmitOpposite))
    {
        QMessageBox::warning(this,"Внимание","Ошибка в параметре среднее врямя передачи черз канал на ПК\n");
    }

    stringVal = ui->tProcessingOnCPU->text();

    if(!GetValueStringToDouble(stringVal,m_tProcessingOnCPU))
    {
        QMessageBox::warning(this,"Внимание","Ошибка в параметре среднее время обработки запроса на процессоре\n");
    }

    m_quantityDisk = ui->quantityDisk->value();

    stringVal = ui->tProcessingOnDisk->text();
    if(!GetValueStringToDouble(stringVal,m_tProcessingOnDisk))
    {
        QMessageBox::warning(this,"Внимание","Ошибка в параметре среднее время обработки запроса на диске\n");
    }

   stringVal = ui->pAfterProcessingOnDiskToCPU->text();
   if(!GetValueStringToDouble(stringVal,m_pAfterProcessingOnDiskToCPU))
   {
       QMessageBox::warning(this,"Внимание","Ошибка в параметре вероятность обращения запроса к ЦП после обработки на диски\n");
   }

    stringVal = ui->K1->text();
    if(!GetValueStringToDouble(stringVal,m_k1))
    {
        QMessageBox::warning(this,"Внимание","Ошибка в параметре коэффициент К1\n");
    }

    if((m_k1 < 0.9) ||(m_k1 > 0.999995))
    {
        QMessageBox::warning(this,"Внимание","Ошибка в параметре коэффициент К1. \nКоэффициент должен быть в диапазоне 0.9 .. 0.999995\n");
    }

    stringVal = ui->K2->text();
    if(!GetValueStringToDouble(stringVal,m_k2))
    {
        QMessageBox::warning(this,"Внимание","Ошибка в параметре коэффициент К2\n");
    }
    if((m_k2 < 10) || (m_k2 > 100000))
    {
        QMessageBox::warning(this,"Внимание","Ошибка в параметре коэффициент К2.  \nКоэффициент должен быть в диапазоне 10 .. 100000\n");
    }

    stringVal = ui->delta->text();
    if(!GetValueStringToDouble(stringVal,m_delta))
    {
        QMessageBox::warning(this,"Внимание","Ошибка в параметре точность\n");
    }

    if((m_delta < 0.000001) || (m_delta > 0.9))
    {
        QMessageBox::warning(this,"Внимание","Ошибка в параметре точность. \nКоэффициент должен быть в диапазоне 0.000001 .. 0.9\n");
    }
}

void AnaliticWindow::ClearOutPutParameters()
{
     m_loadingChanel = 0;
     m_loadingClient = 0;
     m_loadingCPU = 0;
     m_loadingDisks = 0;
     m_loadingPC = 0;
     m_U = 0;
     m_tReqInChanel = 0;
     m_tReqInCPU = 0;
     m_tReqInDisk = 0;
     m_tCycle = 0;
}
void AnaliticWindow::ClearInputParameters()
{
     m_quantityPC = 0;
     m_tDoProcessing = 0;                //среднее врямя дообработки запроса на ПК
     m_tGenerationRequest = 0;           //среднее время формирования запроса на ПК
     m_tTransmitForward = 0;             //среднее врямя передачи черз канал на сервер
     m_tTransmitOpposite = 0;            // среднее врямя передачи черз канал на ПК
     m_quantityCPU = 0;                  // количество процессоров
     m_tProcessingOnCPU = 0;             //среднее время обработки запроса на процессоре
     m_quantityDisk= 0;                 //количество дисков
     m_tProcessingOnDisk= 0;            // среднее время обработки запроса на диске
     m_pAfterProcessingOnDiskToCPU= 0;  // вероятность обращения запроса к ЦП после обработки на диски
     m_k1= 0;
     m_k2= 0;
     m_delta= 0;
}

void AnaliticWindow::on_pushButton_clicked()
{
    descWindow->show();  //Показываем второе окно
    this->close();
}
