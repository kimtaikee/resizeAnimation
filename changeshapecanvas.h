#ifndef CHANGESHAPECANVAS_H
#define CHANGESHAPECANVAS_H

#include <QWidget>

namespace Ui
{
    class ChangeShapeCanvas;
}

class QGraphicsView;
class QGraphicsScene;
class GraphicsPathObject;
class ChangeShapeCanvas : public QWidget
{
    Q_OBJECT
public:
    explicit ChangeShapeCanvas(QWidget *parent = 0);
    ~ChangeShapeCanvas();

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void on_addLineButton_clicked();
    void on_addPieButton_clicked();

private:
    void init();

private:
    Ui::ChangeShapeCanvas *m_ui;
    QGraphicsView* m_view;
    QGraphicsScene* m_scene;
    GraphicsPathObject* m_pathObj = nullptr;
};

Q_DECLARE_METATYPE(QPainterPath)
#endif // CHANGESHAPECANVAS_H
