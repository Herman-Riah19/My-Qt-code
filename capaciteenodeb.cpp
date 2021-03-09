#include "capaciteenodeb.h"
#include <QObject>

CapaciteENodeB::CapaciteENodeB(QObject *parent):
    QObject (parent)
{
    puissanceSignalUtil = 0;
    interferenceCellule = 0;
    debitBinaire = 0;
    rapportSignalInterference = 0;

    energieSignalUtil = 0;
    debitInfoUtil = 0;
    energieBruit = 0;
    bandePassante = 0;
    qualiteService = 0;
    gainTraitement = 0;

    facteurInterference = 0;
    facteurActivite = 0;

    MMax = 0;
}

void CapaciteENodeB::setValue(double puissSU, double interSU, double debit, double energSU, double debitIU, double enerBruit, double bp, double f, double vi)
{
    puissanceSignalUtil = puissSU;
    interferenceCellule = interSU;
    debitBinaire = debit;
    rapportSignalInterference = calculCIR_1 ();

    energieSignalUtil = energSU;
    debitInfoUtil = debitIU;
    energieBruit = enerBruit;
    bandePassante = bp;
    qualiteService = calculQualiteService_1 ();
    gainTraitement = calculGainTraitement_1 ();

    facteurInterference = f;
    facteurActivite = vi;

    MMax = capaciteMaximal ();
}

CapaciteENodeB::~CapaciteENodeB()
{
}

double CapaciteENodeB::calculCIR_1()
{
    return puissanceSignalUtil * interferenceCellule * debitBinaire;
}

double CapaciteENodeB::calculCIR_2()
{
    return qualiteService / gainTraitement;
}

double CapaciteENodeB::EnergieBitDonnee()
{
    return energieSignalUtil / debitInfoUtil;
}

double CapaciteENodeB::energieBruitParHertz()
{
    return energieBruit / bandePassante;
}

double CapaciteENodeB::calculQualiteService_1()
{
    return EnergieBitDonnee () / energieBruitParHertz ();
}

double CapaciteENodeB::calculQualiteService_2()
{
    return gainTraitement * rapportSignalInterference;
}

double CapaciteENodeB::calculGainTraitement_1()
{
    return bandePassante / debitInfoUtil;
}

double CapaciteENodeB::calculGainTraitement_2()
{
    return qualiteService / rapportSignalInterference;
}

double CapaciteENodeB::capaciteMaximal()
{
    return (1 / (1 + facteurInterference)) * (1 + (1 / (rapportSignalInterference * facteurActivite)));
}

QVector<Model> CapaciteENodeB::modelEnodeB() const
{
    QString param[13] = { "Puissance Signal Utile", "Interférence Cellule",
                      "Debit binaire", "Energie Signal Utile",
                      "Débit des informations utiles", "Energie à Bruit",
                      "Bande passante EnodeB", "Facteur interférence",
                      "Facteur d'activité", "Qualité de Service",
                      "Gain de traitement", "Rapport signal interférence",
                      "Capacité Maximal d'ENodeB"};
    QVector<Model> models;

    for (int i = 0; i < param->size (); i++) {
        Model model;
        switch (i) {
        case 0:
            model.parametre = param[i];
            model.valeur = puissanceSignalUtil;
        break;
        case 1:
            model.parametre = param[i];
            model.valeur = interferenceCellule;
        break;
        case 2:
            model.parametre = param[i];
            model.valeur = debitBinaire;
        break;
        case 3:
            model.parametre = param[i];
            model.valeur = energieSignalUtil;
        break;
        case 4:
            model.parametre = param[i];
            model.valeur = debitInfoUtil;
        break;
        case 5:
            model.parametre = param[i];
            model.valeur = energieBruit;
        break;
        case 6:
            model.parametre = param[i];
            model.valeur = bandePassante;
        break;
        case 7:
            model.parametre = param[i];
            model.valeur = facteurInterference;
        break;
        case 8:
            model.parametre = param[i];
            model.valeur = facteurActivite;
        break;
        case 9:
            model.parametre = param[i];
            model.valeur = qualiteService;
        break;
        case 10:
            model.parametre = param[i];
            model.valeur = gainTraitement;
        break;
        case 11:
            model.parametre = param[i];
            model.valeur = rapportSignalInterference;
        break;
        case 12:
            model.parametre = param[i];
            model.valeur =  MMax;
        break;
        default:
            break;
        }
        models.push_back (model);
    }

    return models;
}
