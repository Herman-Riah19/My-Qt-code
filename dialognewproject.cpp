#include "dialognewproject.h"
#include "ui_dialognewproject.h"

DialogNewProject::DialogNewProject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNewProject)
{
    ui->setupUi(this);
    setFixedSize (276, 353);
    setWindowTitle ("Nouveau Projet");

    connect (ui->btnOK, &QAbstractButton::clicked, this, &QDialog::accept);
    connect (ui->btnOK, &QAbstractButton::clicked, this, &QDialog::reject);
}

DialogNewProject::~DialogNewProject()
{
    delete ui;
}

QString DialogNewProject::Nom()
{
    return ui->lineNomProjet->text ();
}

QString DialogNewProject::Ville()
{
    return ui->lineVille->text ();
}

QString DialogNewProject::Province()
{
    return ui->cbPovince->lineEdit ()->text ();
}

QString DialogNewProject::Zone()
{
    return ui->cbZone->lineEdit ()->text ();
}

