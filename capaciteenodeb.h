#ifndef CAPACITEENODEB_H
#define CAPACITEENODEB_H

#include "tablemodel.h"
#include <QObject>

class CapaciteENodeB: public QObject
{
    Q_OBJECT
public:
    CapaciteENodeB(QObject *parent = nullptr);

    void setValue (double puissSU = 0, double interSU = 0, double debit = 0, double energSU = 0, double debitIU = 0, double enerBruit = 0, double bp = 0, double f = 0, double vi = 0);

    double QualiteService () { return qualiteService; }
    double GainTraitement () { return gainTraitement; }
    double CIR () { return rapportSignalInterference; }
    double CapaciteMMaximal () { return MMax; }

    double getPuissanceSU () { return puissanceSignalUtil; }
    double getInterferenceCellule () { return interferenceCellule; }
    double getDebitBinaire () { return debitBinaire; }
    double getEnergieSU () { return energieSignalUtil; }
    double getDebitIU () { return debitInfoUtil; }
    double getEnergieBruit () { return energieBruit; }
    double getBP () { return bandePassante; }
    double getFacteurInterference () { return facteurInterference; }
    double getFacteurActivite () { return facteurActivite; }

    QVector<Model> modelEnodeB () const;

    ~CapaciteENodeB ();
private:
    //les methodes de calcul
    double calculCIR_1();
    double calculCIR_2();

    double EnergieBitDonnee ();
    double energieBruitParHertz ();

    double calculQualiteService_1 ();
    double calculQualiteService_2 ();

    double calculGainTraitement_1 ();
    double calculGainTraitement_2 ();

    double capaciteMaximal ();

    //CIR property
    double rapportSignalInterference; // CIR
    double puissanceSignalUtil;
    double interferenceCellule;
    double debitBinaire;

    double qualiteService, gainTraitement; // Eo/No et SF
    double energieSignalUtil;
    double debitInfoUtil;
    double energieBruit;
    double bandePassante;

    double MMax;
    double facteurInterference, facteurActivite; // f et vi
};

#endif // CAPACITEENODEB_H
