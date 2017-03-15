#ifndef GRAPHICSPATHOBJECT_H
#define GRAPHICSPATHOBJECT_H

#include <QGraphicsPathItem>
#include <QObject>

class GraphicsPathObject : public QObject, public QGraphicsPathItem
{
    Q_OBJECT
    Q_PROPERTY(QPainterPath path READ path WRITE setPath)
public:
    explicit GraphicsPathObject(QObject* parent = nullptr);
};

#endif // GRAPHICSPATHOBJECT_H
