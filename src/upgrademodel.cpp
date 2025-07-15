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
