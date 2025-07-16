#include "upgrade.hpp"

#include <QDebug>

Upgrade::Upgrade(QString name, QColor colour)
    : m_name { name }
    , m_colour { colour }
{
    qDebug() << "Upgrade " << m_name << " initialised with colour " << m_colour.name();
}

QString Upgrade::getName (void) const
{
    return m_name;
}

void Upgrade::setName (QString name)
{
    qDebug() << "Setting name of upgrade" << this << "to" << name;

    m_name = name;
}

QColor Upgrade::getColour (void) const
{
    return m_colour;
}

void Upgrade::setColour (QColor colour)
{
    qDebug() << "Setting colour of upgrade" << this << "to" << colour.name();

    m_colour = colour;
}
