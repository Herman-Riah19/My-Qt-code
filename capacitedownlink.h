#ifndef CAPACITEDOWNLINK_H
#define CAPACITEDOWNLINK_H

#include <QObject>
#include "tablemodel.h"
#include "capaciteuplink.h"

class CapaciteDownlink : public QObject
{
    Q_OBJECT
public:
    explicit CapaciteDownlink(QObject *parent = nullptr);

    void setPertes (double blnf, double lb, double lcl, double lbp, double ga, double lj, double p, double su);
    void setPuissances (double nf, double wrb, double f, double qdl, double h, double na, double nt = 7);

    void calculBdlNoise ();
    void calculRapportSignalInterferenceBruit (double hm = 0);
    void calculBruitDownlink (double nrb);
    void calculAttenuationSignalDownlink ();
    void calculPerteMaximumTrajetAutorise ();
    void calculPuissanceUplink (double nrb);
    void calculDebitUsagerCellule (CapaciteUplink *uplink);
    void calculDebitCellule ();
    void calculDebitSite ();
    void calculNombreSite ();

    double getDebitUser () { return DebitUser; }
    void setDebitUser (double debit) { DebitUser = debit; }

    double getBdlNoise () { return BdlNoise; }
    double RapportSignalInterferenceBruit () { return SINR; }
    double BruitDownlink () { return BIDl; }
    double AttenuationSignalDownlink () { return Lsamax; }
    double PerteMaximumTrajetAutorise () { return Lpmax; }
    double getNombreDl () { return NombreDl; }
    double getFacteurChargeDl () { return Qdl; }
    double PuissanceUplink () { return Ptx; }
    double getDebitUsagerCellule () { return Ruser; }
    double getDebitCellule () { return DebitCellule; }
    double getDebitSite () { return DebitSite; }
    int getNombreSite () {
        int nbr = static_cast<int>(ceil (NombreSite));
        return nbr;
    }

    QVector<Model> modelDownlink () const;
    ~CapaciteDownlink ();
private:
    double calculNombreDl ();

    double SINR;//
    double BdlNoise, Lsamax, NombreDl, Ptx, Lpmax, Qdl, BIDl;//
    double Ruser, DebitUser, DebitCellule;//
    double DebitSite;
    int NombreSite;

    double F, Blnf, Lb, Lcl, Lbp, Ga, Lj;//
    double SensUE, H;//
    double Nt, Nf, Wrb, p;//
    double NombreAbonne;//

public:
    double getF() { return F; }
    double getBlnf () { return Blnf; }
    double getLB () { return Lb; }
    double getLCl () { return Lcl; }
    double getLBP () { return Lbp; }
    double getGa () { return Ga; }
    double getLJ () { return Lj; }

    double getSensibiliteRecepteur () { return SensUE; }
    double getH () { return H; }
    double getNt () { return Nt; }
    double getNf () { return Nf; }
    double getWrb () { return Wrb; }
    double getPuissance () { return p; }
    double getNombreAbonne () { return NombreAbonne; }
};

#endif // CAPACITEDOWNLINK_H
