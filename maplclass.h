#ifndef MAPLCLASS_H
#define MAPLCLASS_H

#include <QObject>

class MAPLClass: public QObject
{
    Q_OBJECT
    Q_PROPERTY (double m_mapl READ mapl WRITE setMapl)

public:
    MAPLClass(QObject *parent = nullptr);

    void setValue(double &ptx, double &ltx, double &gtx,
                  double &sens, double &lrx, double &grx, double &pm);
    double mapl() { return m_mapl; }
    void setMapl(double m) { m_mapl = m; }

    double puissanceEmetteur () { return Ptx; }
    double perteEmetteur () { return Ltx; }
    double gainEmetteur () { return Gtx; }

    double margePlanification () { return PM; }

    double sensibiliteRecepteur () { return SensRx; }
    double perteRecepteur () { return Lrx; }
    double gainRecepteur () { return Grx; }

    ~MAPLClass ();
private:
    double calculMapl(double &ptx, double &ltx, double &gtx, double &sens, double &lrx, double &grx, double &pm);

    double Ptx, Ltx, Gtx;
    double SensRx, Lrx, Grx;
    double PM;
    double m_mapl;
};

#endif // MAPLCLASS_H
