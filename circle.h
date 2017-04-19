#ifndef CIRCLE_H
#define CIRCLE_H

#include <QWidget>

class Circle : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal radius READ radius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
public:
    explicit Circle(QWidget *parent = 0);

    void setRadius(qreal radius);
    qreal radius() const;

    void setOpacity(qreal opacity);
    qreal opacity() const;

    void setColor(const QColor& clr);
    QColor color() const;

signals:
    void radiusChanged(qreal radius);
    void opacityChanged(qreal opacity);
    void colorChanged(const QColor& clr);

protected:
    void paintEvent(QPaintEvent* e);

private:
    qreal m_radius = 1.0;
    qreal m_opacity = 1.0;
    QColor m_color = Qt::black;
};

#endif // CIRCLE_H
