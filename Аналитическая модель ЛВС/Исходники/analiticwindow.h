#ifndef ANALITICWINDOW_H
#define ANALITICWINDOW_H

#include <QMainWindow>
#include<QMessageBox>
#include <QTextBrowser>
#include <descrwindow.h>


namespace Ui {
class AnaliticWindow;
}

class AnaliticWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AnaliticWindow(QWidget *parent = 0);
    ~AnaliticWindow();

private slots:
    void on_modeling_clicked();

    void on_request_clicked();

    void on_cleaning_clicked();

    void on_pushButton_clicked();

private:
    Ui::AnaliticWindow *ui;
    DescrWindow *descWindow;
    //члены класса входные и выходные переменные объявлены ниже
    // входные данные
    unsigned int m_quantityPC;             //количество рабочих станций
    double m_tDoProcessing;                //среднее врямя дообработки запроса на ПК
    double m_tGenerationRequest;           //среднее время формирования запроса на ПК
    double m_tTransmitForward;             //среднее врямя передачи черз канал на сервер
    double m_tTransmitOpposite;            //среднее врямя передачи черз канал на ПК
    unsigned int m_quantityCPU;            //количество процессоров
    double m_tProcessingOnCPU;             //среднее время обработки запроса на процессоре
    unsigned int m_quantityDisk;           //количество дисков
    double m_tProcessingOnDisk;            //среднее время обработки запроса на диске
    double m_pAfterProcessingOnDiskToCPU;  //вероятность обращения запроса к ЦП после обработки на диски
    int m_U;                               //среднее количество работающих компьютеров
    double m_k1;
    double m_k2;
    double m_delta;

    //выходные переменные
    double m_tReqInChanel;             //среднее время пребывания запроса в канале связи
    double m_tReqInCPU;                // среднее время пребывания запроса в процесосре
    double m_tReqInDisk;               // среднее время пребывания запроса в диске
    double m_tCycle;                   // среднее время цикла системы
    double m_loadingPC;                // загрузка ПК
    double m_loadingClient;            // загрузка пользователя
    double m_loadingChanel;            // загрузка канала
    double m_loadingCPU;               // загрузка процессора
    double m_loadingDisks;             // загрузка дисков
    double m_lf1;
    double m_lf;
    double m_reactSys;
    unsigned int m_iter;

    void InitializeValue();  // функция считывания(инициализации входных переменных)
    bool GetValueStringToDouble(QString str, double& value);
    void CalculateOutputParametrs();
    void ShowOutputData();
    void ClearInputParameters();
    void ClearOutPutParameters();
};

#endif // ANALITICWINDOW_H
