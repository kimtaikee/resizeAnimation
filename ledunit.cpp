#include "ledunit.h"

#include <QPainter>
#include <QPropertyAnimation>

LedUnit::LedUnit(QWidget *parent) : QWidget(parent)
{

}

void LedUnit::setOn(bool on)
{
    if (m_on != on) {
        m_on = on;

        if (m_animated) {
            QPropertyAnimation* anim = new QPropertyAnimation(this, "color");
            anim->setDuration(1000);
            anim->setEasingCurve(QEasingCurve::OutCubic);
            anim->setStartValue(on ? m_offColor : m_onColor);
            anim->setEndValue(on ? m_onColor : m_offColor);
            anim->start(QAbstractAnimation::DeleteWhenStopped);
        } else {
            m_color = on ? m_onColor : m_offColor;
            update();
        }
    }
}

bool LedUnit::on() const
{
    return m_on;
}

void LedUnit::setAnimated(bool animate)
{
    if (m_animated != animate)
        m_animated = animate;
}

bool LedUnit::animated() const
{
    return m_animated;
}

void LedUnit::setColor(const QColor& clr)
{
    if (m_color != clr) {
        m_color = clr;
        update();
    }
}

QColor LedUnit::color() const
{
    return m_color;
}

void LedUnit::setOffColor(const QColor& clr)
{
    m_offColor = clr;
}

QColor LedUnit::offColor() const
{
    return m_offColor;
}

void LedUnit::setOnColor(const QColor& clr)
{
    m_onColor = clr;
}

QColor LedUnit::onColor() const
{
    return m_onColor;
}

void LedUnit::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setPen(QPen(QColor(89, 89, 89), 1));
    QLinearGradient lg(this->rect().topLeft(), this->rect().bottomLeft());
    lg.setColorAt(0.0, m_color.lighter());
    lg.setColorAt(1.0, m_color);
    painter.setBrush(QBrush(lg));
    painter.drawRect(rect());
}
