#ifndef LEDUNIT_H
#define LEDUNIT_H

#include <QWidget>

class LedUnit : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(bool on READ on WRITE setOn)
public:
    explicit LedUnit(QWidget *parent = 0);

    void setOn(bool on);
    bool on() const;

    void setAnimated(bool animate);
    bool animated() const;

    void setColor(const QColor& clr);
    QColor color() const;

    void setOffColor(const QColor& clr);
    QColor offColor() const;

    void setOnColor(const QColor& clr);
    QColor onColor() const;

protected:
    void paintEvent(QPaintEvent* event);

private:
    bool m_on = false;
    bool m_animated = true;
    QColor m_color = QColor(45, 45, 45);
    QColor m_onColor = Qt::green;
    QColor m_offColor = QColor(45, 45, 45);
};

#endif // LEDUNIT_H
