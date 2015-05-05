#include "slavespinbox.h"

SlaveSpinBox::SlaveSpinBox(QWidget *parent) : QSpinBox(parent)
{

}

void SlaveSpinBox::changeMax(int value)
{
    this->setEnabled(value != 0);
    this->setMaximum(value);
    this->setSuffix(QString("/%1").arg(value));
}
