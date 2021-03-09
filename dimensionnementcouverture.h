#ifndef DIMENSIONNEMENTCOUVERTURE_H
#define DIMENSIONNEMENTCOUVERTURE_H

#include "maplclass.h"
#include "propagationclass.h"
#include <QWidget>

namespace Ui {
class DimensionnementCouverture;
}

class DimensionnementCouverture : public QWidget
{
    Q_OBJECT

public:
    explicit DimensionnementCouverture(QWidget *parent = nullptr);
    ~DimensionnementCouverture();

    PropagationClass *getPropagation () { return propagation; }

public slots:
    void MAPL ();
    void RayonEtNombreSite ();

signals:
    void sendMapl (MAPLClass *maplClass);
    void sendPropagation (PropagationClass *popagationClass);

private:
    Environnement choixEnvironnement ();
    Propagation typePropagation ();

    Ui::DimensionnementCouverture *ui;
    MAPLClass *mapl;
    PropagationClass *propagation;
};

#endif // DIMENSIONNEMENTCOUVERTURE_H
