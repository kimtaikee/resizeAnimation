#include "circle.h"

#include <QPainter>

Circle::Circle(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint| Qt::ToolTip);
}

void Circle::setRadius(qreal radius)
{
    if (m_radius != radius) {
        m_radius = radius;
        emit radiusChanged(radius);
        update();
    }
}

qreal Circle::radius() const
{
    return m_radius;
}


void Circle::setOpacity(qreal opacity)
{
    if (m_opacity != opacity) {
        m_opacity = opacity;
        update();
        emit opacityChanged(opacity);
    }
}

qreal Circle::opacity() const
{
    return m_opacity;
}

void Circle::setColor(const QColor& clr)
{
    if (m_color != clr) {
        m_color = clr;
        update();
        emit colorChanged(clr);
    }
}

QColor Circle::color() const
{
    return m_color;
}

void Circle::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setOpacity(m_opacity);
    painter.setPen(QPen(m_color, 1));

    if (m_radius <= 3)
        painter.setBrush(QBrush(m_color));

    QPoint center = rect().center();
    painter.drawEllipse(QPointF(center.x(), center.y()), m_radius, m_radius);
}
