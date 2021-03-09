#include "capaciteuplink.h"

CapaciteUplink::CapaciteUplink(QObject *parent) : QObject(parent)
{
    facteurChargeSysteme = 0;
    debitBinaireRequis = 0;
    bandePassante = 0;
    nombreBlocRessource = 0;

    nombreBlocRessourceAttribueCanal = 0;
    debitBinaireParBloc = 0;
    _RArgUL = 0;
    debitCellule = 0;
}

void CapaciteUplink::setValue(double qul, double rreq, double bp, double npucc)
{
    facteurChargeSysteme = qul;
    debitBinaireRequis = rreq;
    bandePassante = bp;
    nombreBlocRessource = choixNombreBlocRessource (bandePassante);

    nombreBlocRessourceAttribueCanal = npucc;
    debitBinaireParBloc = calculDebitBinaireBloc ();
    _RArgUL = calculRAUL ();
    debitCellule = calculDebitCellul ();
}

QVector<Model> CapaciteUplink::modelUplink()
{
    QString param[8] = {"Facteur Charge système", "Débit binaire Réquise",
                      "Bande passante Uplink", "Nombre de bloc ressource",
                      "Nombre de bloc ressource attribué au canal",
                      "Débit binaire par bloc", "RArgUL", "Débit de cellule"};
    QVector<Model> models;
    for (int i = 0; i < param->size (); i++) {
        Model model;
        switch (i) {
        case 0:
            model.parametre = param[i];
            model.valeur = facteurChargeSysteme;
        break;
        case 1:
            model.parametre = param[i];
            model.valeur = debitBinaireRequis;
        break;
        case 2:
            model.parametre = param[i];
            model.valeur = bandePassante;
        break;
        case 3:
            model.parametre = param[i];
            model.valeur = nombreBlocRessource;
        break;
        case 4:
            model.parametre = param[i];
            model.valeur = nombreBlocRessourceAttribueCanal;
        break;
        case 5:
            model.parametre = param[i];
            model.valeur = debitBinaireParBloc;
        break;
        case 6:
            model.parametre = param[i];
            model.valeur = _RArgUL;
        break;
        case 7:
            model.parametre = param[i];
            model.valeur = debitCellule;
        break;
        default:
            break;
        }
        models.push_back (model);
    }
    return models;
}

CapaciteUplink::~CapaciteUplink()
{
}

double CapaciteUplink::calculDebitBinaireBloc()
{
    return debitBinaireRequis / nombreBlocRessource;
}

double CapaciteUplink::calculRAUL()
{
    return debitBinaireParBloc * (nombreBlocRessource - nombreBlocRessourceAttribueCanal);
}

double CapaciteUplink::calculDebitCellul()
{
    return facteurChargeSysteme * _RArgUL;
}

double CapaciteUplink::choixNombreBlocRessource(double bp)
{
    if (bp >= 1.4 || bp < 3)
         return 6;
    else if (bp >= 3 || bp < 5)
         return 15;
    else if (bp >= 5 || bp < 10)
         return 25;
    else if (bp >= 10 || bp < 15)
         return 50;
    else if (bp >= 15 || bp < 20)
         return 75;
    else if (bp >= 20)
         return 100;
    else
         return 0;
}
