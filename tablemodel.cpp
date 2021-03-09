#include "tablemodel.h"
#include <QtWidgets>

TableModel::TableModel(QWidget *parent):
    QAbstractTableModel (parent)
{

}

TableModel::TableModel(QVector<Model> model, QWidget *parent):
    QAbstractTableModel (parent), m_models (model)
{

}

int TableModel::rowCount(const QModelIndex &parent) const
{
    return  parent.isValid () ? 0 : m_models.size ();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid () ? 0 : 2;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid ())
        return QVariant ();

    if (index.row () >= m_models.size () || index.row () < 0)
        return QVariant ();

    if (role == Qt::DisplayRole) {
        const auto model = m_models.at (index.row ());
        switch (index.column ()) {
            case 0:
                return model.parametre;
            case 1:
                return model.valeur;
            default:
                break;
        }
    }
    return QVariant ();
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid () && role == Qt::EditRole) {
        const int ligne = index.row ();
        auto outil = m_models.value (ligne);

        switch (index.column ()) {
            case 0:
                outil.parametre = value.toString ();
                break;
            case 1:
                outil.valeur = value.toDouble ();
                break;
            default:
                break;
        }
        m_models.replace (ligne, outil);
        emit dataChanged (index, index, { Qt::DisplayRole, Qt::EditRole});

        return true;
    }
    return false;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Paramètre");
            case 1:
                return tr("Valeur");
            default:
                break;
        }
    }
    return QVariant();
}

bool TableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    beginInsertRows(QModelIndex(), row, row + count - 1);

    for (int row = 0; row < count; ++row)
        m_models.insert(row, { QString(), double() });

    endInsertRows();
    return true;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid ())
        return Qt::ItemIsEnabled;
    return QAbstractTableModel::flags (index) | Qt::ItemIsEditable;
}
