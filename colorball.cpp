#include "colorball.h"

#include <QPaintEvent>
#include <QPainter>

ColorBall::ColorBall(QWidget *parent) : QWidget(parent)
{
    setFixedSize(QSize(50, 50));
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

void ColorBall::setColor(const QColor& clr)
{
    if (m_color != clr) {
        m_color = clr;
        update();
    }
}

QColor ColorBall::color() const
{
    return m_color;
}

void ColorBall::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::black, 1));
    painter.setBrush(QBrush(m_color));
    painter.drawEllipse(rect());
}
