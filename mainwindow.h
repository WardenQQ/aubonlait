#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "surveywizard.h"
#include "statswidget.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QWidget *startWidget;
    SurveyWizard *surveyWidget;
    StatsWidget *statsWidget;

private slots:
    void displaySurvey();
    void displayStats();
};

#endif // MAINWINDOW_H
