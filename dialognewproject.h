#ifndef DIALOGNEWPROJECT_H
#define DIALOGNEWPROJECT_H

#include <QDialog>
#include <QtWidgets>

struct Projet {
    QString Nom;
    QString Ville;
    QString Province;
    QString Zone;

    bool operator==(const Projet &objet) {
        return Nom == objet.Nom && Ville == objet.Ville && Province == objet.Province && Zone == objet.Zone;
    }
};
inline QDataStream &operator<<(QDataStream &stream, const Projet &objet)
{
    return stream << objet.Nom << objet.Ville << objet.Province << objet.Zone;
}

inline QDataStream &operator>>(QDataStream &stream, Projet &objet)
{
    return stream >> objet.Nom >> objet.Ville >> objet.Province >> objet.Zone;
}

namespace Ui {
class DialogNewProject;
}

class DialogNewProject : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNewProject(QWidget *parent = nullptr);
    ~DialogNewProject();

    QString Nom ();
    QString Ville ();
    QString Province ();
    QString Zone ();

signals:
    void sendProjet (Projet projet);

private:
    Ui::DialogNewProject *ui;
};

#endif // DIALOGNEWPROJECT_H
