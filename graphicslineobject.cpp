#include "graphicslineobject.h"

GraphicsLineObject::GraphicsLineObject(QGraphicsItem* parent) : QGraphicsLineItem(parent)
{

}

void GraphicsLineObject::setPoint1(const QPoint& point)
{
    if (m_point1 != point) {
        m_point1 = point;
        setLine(QLineF(m_point1, m_point2));
    }
}

QPoint GraphicsLineObject::point1() const
{
    return m_point1;
}

void GraphicsLineObject::setPoint2(const QPoint& point)
{
    if (m_point2 != point) {
        m_point2 = point;
        setLine(QLineF(m_point1, m_point2));
    }
}

QPoint GraphicsLineObject::point2() const
{
    return m_point2;
}

