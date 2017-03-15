#include "slidewidgetcontainer.h"

#include <QMouseEvent>
#include <QDebug>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QApplication>

const int SwitchThresholdFactor = 4;
const int DragThreshold = 120;
const int SlideDuration = 500;
static const QEasingCurve::Type EasingCurve = QEasingCurve::OutCubic;

class SlideWidgetContainerPrivate
{
public:
    void layoutWidgetsHorizontally();
    void slideWidgetHorizontally(const QPoint& pos);
    void switchWidgetHorizontally(const QPoint& pos);

    void layoutWidgetsVertically();
    void slideWidgetVertically(const QPoint& pos);
    void switchWidgetVertically(const QPoint& pos);

    void stopAnimations() { /*return;*/ foreach (auto anim, animations) anim->stop(); }
    void startAnimation(QWidget* target, const QPoint& oldPos, const QPoint& newPos, bool add = true);

    SlideWidgetContainer* q_ptr;
    QWidgetList widgets;
    bool pressed = false;
    QPoint pressedPoint;
    int currentIndex = -1;
    QList<QPropertyAnimation*> animations;
    Qt::Orientation orientation = Qt::Horizontal;
};

void SlideWidgetContainerPrivate::layoutWidgetsHorizontally()
{
    if (currentIndex < 0 || currentIndex >= widgets.size())
        return;

    int x = -currentIndex * q_ptr->width();
    for (int i = 0; i < widgets.size(); ++i) {
        widgets.at(i)->move(QPoint(x, 0));
        widgets.at(i)->resize(q_ptr->size());
        x += q_ptr->width();
    }
}

void SlideWidgetContainerPrivate::slideWidgetHorizontally(const QPoint &pos)
{
    if (currentIndex < 0 || currentIndex >= widgets.size())
        return;

    stopAnimations();

    int deltaX = pos.x() - pressedPoint.x();
    QWidget* widget = widgets.at(currentIndex);
    bool reachThreshold = qAbs(deltaX) > DragThreshold;
    bool slideBackward = deltaX > 0;

    // boundary check, cannot drag too far
    if (currentIndex == 0 && reachThreshold && slideBackward)
        deltaX = DragThreshold;
    else if (currentIndex == (widgets.size() - 1) && reachThreshold &&!slideBackward)
        deltaX = - DragThreshold;
    widget->move(QPoint(deltaX, 0));

    if (deltaX < 0) {
        // slide in next widget
        if (widgets.size() > (currentIndex + 1)) {
            qDebug() << "slide in next widget";
            QWidget* nextWidget = widgets.at(currentIndex + 1);
            QPoint nextPos(q_ptr->width() - qAbs(deltaX), 0);
            qDebug() << "next pos: " << nextPos;
            qDebug() << "next widget pos:" << nextWidget->pos();
            nextWidget->move(nextPos);
        }
    } else {
        // slide in previous widget
        if ((currentIndex - 1) >= 0) {
            qDebug() << "slide in previous widget";
            QWidget* prevWidget = widgets.at(currentIndex - 1);
            prevWidget->move(-q_ptr->width() + deltaX, 0);
        }
    }
}

void SlideWidgetContainerPrivate::switchWidgetHorizontally(const QPoint &pos)
{
    if (currentIndex < 0 || currentIndex >= widgets.size())
        return;

    int deltaX = pos.x() - pressedPoint.x();
    bool shouldSwitch = qAbs(deltaX) > (q_ptr->width() / SwitchThresholdFactor);
    bool slideForward = deltaX < 0;

    if (shouldSwitch) {
        if (slideForward) {
            if (widgets.size() > (currentIndex + 1)) {
                QWidget* currentWidget = widgets.at(currentIndex);
                startAnimation(currentWidget, currentWidget->pos(), QPoint(-q_ptr->width(), 0));

                QWidget* nextWidget = widgets.at(currentIndex + 1);
                startAnimation(nextWidget, nextWidget->pos(), QPoint(0, 0));

                ++currentIndex;
            } else {
                // move to original position
                QWidget* currentWidget = widgets.at(currentIndex);
                startAnimation(currentWidget, currentWidget->pos(), QPoint(0, 0));
            }
        } else {
            if ((currentIndex - 1) >= 0) {
                QWidget* prevWidget = widgets.at(currentIndex - 1);
                startAnimation(prevWidget, prevWidget->pos(), QPoint(0, 0));

                QWidget* currentWidget = widgets.at(currentIndex);
                startAnimation(currentWidget, currentWidget->pos(), QPoint(q_ptr->width(), 0), false);

                --currentIndex;
            } else {
                // move to original position
                QWidget* currentWidget = widgets.at(currentIndex);
                startAnimation(currentWidget, currentWidget->pos(), QPoint(0, 0));
            }
        }
    } else {
        QWidget* widget = widgets.at(currentIndex);
        startAnimation(widget, QPoint(deltaX, 0), QPoint(0, 0));

        if (deltaX < 0) {
            // handle next widget's animation
            if (widgets.size() > (currentIndex + 1)) {
                QWidget* nextWidget = widgets.at(currentIndex + 1);
                startAnimation(nextWidget, nextWidget->pos(), QPoint(q_ptr->width(), 0), false);
            }

        } else {
            // handle previous widget's animation
            if ((currentIndex - 1) >= 0) {
                QWidget* prevWidget = widgets.at(currentIndex - 1);
                startAnimation(prevWidget, prevWidget->pos(), QPoint(-q_ptr->width(), 0), false);
            }
        }
    }
}

