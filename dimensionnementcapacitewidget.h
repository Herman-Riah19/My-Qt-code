#ifndef DIMENSIONNEMENTCAPACITEWIDGET_H
#define DIMENSIONNEMENTCAPACITEWIDGET_H

#include <QWidget>
#include "capaciteenodeb.h"
#include "capaciteuplink.h"
#include "capacitedownlink.h"

namespace Ui {
class DimensionnementCapaciteWidget;
}

class DimensionnementCapaciteWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DimensionnementCapaciteWidget(double hm, QWidget *parent = nullptr);
    ~DimensionnementCapaciteWidget();

//    CapaciteENodeB *getEnodeB () { return ENodeB; }
//    CapaciteUplink *getUplink () { return Uplink; }
    CapaciteDownlink *getDownlink () { return Downlink; }

public slots:
    void ENodeBCalcul ();
    void UplinkCalcul ();
    void DownlinkCalcul1 ();
    void DownlinkCalcul2 ();

signals:
    void sendENodeB (CapaciteENodeB *enodeb);
    void sendUplink (CapaciteUplink *uplink);
    void sendDownlink (CapaciteDownlink *downlink);

private:
    Ui::DimensionnementCapaciteWidget *ui;

    double hauteurMobile;
    CapaciteENodeB *ENodeB;
    CapaciteUplink *Uplink;
    CapaciteDownlink *Downlink;
};

#endif // DIMENSIONNEMENTCAPACITEWIDGET_H
