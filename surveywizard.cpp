#include "surveywizard.h"
#include "ui_surveywizard.h"

#include "slaveslider.h"
#include "slavespinbox.h"

#include <QSqlQuery>

SurveyWizard::SurveyWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::SurveyWizard)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Widget);

    this->setButtonText(QWizard::BackButton, QString("Précédent"));
    this->setButtonText(QWizard::NextButton, QString("Suivant"));
    this->setButtonText(QWizard::CancelButton, QString("Annuler"));
    this->setButtonText(QWizard::FinishButton, QString("Valider et imprimer le bon"));


    connect(this->findChild<QRadioButton *>(QString("radioButtonSexeHomme")), &QRadioButton::toggled, this, &SurveyWizard::changeNamesToMale);
    connect(this->findChild<QRadioButton *>(QString("radioButtonSexeFemme")), &QRadioButton::toggled, this, &SurveyWizard::changeNamesToFemale);

    connect(this, &SurveyWizard::accepted, this, &SurveyWizard::saveSurvey);


    for (int i = 1; i <= 8; i++) {
        QSlider * master = this->findChild<QSlider *>(QString("master_%0").arg(i));
        SlaveSlider * slaveSlider = this->findChild<SlaveSlider *>(QString("slaveSlider_%0").arg(i));
        SlaveSpinBox * slaveSpin = this->findChild<SlaveSpinBox *>(QString("slaveSpinBox_%0").arg(i));
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

void SurveyWizard::saveSurvey()
{
    QSqlQuery q;
    q.prepare("INSERT INTO sonde (sexe, age, etat_civil, revenu, nb_adultes, nb_enfants, nb_animaux) "
              " VALUES (:sexe, :age, :etat_civil, :revenu, :nb_adultes, :nb_enfants, :nb_animaux)");
    q.bindValue(":sexe", this->findChild<QButtonGroup *>(QString("sexGroup"))->checkedId() * (-1) -2 );
    q.bindValue(":age", this->findChild<QSpinBox *>(QString("ageSpinBox"))->value());
    q.bindValue(":etat_civil", this->findChild<QButtonGroup *>(QString("etatCivilGroup"))->checkedId() * (-1) -2 );
    q.bindValue(":revenu", this->findChild<QComboBox *>(QString("revenuComboBox"))->currentIndex());
    q.bindValue(":nb_adultes", this->findChild<QSpinBox *>(QString("adultesSpinBox"))->value());
    q.bindValue(":nb_enfants", this->findChild<QSpinBox *>(QString("enfantsSpinBox"))->value());
    q.bindValue(":nb_animaux", this->findChild<QSpinBox *>(QString("animauxSpinBox"))->value());
    q.exec();

    q.exec("SELECT last_insert_rowid();");
    q.next();
    int last_index = q.value(0).toInt();

    for (int i = 0; i < 8; i++) {
        q.prepare("INSERT INTO consommation (id_sonde, type, total, aubonlait) VALUES (?, ?, ?, ?);");
        QSpinBox * spinBox = this->findChild<QSpinBox *>(QString("slaveSpinBox_%1").arg(i + 1));
        q.addBindValue(last_index);
        q.addBindValue(i);
        q.addBindValue(spinBox->maximum());
        q.addBindValue(spinBox->value());
        q.exec();
    }

}
