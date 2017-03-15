#include "slidemenuanimation.h"

#include <QContextMenuEvent>
#include <QMenu>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QDebug>

SlideMenuAnimation::SlideMenuAnimation(QWidget *parent) : QWidget(parent)
{
    populateMenu();
}

void SlideMenuAnimation::contextMenuEvent(QContextMenuEvent *event)
{
#if 0
    QPoint pos = event->pos();
    if (pos.x() > (width() / 2))
        slideIn(Right);
    else
        slideIn(Left);
#endif
    expand(event->globalPos());
}

void SlideMenuAnimation::keyPressEvent(QKeyEvent* event)
{
    QWidget::keyPressEvent(event);

    if (event->key() == Qt::Key_F1)
        m_direction = (m_direction == Left) ? Right: Left;
}

void SlideMenuAnimation::slideIn(Direction d)
{
    m_direction = d;
    m_menu->show();

    QPropertyAnimation* anim = new QPropertyAnimation(m_menu, "pos");
    anim->setDuration(500);
    anim->setEasingCurve(QEasingCurve::OutCubic);

    QPoint globalTopLeft = pos();

    if (d == Left) {
        anim->setStartValue(QPoint(-m_menu->width() + globalTopLeft.x(), globalTopLeft.y()));
        anim->setEndValue(globalTopLeft);
    } else {
        anim->setStartValue(QPoint(globalTopLeft.x() + width(), globalTopLeft.x()));
        anim->setEndValue(QPoint(globalTopLeft.x() + width() - m_menu->width(), globalTopLeft.x()));
    }

    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void SlideMenuAnimation::slideOut(Direction d)
{
    m_direction = d;
    m_menu->show();

    QPropertyAnimation* anim = new QPropertyAnimation(m_menu, "pos");
    anim->setDuration(500);
    anim->setEasingCurve(QEasingCurve::OutCubic);

    QPoint globalTopLeft = pos();

    if (d == Left) {
        anim->setStartValue(m_menu->pos());
        anim->setEndValue(QPoint(-m_menu->width(), 0));
    } else {
        anim->setStartValue(m_menu->pos());
        anim->setEndValue(QPoint(width(), 0));
    }

    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void SlideMenuAnimation::expand(const QPoint& globalPos)
{
    m_globalPos = globalPos;
    m_menu->exec(globalPos);

    QPropertyAnimation* anim = new QPropertyAnimation(m_menu, "size");
    anim->setDuration(500);
    anim->setEasingCurve(QEasingCurve::OutCubic);
    anim->setStartValue(QSize(0, m_menu->height()));
    anim->setEndValue(QSize(m_menu->width(), m_menu->height()));

    QPropertyAnimation* opacityAnim = new QPropertyAnimation(m_menu, "windowOpacity");
    opacityAnim->setDuration(500);
    opacityAnim->setEasingCurve(QEasingCurve::OutCubic);
    opacityAnim->setStartValue(0);
    opacityAnim->setEndValue(1);

    QParallelAnimationGroup* animGroup = new QParallelAnimationGroup();
    animGroup->addAnimation(anim);
    animGroup->addAnimation(opacityAnim);
    animGroup->start(QAbstractAnimation::DeleteWhenStopped);
}

void SlideMenuAnimation::populateMenu()
{
    m_menu = new QMenu(this);

    auto onActionTriggered = [this] {
//        slideOut(m_direction);
    };

    m_menu->addAction("Action 1", onActionTriggered);
    m_menu->addAction("Action 2", onActionTriggered);
    m_menu->addAction("Action 3", onActionTriggered);
    m_menu->addAction("Action 4", onActionTriggered);
    m_menu->addAction("Action 5", onActionTriggered);
    m_menu->addAction("Action 6", onActionTriggered);
    m_menu->addAction("Action 7", onActionTriggered);
    m_menu->addAction("Action 8", onActionTriggered);
    m_menu->addAction("Action 9", onActionTriggered);
}

