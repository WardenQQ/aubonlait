#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "surveywizard.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->startWidget = this->findChild<QWidget *>(QString("startWidget"));

    QPushButton * surveyButton = this->findChild<QPushButton *>(QString("surveyButton"));
    connect(surveyButton, &QPushButton::clicked, this, &MainWindow::displaySurvey);
    connect(surveyButton, &QPushButton::clicked, startWidget, &QWidget::hide);

    QPushButton * statButton = this->findChild<QPushButton *>(QString("statButton"));
    connect(statButton, &QPushButton::clicked, this, &MainWindow::displayStats);
    connect(statButton, &QPushButton::clicked, startWidget, &QWidget::hide);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displaySurvey()
{
    this->surveyWidget = new SurveyWizard();
    connect(surveyWidget, &SurveyWizard::finished, startWidget, &QWidget::show);
    this->centralWidget()->layout()->addWidget(this->surveyWidget);
    this->setMinimumSize(this->surveyWidget->size());
}

void MainWindow::displayStats()
{
    this->statsWidget = new StatsWidget();
    //connect(statsWidget, &StatsWidget::finished, startWidget, &QWidget::show);
    this->centralWidget()->layout()->addWidget(this->statsWidget);
    this->setMinimumSize(this->statsWidget->size());
}