void SlideWidgetContainerPrivate::layoutWidgetsVertically()
{
    if (currentIndex < 0 || currentIndex >= widgets.size())
        return;

    int y = -currentIndex * q_ptr->height();
    for (int i = 0; i < widgets.size(); ++i) {
        widgets.at(i)->move(QPoint(0, y));
        widgets.at(i)->resize(q_ptr->size());
        y += q_ptr->height();
    }
}

void SlideWidgetContainerPrivate::slideWidgetVertically(const QPoint& pos)
{
    if (currentIndex < 0 || currentIndex >= widgets.size())
        return;

    stopAnimations();

    int deltaY = pos.y() - pressedPoint.y();
    QWidget* widget = widgets.at(currentIndex);
    bool reachThreshold = qAbs(deltaY) > DragThreshold;
    bool slideBackward = deltaY > 0;

    // boundary check, cannot drag too far
    if (currentIndex == 0 && reachThreshold && slideBackward)
        deltaY = DragThreshold;
    else if (currentIndex == (widgets.size() - 1) && reachThreshold &&!slideBackward)
        deltaY = - DragThreshold;
    widget->move(QPoint(0, deltaY));

    if (deltaY < 0) {
        // slide in next widget
        if (widgets.size() > (currentIndex + 1)) {
            qDebug() << "slide in next widget";
            QWidget* nextWidget = widgets.at(currentIndex + 1);
            QPoint nextPos(0, q_ptr->height() - qAbs(deltaY));
            qDebug() << "next pos: " << nextPos;
            qDebug() << "next widget pos:" << nextWidget->pos();
            nextWidget->move(nextPos);
        }
    } else {
        // slide in previous widget
        if ((currentIndex - 1) >= 0) {
            qDebug() << "slide in previous widget";
            QWidget* prevWidget = widgets.at(currentIndex - 1);
            prevWidget->move(0, -q_ptr->height() + deltaY);
        }
    }
}

void SlideWidgetContainerPrivate::switchWidgetVertically(const QPoint& pos)
{
    if (currentIndex < 0 || currentIndex >= widgets.size())
        return;

    int deltaY = pos.y() - pressedPoint.y();
    bool shouldSwitch = qAbs(deltaY) > (q_ptr->height() / SwitchThresholdFactor);
    bool slideForward = deltaY < 0;

    if (shouldSwitch) {
        if (slideForward) {
            if (widgets.size() > (currentIndex + 1)) {
                QWidget* currentWidget = widgets.at(currentIndex);
                startAnimation(currentWidget, currentWidget->pos(), QPoint(0, -q_ptr->height()));

                QWidget* nextWidget = widgets.at(currentIndex + 1);
                startAnimation(nextWidget, nextWidget->pos(), QPoint(0, 0));

                ++currentIndex;
            } else {
                // move to original position
                QWidget* currentWidget = widgets.at(currentIndex);
                startAnimation(currentWidget, currentWidget->pos(), QPoint(0, 0));
            }
        } else {
            if ((currentIndex - 1) >= 0) {
                QWidget* prevWidget = widgets.at(currentIndex - 1);
                startAnimation(prevWidget, prevWidget->pos(), QPoint(0, 0));

                QWidget* currentWidget = widgets.at(currentIndex);
                startAnimation(currentWidget, currentWidget->pos(), QPoint(0, q_ptr->height()), false);

                --currentIndex;
            } else {
                // move to original position
                QWidget* currentWidget = widgets.at(currentIndex);
                startAnimation(currentWidget, currentWidget->pos(), QPoint(0, 0));
            }
        }
    } else {
        QWidget* widget = widgets.at(currentIndex);
        startAnimation(widget, QPoint(0, deltaY), QPoint(0, 0));

        if (deltaY < 0) {
            // handle next widget's animation
            if (widgets.size() > (currentIndex + 1)) {
                QWidget* nextWidget = widgets.at(currentIndex + 1);
                startAnimation(nextWidget, nextWidget->pos(), QPoint(0, q_ptr->height()), false);
            }

        } else {
            // handle previous widget's animation
            if ((currentIndex - 1) >= 0) {
                QWidget* prevWidget = widgets.at(currentIndex - 1);
                startAnimation(prevWidget, prevWidget->pos(), QPoint(0, -q_ptr->height()), false);
            }
        }
    }
}

