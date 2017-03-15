#include "explodeanimation.h"
#include "ui_explodeanimation.h"

#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

ExplodeAnimation::ExplodeAnimation(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::ExplodeAnimation)
{
    m_ui->setupUi(this);
}

ExplodeAnimation::~ExplodeAnimation()
{
    delete m_ui;
}

void ExplodeAnimation::on_pushButton_clicked()
{
    QParallelAnimationGroup* animGroup = new QParallelAnimationGroup(this);

    const int DeltaSize = 150;
    QRect newGeo(QPoint(this->pos() - QPoint(DeltaSize / 2, DeltaSize / 2)), this->size() + QSize(DeltaSize, DeltaSize));

    QPropertyAnimation* sizeAnim = new QPropertyAnimation(this, "geometry");
    sizeAnim->setEasingCurve(QEasingCurve::OutCubic);
    sizeAnim->setDuration(500);
    sizeAnim->setStartValue(this->geometry());
    sizeAnim->setEndValue(newGeo);

    QPropertyAnimation* opacityAnim = new QPropertyAnimation(this, "windowOpacity");
    opacityAnim->setEasingCurve(QEasingCurve::OutCubic);
    opacityAnim->setDuration(500);
    opacityAnim->setStartValue(1);
    opacityAnim->setEndValue(0);

    animGroup->addAnimation(sizeAnim);
    animGroup->addAnimation(opacityAnim);
    animGroup->start(QAbstractAnimation::DeleteWhenStopped);

    connect(animGroup, SIGNAL(finished()), this, SLOT(close()));
}
