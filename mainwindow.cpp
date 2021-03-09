#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialognewproject.h"
#include <QtWidgets>
#include <QtSql>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    resize (850, 500);

    m_dimCouverture = new DimensionnementCouverture (this);
    m_dimCouverture->setVisible (false);
    connect (ui->btnAcceuil, &QPushButton::clicked, this, &MainWindow::ouvrirAcceuil);
    connect (ui->btnCouverture, &QPushButton::clicked, this, &MainWindow::ouvrirDimensionnementCouverture);

    m_dimCapacite = new DimensionnementCapaciteWidget (m_dimCouverture->getPropagation ()->HauteurMobile (), this);
    m_dimCapacite->setVisible (false);
    connect (ui->btnCapacite, &QPushButton::clicked, this, &MainWindow::ouvrirDimensionnementCapacite);

    resultat = new ResultatWidget (this);
    resultat->setVisible (false);
    connect (ui->btnResultat, &QPushButton::clicked, this, &MainWindow::ouvrirResultat);
    connect (ui->btnNouveauProjet, &QPushButton::clicked, resultat, &ResultatWidget::ouvrirDialog);
    connect (m_dimCouverture, &DimensionnementCouverture::sendMapl, resultat, &ResultatWidget::receptionMapl);
    connect (m_dimCouverture, &DimensionnementCouverture::sendPropagation, resultat, &ResultatWidget::receptionPropagation);
    connect (m_dimCapacite, &DimensionnementCapaciteWidget::sendENodeB, resultat, &ResultatWidget::receptionENodeB);
    connect (m_dimCapacite, &DimensionnementCapaciteWidget::sendUplink, resultat, &ResultatWidget::receptionUplink);
    connect (m_dimCapacite, &DimensionnementCapaciteWidget::sendDownlink, resultat, &ResultatWidget::receptionDownlink);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ouvrirAcceuil()
{
    ui->widgetAcceuil->setVisible (true);
    m_dimCouverture->setVisible (false);
    m_dimCapacite->setVisible (false);
    resultat->setVisible (false);
}

void MainWindow::ouvrirDimensionnementCouverture()
{
    ui->widgetAcceuil->setVisible (false);
    m_dimCouverture->setVisible (true);
    m_dimCapacite->setVisible (false);
    resultat->setVisible (false);

    ui->layoutWidget->addWidget (m_dimCouverture);
}

void MainWindow::ouvrirDimensionnementCapacite()
{
    ui->widgetAcceuil->setVisible (false);
    m_dimCouverture->setVisible (false);
    m_dimCapacite->setVisible (true);
    resultat->setVisible (false);

    ui->layoutWidget->addWidget (m_dimCapacite);
}

void MainWindow::ouvrirResultat()
{
    ui->widgetAcceuil->setVisible (false);
    m_dimCouverture->setVisible (false);
    m_dimCapacite->setVisible (false);
    resultat->setVisible (true);

    ui->layoutWidget->addWidget (resultat);
}
