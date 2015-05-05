#include "surveywizard.h"
#include "ui_surveywizard.h"

#include "slaveslider.h"
#include "slavespinbox.h"

SurveyWizard::SurveyWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::SurveyWizard)
{
    ui->setupUi(this);

    this->setButtonText(QWizard::BackButton, QString("Précédent"));
    this->setButtonText(QWizard::NextButton, QString("Suivant"));
    this->setButtonText(QWizard::CancelButton, QString("Annuler"));
    this->setButtonText(QWizard::FinishButton, QString("Valider et imprimer le bon"));


    connect(this->findChild<QRadioButton *>(QString("radioButtonSexeHomme")), &QRadioButton::toggled, this, &SurveyWizard::changeNamesToMale);
    connect(this->findChild<QRadioButton *>(QString("radioButtonSexeFemme")), &QRadioButton::toggled, this, &SurveyWizard::changeNamesToFemale);

    connect(this->findChild<QCheckBox *>(QString("aubonlaitCheck")), &QCheckBox::toggled, this, &SurveyWizard::activateAubonlait);
    connect(this->findChild<QCheckBox *>(QString("danoneCheck")), &QCheckBox::toggled, this, &SurveyWizard::activateDanone);
    connect(this->findChild<QCheckBox *>(QString("yoplaitCheck")), &QCheckBox::toggled, this, &SurveyWizard::activateYoplait);
    connect(this->findChild<QCheckBox *>(QString("lactelCheck")), &QCheckBox::toggled, this, &SurveyWizard::activateLactel);


    for (int i = 1; i <= 8; i++) {
        QSlider * master = this->page(3)->findChild<QSlider *>(QString("master_%0").arg(i));
        SlaveSlider * slaveSlider = this->page(4)->findChild<SlaveSlider *>(QString("slaveSlider_%0").arg(i));
        SlaveSpinBox * slaveSpin = this->page(4)->findChild<SlaveSpinBox *>(QString("slaveSpinBox_%0").arg(i));
        connect(master, &QSlider::valueChanged, slaveSlider, &SlaveSlider::changeMax);
        connect(master, &QSlider::valueChanged, slaveSpin, &SlaveSpinBox::changeMax);
    }

}

SurveyWizard::~SurveyWizard()
{
    delete ui;
}

void SurveyWizard::changeNamesToMale()
{
    this->findChild<QRadioButton *>(QString("radioButtonMarie"))->setText("Marié");
    this->findChild<QRadioButton *>(QString("radioButtonVeuf"))->setText("Veuf");
}

void SurveyWizard::changeNamesToFemale()
{
    this->findChild<QRadioButton *>(QString("radioButtonMarie"))->setText("Mariée");
    this->findChild<QRadioButton *>(QString("radioButtonVeuf"))->setText("Veuve");
}

void SurveyWizard::activateAubonlait(bool activate)
{
    QList<QRadioButton *> list = this->findChildren<QRadioButton *>(QRegularExpression("aubonlait"));

    for (auto ite = list.begin(); ite != list.end(); ite++) {
        (*ite)->setEnabled(activate);
    }
}

void SurveyWizard::activateDanone(bool activate)
{
    QList<QRadioButton *> list = this->findChildren<QRadioButton *>(QRegularExpression("danone"));

    for (auto ite = list.begin(); ite != list.end(); ite++) {
        (*ite)->setEnabled(activate);
    }
}

void SurveyWizard::activateYoplait(bool activate)
{
    QList<QRadioButton *> list = this->findChildren<QRadioButton *>(QRegularExpression("yoplait"));

    for (auto ite = list.begin(); ite != list.end(); ite++) {
        (*ite)->setEnabled(activate);
    }
}

void SurveyWizard::activateLactel(bool activate)
{
    QList<QRadioButton *> list = this->findChildren<QRadioButton *>(QRegularExpression("lactel"));

    for (auto ite = list.begin(); ite != list.end(); ite++) {
        (*ite)->setEnabled(activate);
    }
}