void SlideWidgetContainerPrivate::startAnimation(QWidget *target, const QPoint &oldPos, const QPoint &newPos, bool add)
{
    QPropertyAnimation* anim = new QPropertyAnimation(target, "pos");
    anim->setEasingCurve(EasingCurve);
    anim->setDuration(SlideDuration);
    anim->setStartValue(oldPos);
    anim->setEndValue(newPos);

    if (add)
        animations.append(anim);

    q_ptr->connect(anim, &QAbstractAnimation::finished, [this, anim] {
        animations.removeAll(anim);
    });
    q_ptr->connect(anim, &QAbstractAnimation::stateChanged, [this, anim] (QAbstractAnimation::State newState, QAbstractAnimation::State oldState) {
        if (newState == QAbstractAnimation::Stopped)
            animations.removeAll(anim);
    });
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

SlideWidgetContainer::SlideWidgetContainer(QWidget *parent) : QWidget(parent)
{
    d_ptr = new SlideWidgetContainerPrivate;
    d_ptr->q_ptr = this;
}

SlideWidgetContainer::~SlideWidgetContainer()
{
    delete d_ptr;
}

void SlideWidgetContainer::addWidget(QWidget* widget)
{
    if (d_ptr->widgets.contains(widget)) {
        qDebug() << "Already contains this widget.";
        return;
    }

    d_ptr->widgets.append(widget);
    if (d_ptr->currentIndex < 0)
    d_ptr->currentIndex = 0;

    if (d_ptr->orientation == Qt::Horizontal)
        d_ptr->layoutWidgetsHorizontally();
    else
        d_ptr->layoutWidgetsVertically();
}

void SlideWidgetContainer::removeWidget(QWidget* widget)
{
    if (!d_ptr->widgets.contains(widget)) {
        qDebug() << "Doesn't contain this widget.";
        return;
    }

    d_ptr->widgets.removeAll(widget);
}

int SlideWidgetContainer::count() const
{
    return d_ptr->widgets.size();
}

int SlideWidgetContainer::currentIndex() const
{
    return d_ptr->currentIndex;
}

void SlideWidgetContainer::setOrientation(Qt::Orientation ori)
{
    if (d_ptr->orientation != ori)
        d_ptr->orientation = ori;
}

Qt::Orientation SlideWidgetContainer::orientation() const
{
    return d_ptr->orientation;
}

QSize SlideWidgetContainer::sizeHint() const
{
    return QSize(400, 400);
}

void SlideWidgetContainer::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

    if (d_ptr->orientation == Qt::Horizontal)
        d_ptr->layoutWidgetsHorizontally();
    else
        d_ptr->layoutWidgetsVertically();
}

void SlideWidgetContainer::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        d_ptr->pressed = true;
        d_ptr->pressedPoint = event->pos();
        d_ptr->stopAnimations();
        setCursor(QCursor(Qt::ClosedHandCursor));
    }
}

void SlideWidgetContainer::mouseMoveEvent(QMouseEvent* event)
{
    if (!d_ptr->pressed) {
        QWidget::mouseMoveEvent(event);
        return;
    }

    if (d_ptr->orientation == Qt::Horizontal)
        d_ptr->slideWidgetHorizontally(event->pos());
    else
        d_ptr->slideWidgetVertically(event->pos());
}

void SlideWidgetContainer::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {

        if (d_ptr->orientation == Qt::Horizontal)
            d_ptr->switchWidgetHorizontally(event->pos());
        else
            d_ptr->switchWidgetVertically(event->pos());

        d_ptr->pressed = false;
        d_ptr->pressedPoint = QPoint();
        setCursor(QCursor(Qt::ArrowCursor));
    }
}

void SlideWidgetContainer::keyPressEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_F1:
        if (d_ptr->orientation == Qt::Horizontal)
            d_ptr->switchWidgetHorizontally(QPoint(-DragThreshold + 10, 10));
        else
            d_ptr->switchWidgetVertically(QPoint(10, -DragThreshold + 10));
        break;

    case Qt::Key_F2:
        if (d_ptr->orientation == Qt::Horizontal)
            d_ptr->switchWidgetHorizontally(QPoint(DragThreshold + 10, 10));
        else
            d_ptr->switchWidgetHorizontally(QPoint(10, DragThreshold + 10));
        break;

    case Qt::Key_F3:
        d_ptr->orientation = (d_ptr->orientation == Qt::Horizontal) ? Qt::Vertical : Qt::Horizontal;
        break;
    }
}


