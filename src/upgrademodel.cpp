#include "upgrademodel.hpp"

#include <QDebug>

UpgradeModel::UpgradeModel (QObject* parent)
    : QAbstractListModel (parent)
{
    qDebug() << "UpgradeModel constructed.";
}

void UpgradeModel::addUpgrade (Upgrade upgrade)
{
    qDebug() << "Adding upgrade to upgrade model";

    m_upgrades.append (upgrade);

    emit dataChanged (
        index(m_upgrades.size() - 1),
        index(m_upgrades.size() - 1),
        { Qt::EditRole, Qt::DisplayRole }
    );
}

void UpgradeModel::changeUpgrade (const QModelIndex& index, QString newName, QColor newColour)
{
    qDebug() << "Changing upgrade in upgrade model";

    Upgrade upgrade = m_upgrades.at (index.row());
    upgrade.setName (newName);
    upgrade.setColour (newColour);
    m_upgrades.replace (index.row(), upgrade);

    emit dataChanged (
        index,
        index,
        { Qt::EditRole, Qt::DisplayRole }
    );
}

void UpgradeModel::removeUpgrade (const QModelIndex& index)
{
    qDebug() << "Removing upgrade from upgrade model";

    m_upgrades.removeAt(index.row());

    emit dataChanged (
        index,
        index,
        { Qt::EditRole, Qt::DisplayRole }
    );
}

QList<Upgrade> UpgradeModel::getUpgrades (void) const
{
    return m_upgrades;
}

Upgrade UpgradeModel::getUpgrade (const QModelIndex& index) const
{
    return m_upgrades[index.row()];
}

int UpgradeModel::rowCount (const QModelIndex& parent) const
{
    return m_upgrades.size();
}

QVariant UpgradeModel::data (const QModelIndex& index, int role) const
{
    if (index.isValid() && role == Qt::DisplayRole) {
        return m_upgrades[index.row()].getName() + " @ " + m_upgrades[index.row()].getColour().name();
    }

    return QVariant();
}
