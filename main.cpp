#include "mainwindow.h"
#include "surveywizard.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*MainWindow w;
    w.show();*/
    SurveyWizard wizard;
    wizard.show();

    return a.exec();
}
