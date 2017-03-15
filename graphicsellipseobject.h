#ifndef GRAPHICSELLIPSEOBJECT_H
#define GRAPHICSELLIPSEOBJECT_H

#include <QGraphicsEllipseItem>

class GraphicsEllipseObject : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
    Q_PROPERTY(int spanAngle READ spanAngle WRITE setSpanAngle)
    Q_PROPERTY(int startAngle READ startAngle WRITE setStartAngle)
public:
    explicit GraphicsEllipseObject(QObject *parent = 0);
};

#endif // GRAPHICSELLIPSEOBJECT_H
