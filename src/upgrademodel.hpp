#ifndef UPGRADEMODEL_HPP
#define UPGRADEMODEL_HPP

#include <QAbstractListModel>
#include <QList>
#include <QModelIndex>
#include <QVariant>

#include "upgrade.hpp"

class UpgradeModel : public QAbstractListModel
{
    Q_OBJECT

public:
    UpgradeModel (QObject* parent = nullptr);

    void addUpgrade (Upgrade upgrade);

    QList<Upgrade> getUpgrades (void) const;
    Upgrade getUpgrade (const QModelIndex& index) const;

    int rowCount (const QModelIndex& parent = QModelIndex()) const override;
    QVariant data (const QModelIndex& index, int role) const override;

private:
    QList<Upgrade> m_upgrades;
};

#endif // UPGRADEMODEL_HPP
