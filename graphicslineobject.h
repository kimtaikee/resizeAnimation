#ifndef GRAPHICSLINEOBJECT_H
#define GRAPHICSLINEOBJECT_H

#include <QGraphicsLineItem>

class GraphicsLineObject : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
    Q_PROPERTY(QPoint point1 READ point1 WRITE setPoint1)
    Q_PROPERTY(QPoint point2 READ point2 WRITE setPoint2)
public:
    explicit GraphicsLineObject(QGraphicsItem* parent = nullptr);

    void setPoint1(const QPoint& point);
    QPoint point1() const;

    void setPoint2(const QPoint& point);
    QPoint point2() const;

protected:
    QPoint m_point1;
    QPoint m_point2;
};

#endif // GRAPHICSLINEOBJECT_H
