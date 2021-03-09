#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QtWidgets>

struct Model {
    QString parametre;
    double valeur;
};
inline QDataStream &operator<<(QDataStream &stream, const Model &objet)
{
    return stream << objet.parametre << " " << objet.valeur;
}

inline QDataStream &operator>>(QDataStream &stream, Model &objet)
{
    return stream >> objet.parametre >> objet.valeur;
}

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TableModel(QWidget *parent = nullptr);
    explicit TableModel (QVector<Model> model, QWidget *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool insertRows(int row, int count, const QModelIndex &parent) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    QVector<Model> &model () { return m_models; }
private:
    QVector<Model> m_models;


};

#endif // TABLEMODEL_H
