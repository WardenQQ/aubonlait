#include "piechart.h"

#include "nightcharts.h"

#include <QSqlQuery>

PieChart::PieChart(QWidget *parent) : QWidget(parent)
{
    QSqlQuery q;
    q.exec("SELECT COUNT(*), sexe FROM Sonde NATURAL JOIN (SELECT * FROM Consommation WHERE type = 7 AND total > 0) GROUP BY sexe;");
    double female = 0, male = 0;
    while (q.next()) {
        if (q.value(1).toInt() == 0)
            female = q.value(0).toDouble();
        else
            male = q.value(0).toDouble();
    }

    if (male + female == 0) {
        female = 100;
    }
    percentFemale = (female / (female + male)) * 100;
    percentMale = 100 - percentFemale;
}

void PieChart::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);
    QPainter painter;
    QFont font;
    painter.begin(this);
    Nightcharts PieChart;
    PieChart.setType(Nightcharts::Pie);//{Histogramm,Pie,DPie};
    PieChart.setLegendType(Nightcharts::Vertical);//{Round,Vertical}
    PieChart.setCords(0, 0, this->height(), this->height());
    PieChart.setShadows(false);
    PieChart.palpha = 90;

    PieChart.addPiece("Homme", Qt::blue, percentMale);
    PieChart.addPiece("Femme", Qt::red, percentFemale);
    PieChart.draw(&painter);
    PieChart.drawLegend(&painter);
}
