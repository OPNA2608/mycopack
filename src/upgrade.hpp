#ifndef UPGRADE_H
#define UPGRADE_H

#include <QColor>
#include <QString>

class Upgrade
{
public:
    Upgrade(QString name, QColor colour);

    QString getName(void) const;
    void setName(QString name);

    QColor getColour(void) const;
    void setColour(QColor colour);

private:
    QString m_name;
    QColor m_colour;
};

#endif // UPGRADE_H
