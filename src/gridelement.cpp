#include "gridelement.hpp"

#include <QDebug>

GridElement::GridElement (
    QColor occupiedColour,
    bool isOccupied
)
    : m_occupiedColour (occupiedColour)
    , m_isOccupied (isOccupied)
{
    qDebug()
        << "Grid element initialised in"
        << (m_isOccupied ? "occupied" : "empty")
        << "state with occupied colour"
        << m_occupiedColour.name();
}

bool GridElement::isOccupied (void) const
{
    return m_isOccupied;
}

void GridElement::setOccupied (bool newOccupied)
{
    qDebug()
        << "Changed grid element to"
        << (newOccupied ? "occupied" : "empty")
        << "state";

    m_isOccupied = newOccupied;
}

QColor GridElement::getOccupiedColour (void) const
{
    return m_occupiedColour;
}

void GridElement::setOccupiedColour (QColor newOccupiedColour)
{
    qDebug() << "Changed occupied colour of grid element to" << newOccupiedColour.name();

    m_occupiedColour = newOccupiedColour;
}

QColor GridElement::getDisplayedColour (void) const
{
    return m_isOccupied
        ? m_occupiedColour
        : GridElement::EMPTY_COLOUR;
}
