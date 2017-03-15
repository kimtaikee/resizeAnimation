#ifndef SLIDEWIDGETCONTAINER_H
#define SLIDEWIDGETCONTAINER_H

#include <QWidget>

class SlideWidgetContainerPrivate;
class SlideWidgetContainer : public QWidget
{
    Q_OBJECT
public:
    explicit SlideWidgetContainer(QWidget *parent = 0);
    ~SlideWidgetContainer();

    void addWidget(QWidget* widget);
    void removeWidget(QWidget* widget);
    int count() const;
    int currentIndex() const;

    void setOrientation(Qt::Orientation ori);
    Qt::Orientation orientation() const;

protected:
    QSize sizeHint() const;
    void resizeEvent(QResizeEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);

private:
    SlideWidgetContainerPrivate* d_ptr;
    Q_DISABLE_COPY(SlideWidgetContainer)
};

#endif // SLIDEWIDGETCONTAINER_H
