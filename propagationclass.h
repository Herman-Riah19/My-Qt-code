#ifndef PROPAGATIONCLASS_H
#define PROPAGATIONCLASS_H

#include "maplclass.h"
#include <QObject>

enum Propagation{
    Okumura_Hata,
    COST231_Hata
};

enum Environnement{
    Zone_Urbain,
    Zone_Urbain_Dense,
    Zone_Suburbain,
    Zone_rurale
};

class PropagationClass : public QObject
{
    Q_OBJECT
public:
    PropagationClass (QObject *parent = nullptr);

    void setValue (double mapl = 0, double fqc = 0, double hb = 0, double hm = 0, double supZone = 0,Propagation p = Okumura_Hata, Environnement e = Zone_Urbain);

    double MAPLPropagation () { return m_mapl; }
    double Frequence () { return m_frequence; }
    double HauteurMobile () { return m_hm; }
    double HauteurAntenne () { return m_hb; }
    double SuperficieZone () { return m_superficieZone; }

    Propagation getTypePropagation () { return m_propagation; }
    Environnement getZoneEnvironnement () { return m_environnement; }

    QString typePropagation ();

    double Rayon () { return m_rayon; }
    double SuperficieSite () { return m_supSite; }
    double DistanceSite () { return m_distanceSite; }
    int NombreSite () { return m_nombreSite; }

    ~PropagationClass ();
private:
    double calculRayon (Propagation &p, Environnement &e);
    double calculSupSite ();
    double calculDistSite ();
    int calculNbrSite ();

    double choixCM (Environnement e);
    double alpha (Propagation p, Environnement e);

    double m_frequence, m_hb, m_hm;
    double m_superficieZone;

    Propagation m_propagation;
    Environnement m_environnement;

    double m_mapl;

    double m_rayon, m_supSite, m_distanceSite;
    int m_nombreSite;
};

#endif // PROPAGATIONCLASS_H
