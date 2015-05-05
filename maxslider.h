#ifndef MAXSLIDER_H
#define MAXSLIDER_H

#include <QSlider>


class SlaveSlider : public QSlider
{
    Q_OBJECT
public:
    explicit SlaveSlider(QWidget *parent = 0);

signals:

public slots:
    void changeMax(int value);
};

#endif // MAXSLIDER_H
