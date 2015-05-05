#include "maxspinbox.h"

MaxSpinBox::MaxSpinBox(QWidget *parent) : QSpinBox(parent)
{

}

void MaxSpinBox::changeMax(int value)
{
    this->setEnabled(value != 0);
    this->setMaximum(value);
    this->setSuffix(QString("/%1").arg(value));
}
