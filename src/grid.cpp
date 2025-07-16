#include "grid.hpp"

#include <QDebug>

#include <algorithm>

Grid::Grid (unsigned int width, unsigned int height)
    : m_width (width)
    , m_height (height)
{
    qDebug() << "Initialising grid with width" << m_width << "and height" << m_height;

    m_internalGrid = new GridElement*[m_height];
    for (unsigned int y = 0; y < m_height; ++y)
    {
        m_internalGrid[y] = new GridElement[m_width];
    }
}

Grid::~Grid (void)
{
    GridElement** internalGrid = m_internalGrid;
    m_internalGrid = nullptr;

    for (unsigned int y = 0; y < m_height; ++y)
    {
        GridElement* internalGridColumn = internalGrid[y];
        internalGrid[y] = nullptr;
        delete internalGridColumn;
    }

    delete internalGrid;
}

unsigned int Grid::getWidth (void) const
{
    return m_width;
}

bool Grid::setWidth (unsigned int newWidth)
{
    if (!newWidth >= Grid::MINIMUM_WIDTH)
    {
        qDebug()
            << "Rejected invalid width changing request:"
            << newWidth
            << "is less than required minimum width"
            << Grid::MINIMUM_WIDTH;
        return false;
    }

    qDebug() << "Changing grid width to" << newWidth;

    if (newWidth == m_width)
    {
        return true;
    }

    for (unsigned int y = 0; y < m_height; ++y)
    {
        GridElement* oldColumn = m_internalGrid[y];
        m_internalGrid[y] = nullptr;

        // initialised to new width
        GridElement* newColumn = new GridElement[newWidth];

        // copy any entry'd details from the old column that fit within the new column
        for (unsigned int x = 0; x < std::min(m_width, newWidth); ++x)
        {
            newColumn[x].setOccupiedColour(oldColumn[x].getOccupiedColour());
            newColumn[x].setOccupied(oldColumn[x].isOccupied());
        }

        m_internalGrid[y] = newColumn;
        delete oldColumn;
    }

    m_width = newWidth;
    return true;
}

unsigned int Grid::getHeight (void) const
{
    return m_height;
}

bool Grid::setHeight (unsigned int newHeight)
{

    if (!newHeight >= Grid::MINIMUM_HEIGHT)
    {
        qDebug()
        << "Rejected invalid height changing request:"
        << newHeight
        << "is less than required minimum width"
        << Grid::MINIMUM_HEIGHT;
        return false;
    }

    qDebug() << "Changing grid height to" << newHeight;

    if (newHeight == m_height)
    {
        return true;
    }

    GridElement** oldRow = m_internalGrid;
    m_internalGrid = nullptr;

    // initialised to new height
    GridElement** newRow = new GridElement*[newHeight];

    // copy any columns from the old row that fit within the new row
    for (unsigned int y = 0; y < std::min(m_height, newHeight); ++y)
    {
        newRow[y] = oldRow[y];
    }

    // if new height > old height, initialise empty columns
    for (unsigned int y = m_height; y < newHeight; ++y)
    {
        newRow[y] = new GridElement[m_width];
    }

    // if old height > new height, delete no longer used columns
    for (unsigned int y = newHeight; y < m_height; ++y)
    {
        delete oldRow[y];
    }

    m_internalGrid = newRow;
    delete oldRow;

    m_height = newHeight;
    return true;
}

bool Grid::resize (unsigned int newWidth, unsigned int newHeight)
{
    qDebug() << "Resizing grid";

    return setWidth (newWidth) && setHeight (newHeight);
}

GridElement* Grid::getElement (unsigned int x, unsigned int y) const
{
    if (!x < m_width)
    {
        qDebug()
            << "Attempted to access grid element with x coordinate"
            << x
            << ", which is outside of the grid's current width"
            << m_width;
        return nullptr;
    }

    if (!y < m_height)
    {
        qDebug()
            << "Attempted to access grid element with y coordinate"
            << y
            << ", which is outside of the grid's current height"
            << m_height;
        return nullptr;
    }

    return &m_internalGrid[y][x];
}
