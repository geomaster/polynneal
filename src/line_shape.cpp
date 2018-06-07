#include "line_shape.hpp"
#include <cmath>

sf::LineShape::LineShape(const Vector2f& point1, const Vector2f& point2):
    m_direction(point2 - point1)
{
    setPosition(point1);
    setThickness(2.f);
}


void sf::LineShape::setThickness(float thickness)
{
    m_thickness = thickness;
    update();
}


float sf::LineShape::getThickness() const
{
    return m_thickness;
}


float sf::LineShape::getLength() const
{
    return std::sqrt(m_direction.x*m_direction.x+m_direction.y*m_direction.y);
}


std::size_t sf::LineShape::getPointCount() const
{
    return 4;
}


sf::Vector2f sf::LineShape::getPoint(std::size_t index) const
{
    Vector2f unitDirection = m_direction/getLength();
    Vector2f unitPerpendicular(-unitDirection.y,unitDirection.x);

    Vector2f offset = (m_thickness/2.f)*unitPerpendicular;

    switch (index)
    {
        default:
        case 0: return offset;
        case 1: return (m_direction + offset);
        case 2: return (m_direction - offset);
        case 3: return (-offset);
    }
}
