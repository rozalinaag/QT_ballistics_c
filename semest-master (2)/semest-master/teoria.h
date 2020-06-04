#ifndef TEORIA_H
#define TEORIA_H

#include <QDialog>

namespace Ui {
class Teoria;
}

class Teoria : public QDialog
{
    Q_OBJECT

public:
    explicit Teoria(QWidget *parent = nullptr);
    ~Teoria();

private:
    Ui::Teoria *ui;
};

#endif // TEORIA_H
