#include "dimensionnementcapacitewidget.h"
#include "ui_dimensionnementcapacitewidget.h"

#include <iostream>
#include <QMessageBox>
using namespace std;

DimensionnementCapaciteWidget::DimensionnementCapaciteWidget(double hm, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DimensionnementCapaciteWidget)
{
    ui->setupUi(this);
    ui->toolBox->setCurrentIndex (0);

    hauteurMobile = hm;
    ENodeB = new CapaciteENodeB (this);
    Uplink = new CapaciteUplink (this);
    Downlink = new CapaciteDownlink (this);

    connect (ui->btnValiderENodeB, &QPushButton::clicked, this, &DimensionnementCapaciteWidget::ENodeBCalcul);
    connect (ui->btnValiderUplink, &QPushButton::clicked, this, &DimensionnementCapaciteWidget::UplinkCalcul);
    connect (ui->btnValiderDownlink1, &QPushButton::clicked, this, &DimensionnementCapaciteWidget::DownlinkCalcul1);
    connect (ui->btnValiderDownlink2, &QPushButton::clicked, this, &DimensionnementCapaciteWidget::DownlinkCalcul2);
}

DimensionnementCapaciteWidget::~DimensionnementCapaciteWidget()
{
    delete ui;
    delete ENodeB;
    delete Uplink;
    delete Downlink;
}

void DimensionnementCapaciteWidget::ENodeBCalcul()
{
    double puissSU = ui->linePuissSU->text ().toDouble ();
    double InterCell = ui->lineInterCellule->text ().toDouble ();
    double debitBinaire = ui->lineDebitBinaire->text ().toDouble ();

    double energSu = ui->lineEnergieSU->text ().toDouble ();
    double debitInfo = ui->lineDebitInfoUtil->text ().toDouble ();
    double energBruit = ui->lineEnergieBruit->text ().toDouble ();
    double bandePass = ui->lineBandePassante->text ().toDouble ();

    double factInter = ui->lineFacteurInterference->text ().toDouble ();
    double factAct = ui->lineFacteurActivite->text ().toDouble ();

    ENodeB->setValue (puissSU, InterCell, debitBinaire, energSu, debitInfo, energBruit, bandePass, factInter, factAct);

    cout << "CIR : " << ENodeB->CIR () << endl << "QoS : " << ENodeB->QualiteService () << endl;
    cout << "Gain traitement : " << ENodeB->GainTraitement () << endl << "Capacite max : " << ENodeB->CapaciteMMaximal () << endl;

    emit sendENodeB (ENodeB);
}

void DimensionnementCapaciteWidget::UplinkCalcul()
{
    double facteurCharge = ui->lineFacteurCharge->text ().toDouble ();
    double bpUplink = ui->lineBPUplink->text ().toDouble ();
    double debitBinaire = ui->lineDebitBinaireRequise->text ().toDouble ();
    double nPuccc = ui->lineNombrePUCC->text ().toDouble ();

    Uplink->setValue (facteurCharge, debitBinaire, bpUplink, nPuccc);
    cout << "Debit cellule: " << Uplink->DebitCellule () << endl << "RRAgr : " << Uplink->RArgUL () << endl;
    cout << "Debit Binaire par bloc: " << Uplink->DebitBinaireBloc () << endl;
    cout << "Facteur charge systeme: " << Uplink->FacteurChargeSysteme () << endl;

    emit sendUplink (Uplink);
}

void DimensionnementCapaciteWidget::DownlinkCalcul1()
{
    double margeEva = ui->lineMargeEvanoissement->text ().toDouble ();
    double perteCorp = ui->linePerteCorps->text ().toDouble ();
    double perteVoiture = ui->linePerteVoiture->text ().toDouble ();
    double perteBat = ui->linePerteBatiment->text ().toDouble ();
    double sommeGain = ui->lineSommeGain->text ().toDouble ();
    double sommePuissance = ui->lineSommePuissance->text ().toDouble ();
    double sensRecepteur = ui->lineSensRecepteur->text ().toDouble ();
    double jumper = ui->lineJumper->text ().toDouble ();

    Downlink->setPertes (margeEva, perteCorp, perteVoiture, perteBat, sommeGain, jumper, sommePuissance, sensRecepteur);
    Downlink->calculPuissanceUplink (Uplink->NombreBlocRessource ());

    cout << "Puissance Uplink: " << Downlink->PuissanceUplink () << endl;
}

void DimensionnementCapaciteWidget::DownlinkCalcul2()
{
    double densitePuiss = ui->lineDensitePuiss->text ().toDouble ();
    double facteurBruit = ui->lineFacteurBruit->text ().toDouble ();
    double bpBlocRessource = ui->lineBPBlocRessource->text ().toDouble ();
    double facteurChargeDown = ui->lineFactCharDown->text ().toDouble ();
    double facteurAffaibliss = ui->lineFactAffaiblProp->text ().toDouble ();
    double ratioMoyenne = ui->lineRayonMoyenne->text ().toDouble ();
    double nombreAbonne = ui->lineNombreAbonne->text ().toDouble ();
    double debitUtilisateur = ui->lineDebitUtilisateur->text ().toDouble ();

    Downlink->setPuissances (facteurBruit, bpBlocRessource, ratioMoyenne, facteurChargeDown, facteurAffaibliss, nombreAbonne, densitePuiss);
    Downlink->setDebitUser (debitUtilisateur);
    cout << "Debit utilisateur: " << Downlink->getDebitUser () << endl;

    Downlink->calculBruitDownlink (Uplink->NombreBlocRessource ());
    Downlink->calculPerteMaximumTrajetAutorise ();
    Downlink->calculAttenuationSignalDownlink ();
    Downlink->calculBdlNoise ();
    Downlink->calculRapportSignalInterferenceBruit (hauteurMobile);
    Downlink->calculDebitUsagerCellule (Uplink);
    Downlink->calculDebitSite ();
    Downlink->calculNombreSite ();

    cout << "Debit utilisateur par cellule: " << Downlink->getDebitUsagerCellule () << endl;
    cout << "Bruit downlink: " << Downlink->BruitDownlink () << endl;

    emit sendDownlink (Downlink);
}
