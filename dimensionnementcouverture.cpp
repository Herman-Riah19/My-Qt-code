#include "dimensionnementcouverture.h"
#include "ui_dimensionnementcouverture.h"
#include "propagationclass.h"

#include <iostream>
#include <QtWidgets>
using namespace std;

DimensionnementCouverture::DimensionnementCouverture(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DimensionnementCouverture)
{
    ui->setupUi(this);

    mapl = new MAPLClass (this);
    propagation = new PropagationClass (this);

    connect (ui->m_boutonValide1, &QPushButton::clicked, this, &DimensionnementCouverture::MAPL);
    connect (ui->m_boutonValider2, &QPushButton::clicked, this, &DimensionnementCouverture::RayonEtNombreSite);
}

DimensionnementCouverture::~DimensionnementCouverture()
{
    delete ui;
    delete mapl;
    delete propagation;
}

void DimensionnementCouverture::MAPL()
{
   double ptx = ui->linePTX->text ().toDouble ();
   double ltx = ui->lineLTX->text ().toDouble ();
   double gtx = ui->lineGTX->text ().toDouble ();
   double pm = ui->linePM->text ().toDouble ();
   double sensrx = ui->lineSensRX->text ().toDouble ();
   double lrx = ui->lineLRX->text ().toDouble ();
   double grx = ui->lineGRX->text ().toDouble ();

   mapl->setValue (ptx, ltx, gtx, sensrx, lrx, grx, pm);
   cout << "MALP : " << mapl->mapl () << endl;

   emit sendMapl (mapl);
}

void DimensionnementCouverture::RayonEtNombreSite()
{
    double _mapl = mapl->mapl ();
    double fr = ui->lineFrequence->text ().toDouble ();
    double hb = ui->lineHb->text ().toDouble ();
    double hm = ui->lineHm->text ().toDouble ();
    double d = ui->lineDistances->text ().toDouble ();

    Environnement env = choixEnvironnement ();
    Propagation type = typePropagation ();

    propagation->setValue (_mapl, fr, hb, hm, d, type, env);
    cout << "Rayon : " << propagation->Rayon () << endl << "Nombre site : " << propagation->NombreSite () << endl;

    emit sendPropagation (propagation);
}

Environnement DimensionnementCouverture::choixEnvironnement()
{
    Environnement env = Zone_Urbain;
    if (ui->radioUrbain->isChecked ())
        env = Zone_Urbain;
    if (ui->radioUrbainDense->isChecked ())
        env = Zone_Urbain_Dense;
    if (ui->radioSuburbain->isChecked ())
        env = Zone_Suburbain;
    if (ui->radioRural->isChecked ())
        env = Zone_rurale;

    return env;
}

Propagation DimensionnementCouverture::typePropagation()
{
    Propagation type = Okumura_Hata;
    if (ui->radioOkumura->isChecked ())
        type = Okumura_Hata;
    if (ui->radioCost231->isChecked ())
        type = COST231_Hata;

    return type;
}
