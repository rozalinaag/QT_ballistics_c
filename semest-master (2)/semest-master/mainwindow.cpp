#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <cmath>
#include "./qcustomplot.h"
#include<QPixmap>
#include "teoria.h"
#define PI 3.14
#define G 9.8
#define E 2.7

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->angle->setMaximum(90); //ограничения угла и скорости
    ui->speed->setMaximum(45);

    graphic = ui->widget;
    //составление графика
    graphic->addGraph();

    // добавляем название осей
    graphic->xAxis->setLabel("Дальность, м");
    graphic->yAxis->setLabel("Высота, м");
    // диапозон осей
    graphic->xAxis->setRange(0, 20);
    graphic->yAxis->setRange(0, 20);
    graphic->replot();


    //для картинки
    QPixmap pix(":/img/Ym.PNG");
    int w=ui->image->width();
    int h=ui->image->height();
    ui->image->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::printGraphicWithResistance(int speed, int angle, double coeff, double weight){ //с учетом среды
    QVector<double> x(700), y(700);

    double maxHeight = 0,
           maxDistance = 0,
           time = 0,
           step = 0.01,
           flag = true,
           maxAxis = 0;

    for (int i=0; i < x.length(); i++)
    {
        x[i]=speed*cos(angle*PI/180)*(weight/coeff)*(1-pow(E,(-coeff*time/weight)));
        y[i]=(weight/coeff)*((speed*sin(angle*PI/180)+weight*G/coeff)*(1-pow(E,(-coeff*time/weight)))-G*time);

        if (i >= 1 && y[i-1] <= 0 && y[i] <= 0 && flag) {
            ui->resultTime->setNum(time - 0.02);
            maxDistance = x[i-2];
            ui->resultDistance->setNum(maxDistance);
            flag = !flag;
        }

        if (y[i] > maxHeight) { //нахождение максимальной высоты
            maxHeight = y[i];
        }

        time += step;
    }

    ui->resultHeight->setNum(maxHeight);

    if (maxDistance > maxHeight) maxAxis = maxDistance; else maxAxis = maxHeight;

    graphic->graph(0)->setData(x, y);
    graphic->xAxis->setRange(0, maxAxis);
    graphic->yAxis->setRange(0, maxAxis);
    graphic->replot();

    x.clear();
    y.clear();
}

void MainWindow::printGraphicWithoutResistance(int speed, int angle) { //функция без учета среды
    QVector<double> x(1000), y(1000);
    double maxAxis = 0,
           value = 0;

    double time = 2 * speed * sin(angle * PI / 180) / G;   //время
    double distance = pow(speed, 2) * sin(2 * angle * PI / 180) / G;  //дистанция
    double height = pow(speed * sin(angle * PI / 180), 2) / (2 * G);   //высота
    double step = distance / 1000;

    if (distance > height) maxAxis = distance; else maxAxis = height;

    for (int i=0; i < 1000; i++) {
      x[i] = value;
      y[i] = x[i] * tan(angle * PI / 180) - (G / (2 * pow(speed, 2) * pow(cos(angle * PI / 180), 2))) * pow(x[i], 2);
      value += step;
    }

    ui->resultTime->setNum(time);
    ui->resultHeight->setNum(height);
    ui->resultDistance->setNum(distance);

    graphic->graph(0)->setData(x, y);
    graphic->xAxis->setRange(0, maxAxis);
    graphic->yAxis->setRange(0, maxAxis);
    graphic->replot();

    x.clear();
    y.clear();
}

void MainWindow::on_buttonStart_clicked() //кнопка вычислить
{
    int speed = ui->speed->value();   //скорость
    int angle = ui->angle->value();   //угол
    double density = ui->density->value();  //плотность среды
    double radius = ui->radius->value();   //радиус шара
    double weight = ui->weight->value(); //масса нужна для вычисления у(х) и х с учетом сопротивления

    double coeff = 0.5*0.15*PI*pow(radius, 2)*density; //рассчитываем коэффициент сопротивления k=0.5*C*S*ro C=0.15 S=pi*r^2 ro=1.29

    ui->resultHeight->setNum(coeff);

    if (density == 0 || radius == 0 || weight == 0) {
        printGraphicWithoutResistance(speed, angle);
    } else {
        printGraphicWithResistance(speed, angle, coeff, weight);
    }
}

void MainWindow::on_action_triggered()
{
    ui->statusbar->showMessage("Новый проект создан!");
}

void MainWindow::on_action_2_triggered()
{
    ui->statusbar->showMessage("Проект открыт!");
}

void MainWindow::on_action_3_triggered()
{
   QMessageBox::StandardButton reply = QMessageBox::question(this,"Закрытие проекта","Закрыть проект?",QMessageBox::No|QMessageBox::Yes);
   if (reply==QMessageBox::Yes)
   {
       QApplication::quit();
   }
}

void MainWindow::on_action_9_triggered()
{
    Teoria win;
    win.setModal(true);
    win.exec();
}

void MainWindow::on_action_8_triggered()
{
    ui->statusbar->showMessage("Сохранено!");
}

void MainWindow::on_action_7_triggered()
{
    ui->statusbar->showMessage("Сохранено!");
}
