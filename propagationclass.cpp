#include "propagationclass.h"
#include "maplclass.h"

#include <QObject>
#include <QtWidgets>

PropagationClass::PropagationClass(QObject *parent):
    QObject (parent)
{
    m_mapl = 0;

    m_frequence = 0;
    m_hb = 0;
    m_hm = 0;
    m_superficieZone = 0;

    m_rayon = 0;
    m_supSite = 0;
    m_distanceSite = 0;
    m_nombreSite = 0;
}

void PropagationClass::setValue(double mapl, double fqc, double hb, double hm, double supZone, Propagation p, Environnement e)
{
    m_mapl = mapl;

    m_frequence = fqc;
    m_hb = hb;
    m_hm = hm;
    m_superficieZone = supZone;

    m_rayon = calculRayon (p, e);
    m_supSite = calculSupSite ();
    m_distanceSite = calculDistSite ();
    m_nombreSite = calculNbrSite ();
}

QString PropagationClass::typePropagation()
{
    QString type;
    if (m_propagation == Okumura_Hata) {
        type = QString ("Okumura-Hata");
    } else {
        type = QString ("Cost231-Hata");
    }

    return type;
}

PropagationClass::~PropagationClass()
{

}

double PropagationClass::calculRayon(Propagation &p, Environnement &e)
{
    double r = 0;
    if (p == Okumura_Hata) {
        r = m_mapl - 69.55 - 26.16 * log10 (m_frequence);
        r += 13.82 * log10 (m_hb) + alpha (p, e);
        if (e == Zone_Suburbain) {
            r += 2 * pow (log10 (m_frequence / 28), 2) + 54;
        } else if (e == Zone_rurale) {
            r += 4.78 * pow (log10(m_frequence), 2);
            r -= 18.33 * log10(m_frequence) + 40.94;
        }
        r /= (44.9 - 6.55 * log10 (m_hb));
        r = pow (10, r);

    } else if (p == COST231_Hata) {
        r = m_mapl - 46.3 - 33.9 * log10 (m_frequence);
        r += 13.82 * log10 (m_hb) + alpha(p, e) - choixCM(e);
        r /= (44.9 - 6.55 * log10 (m_hb));
        r = pow (10, r);
    }

    return r;
}

double PropagationClass::calculSupSite()
{
    double super = 1.95 * 2.6 * pow (Rayon(), 2); //pour une site à 3 secteurs
    return super;
}

double PropagationClass::calculDistSite()
{
    double d = 1.5 * Rayon ();
    return d;
}

int PropagationClass::calculNbrSite()
{
    double dec = ( m_superficieZone / SuperficieSite ());
    int nbr = static_cast<int>(ceil (dec));
    return nbr;
}

double PropagationClass::choixCM(Environnement e)
{
    double cm = 0;
    if (e == Zone_Urbain || e == Zone_Urbain_Dense) {
         cm = 8;
    } else if (e == Zone_Suburbain) {
         cm = 0;
    } else if (e == Zone_rurale) {
         cm = -3;
    }

    return cm;
}

double PropagationClass::alpha(Propagation p, Environnement e)
{
    double al = 0;
    if (p == Okumura_Hata) {
        if (e == Zone_Urbain) {
            al = (1.1 * log10 (m_frequence) - 0.7) * m_hm;
            al -= 1.56 * log10 (m_frequence) - 0.8;
            return al;

        } else if (e == Zone_Urbain_Dense) {
            if (m_frequence >= 2000) {
                al = 3.2 * pow (log10 (11.75 * m_hm), 2) - 4.97;
                return al;

            } else if (m_frequence <= 2000) {
                al = 8.29 * pow (log10 (1.54 * m_hm), 2) - 1.1;
                return al;

            }
        }
    } else if (p == COST231_Hata) {
        al = (1.1 * log10 (m_frequence) - 0.7) * m_hm;
        al -= 1.56 * log10 (m_frequence) - 0.8;
        return al;
    }

    return al;
}
