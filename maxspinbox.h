#ifndef MAXSPINBOX_H
#define MAXSPINBOX_H

#include <QSpinBox>


class MaxSpinBox : public QSpinBox
{
    Q_OBJECT
public:
    explicit MaxSpinBox(QWidget *parent = 0);

signals:

public slots:
    void changeMax(int value);
};

#endif // MAXSPINBOX_H
