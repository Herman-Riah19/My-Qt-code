#ifndef RESULTATWIDGET_H
#define RESULTATWIDGET_H

#include <QWidget>
#include "tablemodel.h"
#include "maplclass.h"
#include "propagationclass.h"
#include "capaciteenodeb.h"
#include "capaciteuplink.h"
#include "capacitedownlink.h"
#include "dialognewproject.h"

namespace Ui {
class ResultatWidget;
}

class ResultatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ResultatWidget(QWidget *parent = nullptr);
    ~ResultatWidget();

    void setupProjet (const QString &nom, const QString &ville, const QString &province, const QString &zone);
    void setupCouverture ();
    void setupCapacite ();

public slots:
    void ouvrirDialog ();
    void receptionMapl (MAPLClass *m);
    void receptionPropagation (PropagationClass *prop);
    void receptionENodeB (CapaciteENodeB *enode);
    void receptionUplink (CapaciteUplink *up);
    void receptionDownlink (CapaciteDownlink *down);

private:
    Ui::ResultatWidget *ui;

    MAPLClass *mapl;
    PropagationClass *propagation;
    CapaciteENodeB *enodb;
    CapaciteUplink *uplink;
    CapaciteDownlink *downlink;

    QVector<Model> modelsCouvertures, modelsCapacites;

private:
    QVector<Model> initModelCouverture (MAPLClass *mapl = nullptr, PropagationClass *prop = nullptr);
    QVector<Model> initModelCapacite (CapaciteENodeB *enodeb = nullptr, CapaciteUplink *uplink = nullptr, CapaciteDownlink *down = nullptr);
};

#endif // RESULTATWIDGET_H
