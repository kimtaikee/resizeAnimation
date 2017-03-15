#include "fadingtoolbutton.h"

#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>

static const int MinBlurRadius = 5;
static const int MaxBlurRadius = 40;
static const int Duration = 1000;

class FadingToolButtonPrivate
{
public:
    void init();
    void startFading();
    void stopFading();

    FadingToolButton* q_ptr;
    QPropertyAnimation* fadeInAnim = nullptr;
    QPropertyAnimation* fadeOutAnim = nullptr;
};

void FadingToolButtonPrivate::init()
{
    fadeInAnim = new QPropertyAnimation(q_ptr);
    fadeInAnim->setEasingCurve(QEasingCurve::Linear);
    fadeInAnim->setDuration(Duration);
    fadeInAnim->setStartValue(MinBlurRadius);
    fadeInAnim->setEndValue(MaxBlurRadius);

    fadeOutAnim = new QPropertyAnimation(q_ptr);
    fadeOutAnim->setEasingCurve(QEasingCurve::Linear);
    fadeOutAnim->setDuration(Duration);
    fadeOutAnim->setStartValue(MaxBlurRadius);
    fadeOutAnim->setEndValue(MinBlurRadius);

    QObject::connect(fadeInAnim, SIGNAL(finished()), fadeOutAnim, SLOT(start()));
    QObject::connect(fadeOutAnim, SIGNAL(finished()), fadeInAnim, SLOT(start()));
}

void FadingToolButtonPrivate::startFading()
{
    QGraphicsDropShadowEffect* dropShadow = new QGraphicsDropShadowEffect();
    dropShadow->setOffset(0);

    q_ptr->setGraphicsEffect(dropShadow);
    fadeInAnim->setTargetObject(dropShadow);
    fadeInAnim->setPropertyName("blurRadius");

    fadeOutAnim->setTargetObject(dropShadow);
    fadeOutAnim->setPropertyName("blurRadius");
    fadeInAnim->start();
}

void FadingToolButtonPrivate::stopFading()
{
    q_ptr->setGraphicsEffect(nullptr);
    fadeInAnim->stop();
    fadeOutAnim->stop();
}

FadingToolButton::FadingToolButton(QWidget* parent) : QToolButton(parent)
{
    d_ptr = new FadingToolButtonPrivate;
    d_ptr->q_ptr = this;
    d_ptr->init();
}

FadingToolButton::~FadingToolButton()
{
    delete d_ptr;
}

void FadingToolButton::enterEvent(QEvent* event)
{
    d_ptr->startFading();
    QToolButton::enterEvent(event);
}

void FadingToolButton::leaveEvent(QEvent* event)
{
    d_ptr->stopFading();
    QToolButton::leaveEvent(event);
}

