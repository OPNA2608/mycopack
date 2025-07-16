#ifndef GRID_HPP
#define GRID_HPP

#include "gridelement.hpp"

class Grid
{
public:
    Grid (
        unsigned int width = Grid::MINIMUM_WIDTH,
        unsigned int height = Grid::MINIMUM_HEIGHT
    );

    ~Grid(void);

    unsigned int getWidth (void) const;
    bool setWidth (unsigned int newWidth);

    unsigned int getHeight (void) const;
    bool setHeight (unsigned int newHeight);

    bool resize (unsigned int newWidth, unsigned int newHeight);

    GridElement* getElement (unsigned int x, unsigned int y) const;

private:
    static const unsigned int MINIMUM_WIDTH = 2;
    static const unsigned int MINIMUM_HEIGHT = 2;

    unsigned int m_width;
    unsigned int m_height;

    GridElement** m_internalGrid;
};

#endif // GRID_HPP
