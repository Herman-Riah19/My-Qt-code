#ifndef CAPACITEUPLINK_H
#define CAPACITEUPLINK_H

#include <QObject>
#include "tablemodel.h"

class CapaciteUplink : public QObject
{
    Q_OBJECT
public:
    explicit CapaciteUplink(QObject *parent = nullptr);

    void setValue (double qul = 0, double rreq = 0, double bp = 0, double npucc = 0);

    double DebitCellule () { return debitCellule; }
    double RArgUL () { return _RArgUL; }
    double DebitBinaireBloc () { return debitBinaireParBloc; }
    double FacteurChargeSysteme () { return facteurChargeSysteme; }
    double NombreBlocRessource () { return nombreBlocRessource; }

    double DebitBinaireRequise() { return debitBinaireRequis; }
    double NombreBlocRessourceAttributAuCanal () { return nombreBlocRessourceAttribueCanal; }
    double BPUplink () { return bandePassante; }

    QVector<Model> modelUplink ();

    ~CapaciteUplink ();
private:
    double calculDebitBinaireBloc ();
    double calculRAUL ();
    double calculDebitCellul ();
    double choixNombreBlocRessource (double bp);


    double debitBinaireRequis;
    double nombreBlocRessource;
    double nombreBlocRessourceAttribueCanal;
    double bandePassante;

    double facteurChargeSysteme;
    double debitBinaireParBloc;
    double _RArgUL;
    double debitCellule;
};

#endif // CAPACITEUPLINK_H
