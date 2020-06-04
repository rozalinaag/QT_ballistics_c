#include "teoria.h"
#include "ui_teoria.h"
#include<QPixmap>

Teoria::Teoria(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Teoria)
{
    ui->setupUi(this);

    //для картинки
    QPixmap pix(":/img/11.PNG");
    int w=ui->label1->width();
    int h=ui->label1->height();
    ui->label1->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));
}

Teoria::~Teoria()
{
    delete ui;
}
