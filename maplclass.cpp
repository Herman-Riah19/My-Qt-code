#include "maplclass.h"

MAPLClass::MAPLClass(QObject *parent):QObject (parent)
{
    Ptx = 0; Ltx = 0; Gtx = 0;
    SensRx = 0; Lrx = 0; Grx = 0;
    PM = 0; m_mapl = 0;
}

void MAPLClass::setValue(double &ptx, double &ltx, double &gtx, double &sens, double &lrx, double &grx, double &pm)
{
    Ptx = ptx; Ltx = ltx; Gtx = gtx;
    SensRx = sens; Lrx = lrx; Grx = grx;
    PM = pm;
    m_mapl = calculMapl (Ptx, Ltx, Gtx, SensRx, Lrx, Grx, PM);
}

MAPLClass::~MAPLClass()
{

}

double MAPLClass::calculMapl(double &ptx, double &ltx, double &gtx, double &sens, double &lrx, double &grx, double &pm)
{
    return ptx + gtx - ltx - sens + grx - lrx - pm;
}
