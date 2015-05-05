#include "statswidget.h"
#include "ui_statswidget.h"

StatsWidget::StatsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatsWidget)
{
    ui->setupUi(this);

    consommationsParTypes(this->findChild<QCustomPlot *>(QString("histogrammeMoyenne")));
    consommationsParRevenu(this->findChild<QCustomPlot *>(QString("histogrammeRevenu")));

}

StatsWidget::~StatsWidget()
{
    delete ui;
}

void StatsWidget::consommationsParTypes(QCustomPlot *customPlot)
{

    QSqlQuery q;
    q.exec("SELECT avg(aubonlait), avg(total) FROM consommation GROUP BY type;");
    QVector<double> totalData, aubonlaitData;
    double max = 5;
    while(q.next()) {
        aubonlaitData << q.value(0).toDouble();
        totalData << q.value(1).toDouble() - q.value(0).toDouble();
        if (q.value(1).toDouble() > max)
            max = q.value(1).toDouble();
    }

    // create empty bar chart objects:
    QCPBars *total = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    QCPBars *aubonlait = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    customPlot->addPlottable(total);
    customPlot->addPlottable(aubonlait);
    // set names and colors:
    QPen pen;
    pen.setWidthF(1.2);
    aubonlait->setName("Aubonlait");
    pen.setColor(QColor(255, 131, 0));
    aubonlait->setPen(pen);
    aubonlait->setBrush(QColor(255, 131, 0, 50));
    total->setName("Total");
    pen.setColor(QColor(150, 222, 0));
    total->setPen(pen);
    total->setBrush(QColor(150, 222, 0, 70));
    // stack bars ontop of each other:
    total->moveAbove(aubonlait);

    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8;
    labels << "Natures" << "Fruits avec morceaux" << "Mixés/brassés" << "Aromatisés" << "Bifidus" << "Anti-cholestérol" << "À boire" << "Allégés";
    customPlot->xAxis->setAutoTicks(false);
    customPlot->xAxis->setAutoTickLabels(false);
    customPlot->xAxis->setTickVector(ticks);
    customPlot->xAxis->setTickVectorLabels(labels);
    customPlot->xAxis->setTickLabelRotation(60);
    customPlot->xAxis->setSubTickCount(0);
    customPlot->xAxis->setTickLength(0, 4);
    customPlot->xAxis->grid()->setVisible(true);
    customPlot->xAxis->setRange(0, 9);

    // prepare y axis:
    customPlot->yAxis->setRange(0, max+1);
    customPlot->yAxis->setPadding(5); // a bit more space to the left border
    customPlot->yAxis->setLabel("Nombre de yaourts");
    customPlot->yAxis->grid()->setSubGridVisible(true);
    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 0, 25));
    customPlot->yAxis->grid()->setPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    customPlot->yAxis->grid()->setSubGridPen(gridPen);

    // Set data:
    total->setData(ticks, totalData);
    aubonlait->setData(ticks, aubonlaitData);

    // setup legend:
    customPlot->legend->setVisible(true);
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    customPlot->legend->setBrush(QColor(255, 255, 255, 200));
    QPen legendPen;
    legendPen.setColor(QColor(130, 130, 130, 200));
    customPlot->legend->setBorderPen(legendPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    customPlot->legend->setFont(legendFont);
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void StatsWidget::consommationsParRevenu(QCustomPlot *customPlot)
{

    QSqlQuery q;
    q.exec("SELECT SUM(total) FROM Sonde NATURAL JOIN Consommation GROUP BY revenu;");
    QVector<double> totalData;
    double max = 5;
    while(q.next()) {
        double val = q.value(0).toDouble();
        totalData << val;
        if (val > max)
            max = val;
    }

    // create empty bar chart objects:
    QCPBars *total = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    customPlot->addPlottable(total);
    // set names and colors:
    QPen pen;
    pen.setWidthF(1.2);
    total->setName("Total");
    pen.setColor(QColor(150, 222, 0));
    total->setPen(pen);
    total->setBrush(QColor(150, 222, 0, 70));

    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3 << 4 << 5 << 6;
    labels << "De 0 à 1000" << "De 1000 à 2000" << "De 2000 à 3000" << "De 3000 à 4000" << "De 4000 à 5000" << "5000 et plus";
    customPlot->xAxis->setAutoTicks(false);
    customPlot->xAxis->setAutoTickLabels(false);
    customPlot->xAxis->setTickVector(ticks);
    customPlot->xAxis->setTickVectorLabels(labels);
    customPlot->xAxis->setTickLabelRotation(60);
    customPlot->xAxis->setSubTickCount(0);
    customPlot->xAxis->setTickLength(0, 4);
    customPlot->xAxis->grid()->setVisible(true);
    customPlot->xAxis->setRange(0, 7);

    // prepare y axis:
    customPlot->yAxis->setRange(0, max+1);
    customPlot->yAxis->setPadding(5); // a bit more space to the left border
    customPlot->yAxis->setLabel("Nombre de yaourts");
    customPlot->yAxis->grid()->setSubGridVisible(true);
    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 0, 25));
    customPlot->yAxis->grid()->setPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    customPlot->yAxis->grid()->setSubGridPen(gridPen);

    // Set data:
    total->setData(ticks, totalData);

    // setup legend:
    customPlot->legend->setVisible(true);
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    customPlot->legend->setBrush(QColor(255, 255, 255, 200));
    QPen legendPen;
    legendPen.setColor(QColor(130, 130, 130, 200));
    customPlot->legend->setBorderPen(legendPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    customPlot->legend->setFont(legendFont);
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}
