#include "maxslider.h"

SlaveSlider::SlaveSlider(QWidget *parent) : QSlider(parent)
{

}

void SlaveSlider::changeMax(int value)
{
    this->setMaximum(value);
}
