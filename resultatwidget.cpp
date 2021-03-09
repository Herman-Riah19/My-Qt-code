#include "resultatwidget.h"
#include "ui_resultatwidget.h"
#include <QtWidgets>

ResultatWidget::ResultatWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResultatWidget)
{
    ui->setupUi(this);

    mapl = new MAPLClass;
    propagation = new PropagationClass;
    enodb = new CapaciteENodeB;
    uplink = new CapaciteUplink;
    downlink = new CapaciteDownlink;

    setupProjet ("Inconnue", "inconnue", "Antananarivo", "Urbaine");
    setupCouverture ();
    setupCapacite ();
}

ResultatWidget::~ResultatWidget()
{
    delete ui;
    delete mapl;
    delete propagation;
    delete enodb;
    delete uplink;
    delete downlink;
}

void ResultatWidget::setupProjet(const QString &nom, const QString &ville, const QString &province, const QString &zone)
{
    try {
        ui->labelNomProjet->setText (nom);
        ui->labelVille->setText (ville);
        ui->labelProvince->setText (province);
        ui->labelZone->setText (zone);
    } catch (QException exception) {
        qDebug() << &exception;
    }
}

void ResultatWidget::setupCouverture()
{
    modelsCouvertures = initModelCouverture (mapl, propagation);

    TableModel *tableModel = new TableModel (modelsCouvertures);
    ui->tableCouverture->setModel (tableModel);
    ui->tableCouverture->setSizeIncrement (100, 50);
    ui->tableCouverture->setSelectionBehavior (QAbstractItemView::SelectRows);
    ui->tableCouverture->horizontalHeader ()->setStretchLastSection (true);
    ui->tableCouverture->verticalHeader ()->hide ();
    ui->tableCouverture->setEditTriggers (QAbstractItemView::NoEditTriggers);
    ui->tableCouverture->setSelectionMode (QAbstractItemView::SingleSelection);
    ui->tableCouverture->setSortingEnabled (true);

    ui->labelNombreSiteCouverture->setText (QString::number (modelsCouvertures[15].valeur));
}

void ResultatWidget::setupCapacite()
{
    modelsCapacites = initModelCapacite (enodb, uplink, downlink);

    TableModel *tableModel = new TableModel (modelsCapacites);

    ui->tableCapacite->setModel (tableModel);
    ui->tableCapacite->setSelectionBehavior (QAbstractItemView::SelectRows);
    ui->tableCapacite->horizontalHeader ()->setStretchLastSection (true);
    ui->tableCapacite->verticalHeader ()->hide ();
    ui->tableCapacite->setEditTriggers (QAbstractItemView::NoEditTriggers);
    ui->tableCapacite->setSelectionMode (QAbstractItemView::SingleSelection);
    ui->tableCapacite->setSortingEnabled (true);

    ui->labelNombreSiteCapacite->setText (QString::number (modelsCapacites[modelsCapacites.size ()-1].valeur));
}

void ResultatWidget::ouvrirDialog()
{
    DialogNewProject dialg;
    if (dialg.exec ()) {
        return;
    }
}

void ResultatWidget::receptionMapl(MAPLClass *m)
{
    mapl = m;
    setupCouverture ();
}

void ResultatWidget::receptionPropagation(PropagationClass *prop)
{
    propagation = prop;
    ui->labelPropagation->setText (QString ("\"%1\"").arg(propagation->typePropagation ()));
    setupCouverture ();
}

void ResultatWidget::receptionENodeB(CapaciteENodeB *enode)
{
    enodb = enode;
    setupCapacite ();
}

void ResultatWidget::receptionUplink(CapaciteUplink *up)
{
    uplink = up;
    setupCapacite ();
}

void ResultatWidget::receptionDownlink(CapaciteDownlink *down)
{
    downlink = down;
    setupCapacite ();
}

QVector<Model> ResultatWidget::initModelCouverture(MAPLClass *mapl, PropagationClass *prop)
{
    QVector<Model> models;
    QString param[16] = {"Puissance Emetteur", "Perte Emetteur", "Gain Emetteur",
                       "Sensibilite Recepteur", "Perte Recepteur", "Gain Recepteur",
                       "Marge de planification", "MALP", "Frequence", "Hauteur Mobile",
                       "Hauteur Antenne", "Superficie de zone", "Rayon", "Superficie de site",
                       "Distance entre site", "Nombre de site"};
    for (int i = 0; i < param->size(); ++i) {
        Model model;
        switch (i) {
        case 0:
            model.parametre = param[i];
            model.valeur = mapl->puissanceEmetteur ();
            break;
        case 1:
            model.parametre = param[i];
            model.valeur = mapl->perteEmetteur ();
            break;
        case 2:
            model.parametre = param[i];
            model.valeur = mapl->gainEmetteur ();
            break;
        case 3:
            model.parametre = param[i];
            model.valeur = mapl->sensibiliteRecepteur ();
            break;
        case 4:
            model.parametre = param[i];
            model.valeur = mapl->perteRecepteur ();
            break;
        case 5:
            model.parametre = param[i];
            model.valeur = mapl->gainRecepteur ();
            break;
        case 6:
            model.parametre = param[i];
            model.valeur = mapl->margePlanification ();
            break;
        case 7:
            model.parametre = param[i];
            model.valeur = mapl->mapl ();
            break;
        case 8:
            model.parametre = param[i];
            model.valeur = prop->Frequence ();
            break;
        case 9:
            model.parametre = param[i];
            model.valeur = prop->HauteurMobile ();
            break;
        case 10:
            model.parametre = param[i];
            model.valeur = prop->HauteurAntenne ();
            break;
        case 11:
            model.parametre = param[i];
            model.valeur = prop->SuperficieZone ();
            break;
        case 12:
            model.parametre = param[i];
            model.valeur = prop->Rayon ();
            break;
        case 13:
            model.parametre = param[i];
            model.valeur = prop->SuperficieSite ();
            break;
        case 14:
            model.parametre = param[i];
            model.valeur = prop->DistanceSite ();
            break;
        case 15:
            model.parametre = param[i];
            model.valeur = prop->NombreSite ();
            break;
        }
        models.push_back (model);
    }
    return models;
}

QVector<Model> ResultatWidget::initModelCapacite(CapaciteENodeB *enodeb, CapaciteUplink *uplink, CapaciteDownlink *down)
{
    QVector<Model> models;
    QVector<Model> modelsENodeB = enodeb->modelEnodeB ();
    QVector<Model> modelsUplink = uplink->modelUplink ();
    QVector<Model> modelsDownlink = down->modelDownlink ();

    for (int i = 0; i < modelsENodeB.size (); i++) {
        Model model;
        model.parametre = modelsENodeB[i].parametre;
        model.valeur = modelsENodeB[i].valeur;
        models.push_back (model);
    }

    for (int j = 0; j < modelsUplink.size (); j++) {
        Model model;
        model.parametre = modelsUplink[j].parametre;
        model.valeur = modelsUplink[j].valeur;
        models.push_back (model);
    }

    for (int k = 0; k < modelsDownlink.size (); k++) {
        Model model;
        model.parametre = modelsDownlink[k].parametre;
        model.valeur = modelsDownlink[k].valeur;
        models.push_back (model);
    }

    return models;
}
