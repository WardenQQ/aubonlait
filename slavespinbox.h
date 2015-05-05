#ifndef SLAVESPINBOX_H
#define SLAVESPINBOX_H


#include <QSpinBox>


class SlaveSpinBox : public QSpinBox
{
    Q_OBJECT
public:
    explicit SlaveSpinBox(QWidget *parent = 0);

signals:

public slots:
    void changeMax(int value);
};

#endif // SLAVESPINBOX_H
