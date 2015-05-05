#ifndef SURVEYWIZARD_H
#define SURVEYWIZARD_H

#include <QWizard>

namespace Ui {
class SurveyWizard;
}

class SurveyWizard : public QWizard
{
    Q_OBJECT

public:
    explicit SurveyWizard(QWidget *parent = 0);
    ~SurveyWizard();

private:
    Ui::SurveyWizard *ui;

private slots:
    void changeNamesToFemale();
    void changeNamesToMale();
    void activateAubonlait(bool activate);
    void activateDanone(bool activate);
    void activateYoplait(bool activate);
    void activateLactel(bool activate);
};

#endif // SURVEYWIZARD_H
