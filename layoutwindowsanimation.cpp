#include "layoutwindowsanimation.h"
#include "ui_layoutwindowsanimation.h"

#include <QMdiSubWindow>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

class CustomWidget : public QWidget
{
public:
    explicit CustomWidget(QWidget* parent = nullptr) : QWidget(parent) {}

protected:
    QSize sizeHint() const { return QSize(200, 200); }
};

void addWindowAnimation(QParallelAnimationGroup* paraAnimGroup, QMdiSubWindow* subWin, const QPoint& newPos, const QSize& newSize)
{
    if (!paraAnimGroup)
        return;

    QPropertyAnimation* posAnim = new QPropertyAnimation(subWin, "pos");
    posAnim->setEasingCurve(QEasingCurve::OutCubic);
    posAnim->setDuration(1000);
    posAnim->setStartValue(subWin->pos());
    posAnim->setEndValue(newPos);
    paraAnimGroup->addAnimation(posAnim);

    QPropertyAnimation* sizeAnim = new QPropertyAnimation(subWin, "size");
    sizeAnim->setEasingCurve(QEasingCurve::OutCubic);
    sizeAnim->setDuration(1000);
    sizeAnim->setStartValue(subWin->size());
    sizeAnim->setEndValue(newSize);
    paraAnimGroup->addAnimation(sizeAnim);
}

void cascadeWindows(QMdiArea* mdi)
{
    QParallelAnimationGroup* animGroup = new QParallelAnimationGroup();

    QList<QMdiSubWindow* > subWins = mdi->subWindowList();
    for (int i = 0; i < subWins.size(); ++i)
        addWindowAnimation(animGroup, subWins.at(i), QPoint(i * 30, i * 30), subWins.at(i)->widget()->sizeHint());
    animGroup->start(QAbstractAnimation::DeleteWhenStopped);
}

LayoutWindowsAnimation::LayoutWindowsAnimation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayoutWindowsAnimation)
{
    ui->setupUi(this);
    ui->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}

LayoutWindowsAnimation::~LayoutWindowsAnimation()
{
    delete ui;
}

void LayoutWindowsAnimation::on_addWindowButton_clicked()
{
    CustomWidget* widget = new CustomWidget;
    auto win = ui->mdiArea->addSubWindow(widget);
    win->show();
}

void LayoutWindowsAnimation::on_cascadeButton_clicked()
{
    cascadeWindows(ui->mdiArea);
}
