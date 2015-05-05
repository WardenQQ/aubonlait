#include "piechart.h"

#include "nightcharts.h"

#include <QSqlQuery>

PieChart::PieChart(QWidget *parent) : QWidget(parent)
{
    QSqlQuery q;
    q.exec("SELECT COUNT(*) FROM Sonde NATURAL JOIN (SELECT * FROM Consommation WHERE type = 7 AND total > 0) GROUP BY sexe;");
    q.next();
    double female = q.value(0).toDouble();
    q.next();
    double male = q.value(0).toDouble();

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
