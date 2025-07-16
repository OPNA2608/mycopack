#ifndef GRIDELEMENT_HPP
#define GRIDELEMENT_HPP

#include <QColor>

class GridElement
{
public:
    GridElement (
        QColor occupiedColour = GridElement::DEFAULT_COLOUR,
        bool isOccupied = false
    );

    static constexpr QColor DEFAULT_COLOUR = QColor (255, 255, 255);
    static constexpr QColor EMPTY_COLOUR = QColor (0, 0, 0);

    bool isOccupied (void) const;
    void setOccupied (bool newOccupied);

    QColor getOccupiedColour (void) const;
    void setOccupiedColour (QColor newOccupiedColour);

    QColor getDisplayedColour (void) const;

private:
    QColor m_occupiedColour;
    bool m_isOccupied;
};

#endif // GRIDELEMENT_HPP
