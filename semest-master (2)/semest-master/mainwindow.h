#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonStart_clicked();
    void printGraphicWithResistance(int speed, int angle, double coeff, double weight);
    void printGraphicWithoutResistance(int speed, int angle);

    void on_action_triggered();

    void on_action_2_triggered();

    void on_action_3_triggered();

    void on_action_9_triggered();

    void on_action_8_triggered();

    void on_action_7_triggered();

private:
    Ui::MainWindow *ui;
    QCustomPlot *graphic;      // Объявляем объект QCustomPlot
    QCPCurve *verticalLine;     // Объявляем объект для вертикальной линии
    QCPItemTracer *tracer;      // Трасировщик по точкам графика
};
#endif // MAINWINDOW_H
