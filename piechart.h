#ifndef PIECHART_H
#define PIECHART_H

#include <QWidget>

class PieChart : public QWidget
{
    Q_OBJECT
public:
    explicit PieChart(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *e);

private:
    double percentFemale;
    double percentMale;

signals:

public slots:
};

#endif // PIECHART_H
