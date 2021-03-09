#include "capacitedownlink.h"

#include <QtWidgets>

CapaciteDownlink::CapaciteDownlink(QObject *parent) : QObject(parent)
{
    this->Blnf = 0;
    this->Lb = 0;
    this->Lcl = 0;
    this->Lbp = 0;
    this->Ga = 0;
    this->Lj = 0;

    this->SensUE = 0;
    this->H = 0;

    this->Nt = 0;
    this->Nf = 0;
    this->p = 0;
    this->F = 0;
    this->Wrb = 0;
    this->NombreAbonne = 0;

    this->Ptx = 0;
    this->NombreDl = 0;
    this->BIDl = 0;

    this->Lpmax = 0;
    this->Lsamax = 0;
    this->BdlNoise = 0;
    this->SINR = 0;

    this->DebitSite = 0;
    this->NombreSite = 0;
}

void CapaciteDownlink::setPertes(double blnf, double lb, double lcl, double lbp, double ga, double lj, double p, double su)
{
    this->Blnf = blnf;
    this->Lb = lb;
    this->Lcl = lcl;
    this->Lbp = lbp;
    this->Ga = ga;
    this->Lj = lj;

    this->p = p;

    this->SensUE = su;
}

void CapaciteDownlink::setPuissances(double nf, double wrb, double f, double qdl, double h, double na, double nt)
{
    this->Nt = nt;
    this->Nf = nf;
    this->Wrb = wrb;
    this->F = f;
    this->Qdl = qdl;
    this->H = h;

    this->NombreAbonne = na;

    this->NombreDl = calculNombreDl();
}

QVector<Model> CapaciteDownlink::modelDownlink () const
{
    QString param[27] = {"Log-normal marge d'évanoissement", "Perte de corps", "Perte de pénétration de voiture",
                         "Perte de pénétration de bâtiment", "Gain d'antenne ENodeB", "Jumper et connecteur d'antenne",
                         "Puissance de l'émetteur", "Sensibilité d'équipement utilisateur", "Densité de puissance",
                         "Facteur de bruit", "Bande passante par bloc ressource", "Ratio moyenne de puissance reçue d'autre cellule",
                         "Facteur de charge Downlink", "Facteur d'affaiblissement de propagation", "Nombre des abonnées",
                         "Bruit thermique par bloc ressource", "BdlNoise", "Rapport signal interférence bruit (SINR)",
                         "Buit Downlink", "Atténuation du signal Downlink", "Perte maximum de trajet autorisé", "Puissance Uplink",
                         "Débit usagé de cellule", "Débit de cellule", "Débit des utilisateurs", "Débit de site", "Nombre de site"};

    QVector<Model> models;
    for (int i = 0; i < param->size (); i++) {
        Model model;
        switch (i) {
        case 0:
            model.parametre = param[i];
            model.valeur = Blnf;
            break;
        case 1:
            model.parametre = param[i];
            model.valeur = Lb;
            break;
        case 2:
            model.parametre = param[i];
            model.valeur = Lcl;
            break;
        case 3:
            model.parametre = param[i];
            model.valeur = Lbp;
            break;
        case 4:
            model.parametre = param[i];
            model.valeur = Ga;
            break;
        case 5:
            model.parametre = param[i];
            model.valeur = Lj;
            break;
        case 6:
            model.parametre = param[i];
            model.valeur = p;
            break;
        case 7:
            model.parametre = param[i];
            model.valeur = SensUE;
            break;
        case 8:
            model.parametre = param[i];
            model.valeur = Nt;
            break;
        case 9:
            model.parametre = param[i];
            model.valeur = Nf;
            break;
        case 10:
            model.parametre = param[i];
            model.valeur = Wrb;
            break;
        case 11:
            model.parametre = param[i];
            model.valeur = F;
            break;
        case 12:
            model.parametre = param[i];
            model.valeur = Qdl;
            break;
        case 13:
            model.parametre = param[i];
            model.valeur = H;
            break;
        case 14:
            model.parametre = param[i];
            model.valeur = NombreAbonne;
            break;
        case 15:
            model.parametre = param[i];
            model.valeur = NombreDl;
            break;
        case 16:
            model.parametre = param[i];
            model.valeur = BdlNoise;
            break;
        case 17:
            model.parametre = param[i];
            model.valeur = SINR;
            break;
        case 18:
            model.parametre = param[i];
            model.valeur = BIDl;
            break;
        case 19:
            model.parametre = param[i];
            model.valeur = Lsamax;
            break;
        case 20:
            model.parametre = param[i];
            model.valeur = Lpmax;
            break;
        case 21:
            model.parametre = param[i];
            model.valeur = Ptx;
            break;
        case 22:
            model.parametre = param[i];
            model.valeur = Ruser;
            break;
        case 23:
            model.parametre = param[i];
            model.valeur = DebitCellule;
            break;
        case 24:
            model.parametre = param[i];
            model.valeur = DebitUser;
            break;
        case 25:
            model.parametre = param[i];
            model.valeur = DebitSite;
            break;
        case 26:
            model.parametre = param[i];
            model.valeur = NombreSite;
            break;
        default:
            break;
        }
        models.push_back (model);
    }
    return models;
}

void CapaciteDownlink::calculBdlNoise()
{
    BdlNoise = 1 + ((Ptx * Qdl * F) / (NombreDl * Lsamax));
}

void CapaciteDownlink::calculRapportSignalInterferenceBruit(double hm)
{
    SINR = BdlNoise * Ptx * hm * Lsamax * NombreDl;
}

void CapaciteDownlink::calculBruitDownlink(double nrb)
{
    BIDl = 1 + ((Ptx * Qdl * F) / (nrb * NombreDl * H * Lsamax));
}

void CapaciteDownlink::calculAttenuationSignalDownlink()
{
    Lsamax = Lpmax + Blnf + Lb + Lcl + Lbp - Ga + Lj;
}

void CapaciteDownlink::calculPerteMaximumTrajetAutorise()
{
    Lpmax = Ptx - SensUE - BIDl - Blnf - Lb - Lcl - Lbp + Ga - Lj;
}

void CapaciteDownlink::calculPuissanceUplink(double nrb)
{
    Ptx = p / nrb;
}

void CapaciteDownlink::calculDebitUsagerCellule(CapaciteUplink *uplink)
{
    Ruser = NombreDl * uplink->DebitBinaireBloc ();
}

void CapaciteDownlink::calculDebitCellule()
{
    DebitCellule = Qdl * Ruser;
}

void CapaciteDownlink::calculDebitSite()
{
    DebitSite = DebitCellule * 3;
}

void CapaciteDownlink::calculNombreSite()
{
    double nbr = (DebitUser / DebitSite) * NombreAbonne;
    NombreSite = static_cast<int>(ceil (nbr));
}

CapaciteDownlink::~CapaciteDownlink()
{
}

double CapaciteDownlink::calculNombreDl()
{
    return this->Nt + this->Nf + 10* log10 (this->Wrb);
}
