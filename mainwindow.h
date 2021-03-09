#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "maplclass.h"
#include "propagationclass.h"
#include "capaciteenodeb.h"
#include "capaciteuplink.h"
#include "capacitedownlink.h"
#include "dimensionnementcouverture.h"
#include "dimensionnementcapacitewidget.h"
#include "resultatwidget.h"

#include <QMainWindow>
#include <QtWidgets>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void ouvrirAcceuil ();
    void ouvrirDimensionnementCouverture ();
    void ouvrirDimensionnementCapacite ();
    void ouvrirResultat ();

private:
    Ui::MainWindow *ui;

    DimensionnementCouverture *m_dimCouverture;
    DimensionnementCapaciteWidget *m_dimCapacite;
    ResultatWidget *resultat;
    QStackedWidget *stack;
};

#endif // MAINWINDOW_H
