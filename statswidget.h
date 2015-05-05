#ifndef STATSWIDGET_H
#define STATSWIDGET_H

#include <QWidget>
#include <QSqlQuery>


#include "qcustomplot.h"

namespace Ui {
class StatsWidget;
}

class StatsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StatsWidget(QWidget *parent = 0);
    ~StatsWidget();
    void consommationsParTypes(QCustomPlot *customPlot);
    void consommationsParRevenu(QCustomPlot *customPlot);


private:
    Ui::StatsWidget *ui;
};

#endif // STATSWIDGET_H
