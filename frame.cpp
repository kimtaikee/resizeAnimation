#include "frame.h"

#include <QPainter>

Frame::Frame(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

void Frame::setColor(const QColor& clr)
{
    if (m_color != clr) {
        m_color = clr;
        update();
    }
}

QColor Frame::color() const
{
    return m_color;
}

void Frame::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(QPen(m_color, 2));
    painter.drawRoundedRect(rect(), 5, 5);
}
