#include "widget.h"
#include "ui_widget.h"
#include "changeshapecanvas.h"
#include "slidetextanimation.h"
#include "layoutwindowsanimation.h"
#include "colorball.h"
#include "tagwidget.h"
#include "tsttagwidget.h"
#include "bounceindicator.h"
#include "slidewidgetcontainer.h"
#include "tstflowlayout.h"
#include "explodeanimation.h"
#include "tableselectionanimation.h"
#include "lednumberanimation.h"
#include "slidemenuanimation.h"
#include "shadowwindow.h"
#include "inputdialog.h"
#include "circle.h"
#include "flyawayanimation.h"
#include "highlighwindow.h"

#include <QPainter>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QTimer>
#include <QDesktopWidget>
#include <QTime>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

static const int Duration = 500;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::Widget)
{
    m_ui->setupUi(this);
    m_ui->toolButton->setIcon(QIcon(":/images/navigate.png"));
    m_ui->toolButton->setIconSize(QSize(64, 64));
}

Widget::~Widget()
{
    delete m_ui;
}

float Widget::rotation() const
{
    return m_rotation;
}

void Widget::setRotation(float rotation)
{
    m_rotation = rotation;

    if (!m_flipLabel) {
        m_flipLabel = new QLabel();
    }

    m_flipLabel->setWindowTitle(windowTitle());
    m_flipLabel->move(pos());
    m_flipLabel->resize(size());
    m_flipLabel->show();

    QPixmap pixmap = grab(rect());
    QPainter painter(&pixmap);

    QTransform transform;
    transform.translate(width() / 2, 0);

    if(m_rotation > 90)
        transform.rotate(m_rotation + 180, Qt::YAxis);
    else
        transform.rotate(m_rotation, Qt::YAxis);

    painter.setTransform(transform);
    painter.drawPixmap(-1 * width() / 2, 0, pixmap);
    m_flipLabel->setPixmap(pixmap);
}

void Widget::flyIn()
{
    // TODO
}

void Widget::flyOut()
{
    // TODO
}

QSize Widget::sizeHint() const
{
    return QSize(300, 500);
}

void Widget::closeEvent(QCloseEvent* e)
{
    m_keepRaining = false;
    QWidget::close();
}

void Widget::on_resizeButton_clicked()
{
    doAnimation();
}

void Widget::on_easingCurveCombo_currentIndexChanged(int index)
{
    m_easingCurve = index;
}

void Widget::doAnimation()
{
#if 1
    QPropertyAnimation* animation = new QPropertyAnimation(this, "size");
    animation->setDuration(Duration);
    animation->setStartValue(this->size());
    animation->setEasingCurve(QEasingCurve(static_cast<QEasingCurve::Type>(m_easingCurve)));
    animation->setEndValue(QSize(width() + 30, height() + 100));
//    animation->start(QAbstractAnimation::DeleteWhenStopped);
#elif 1
    QPropertyAnimation *animation = new QPropertyAnimation(this, "pos");
    animation->setDuration(Duration);
    animation->setEasingCurve(QEasingCurve(static_cast<QEasingCurve::Type>(m_easingCurve)));
    animation->setStartValue(this->pos());
    animation->setEndValue(QPoint(0,0));
    animation->start(QAbstractAnimation::DeleteWhenStopped);
#elif 0
    QRect startRect(60, 0, 5, 5);
    QRect endRect(60, 0, 300, 300);
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(Duration);
    animation->setEasingCurve(QEasingCurve(static_cast<QEasingCurve::Type>(m_easingCurve)));
    animation->setStartValue(startRect);
    animation->setEndValue(endRect);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
#endif

    QPropertyAnimation* animation2 = new QPropertyAnimation(this, "windowOpacity");
    animation2->setDuration(Duration);
    animation2->setEasingCurve(QEasingCurve::Linear);
    animation2->setStartValue(0.0);
    animation2->setEndValue(1.0);
//    animation2->start(QAbstractAnimation::DeleteWhenStopped);

    QParallelAnimationGroup *group = new QParallelAnimationGroup;
    group->addAnimation(animation);
    group->addAnimation(animation2);
    group->start(QAbstractAnimation::DeleteWhenStopped);
}

void Widget::on_dropShadowCheckBox_toggled(bool checked)
{

    QList<QPushButton*> buttons = findChildren<QPushButton*>();
    foreach (QPushButton* button, buttons) {
        QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(this);
        effect->setBlurRadius(15);
        effect->setOffset(0);
        button->setGraphicsEffect(checked ? effect : nullptr);
    }
}

void Widget::on_shakeButton_clicked()
{
    const int DeltaPos = 10;

    QPropertyAnimation *animation = new QPropertyAnimation(this, "pos");
    animation->setDuration(500);

    if (m_ui->shakeDirectionCombo->currentIndex() == 0) {
        int oldX = pos().x();
        animation->setEasingCurve(QEasingCurve(static_cast<QEasingCurve::Type>(m_easingCurve)));
        animation->setKeyValueAt(0.0, QPoint(oldX - DeltaPos, pos().y()));
        animation->setKeyValueAt(0.1, QPoint(oldX + DeltaPos, pos().y()));
        animation->setKeyValueAt(0.2, QPoint(oldX - DeltaPos, pos().y()));
        animation->setKeyValueAt(0.3, QPoint(oldX + DeltaPos, pos().y()));
        animation->setKeyValueAt(0.4, QPoint(oldX - DeltaPos, pos().y()));
        animation->setKeyValueAt(0.5, QPoint(oldX + DeltaPos, pos().y()));
        animation->setKeyValueAt(0.6, QPoint(oldX - DeltaPos, pos().y()));
        animation->setKeyValueAt(0.7, QPoint(oldX + DeltaPos, pos().y()));
        animation->setKeyValueAt(0.8, QPoint(oldX - DeltaPos, pos().y()));
        animation->setKeyValueAt(0.9, QPoint(oldX + DeltaPos, pos().y()));
        animation->setKeyValueAt(1.0, QPoint(oldX, pos().y()));
    } else {
        int oldY = pos().y();
        animation->setEasingCurve(QEasingCurve(static_cast<QEasingCurve::Type>(m_easingCurve)));
        animation->setKeyValueAt(0.0, QPoint(pos().x(), oldY + DeltaPos));
        animation->setKeyValueAt(0.1, QPoint(pos().x(), oldY - DeltaPos));
        animation->setKeyValueAt(0.2, QPoint(pos().x(), oldY + DeltaPos));
        animation->setKeyValueAt(0.3, QPoint(pos().x(), oldY - DeltaPos));
        animation->setKeyValueAt(0.4, QPoint(pos().x(), oldY + DeltaPos));
        animation->setKeyValueAt(0.5, QPoint(pos().x(), oldY - DeltaPos));
        animation->setKeyValueAt(0.6, QPoint(pos().x(), oldY + DeltaPos));
        animation->setKeyValueAt(0.7, QPoint(pos().x(), oldY - DeltaPos));
        animation->setKeyValueAt(0.8, QPoint(pos().x(), oldY + DeltaPos));
        animation->setKeyValueAt(0.9, QPoint(pos().x(), oldY - DeltaPos));
        animation->setKeyValueAt(1.0, QPoint(pos().x(), oldY));
    }
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void Widget::on_shrinkButton_clicked()
{
    m_shrinkOldSize = size();
    QPropertyAnimation* sizeAnim = new QPropertyAnimation(this, "size");
    sizeAnim->setStartValue(size());
    sizeAnim->setEasingCurve(QEasingCurve(static_cast<QEasingCurve::Type>(m_easingCurve)));
    sizeAnim->setEndValue(QSize(width(), this->minimumHeight()));

    QPoint topLeft = pos();
    m_shrinkOldPos = topLeft;
    QPropertyAnimation* posAnim = new QPropertyAnimation(this, "pos");
    posAnim->setStartValue(topLeft);
    posAnim->setEndValue(QPoint(topLeft.x(), topLeft.y() + (height() - minimumHeight())/ 2));
    posAnim->setEasingCurve(QEasingCurve(static_cast<QEasingCurve::Type>(m_easingCurve)));

    QParallelAnimationGroup* animGroup = new QParallelAnimationGroup(this);
    animGroup->addAnimation(sizeAnim);
    animGroup->addAnimation(posAnim);
    animGroup->start(QAbstractAnimation::DeleteWhenStopped);
}

void Widget::on_expandButton_clicked()
{
    QPropertyAnimation* sizeAnim = new QPropertyAnimation(this, "size");
    sizeAnim->setStartValue(size());
    sizeAnim->setEasingCurve(QEasingCurve(static_cast<QEasingCurve::Type>(m_easingCurve)));
    sizeAnim->setEndValue(m_shrinkOldSize);

    QPoint topLeft = pos();
    QPropertyAnimation* posAnim = new QPropertyAnimation(this, "pos");
    posAnim->setStartValue(topLeft);
    posAnim->setEndValue(m_shrinkOldPos);
    posAnim->setEasingCurve(QEasingCurve(static_cast<QEasingCurve::Type>(m_easingCurve)));

    QParallelAnimationGroup* animGroup = new QParallelAnimationGroup(this);
    animGroup->addAnimation(sizeAnim);
    animGroup->addAnimation(posAnim);
    animGroup->start(QAbstractAnimation::DeleteWhenStopped);
}

void Widget::on_shakeDirectionCombo_currentIndexChanged(int index)
{
    Q_UNUSED(index)
    on_shakeButton_clicked();
}

void Widget::on_fadeInButton_clicked()
{
    QPropertyAnimation* opacityAnim = new QPropertyAnimation(this, "windowOpacity");
    opacityAnim->setStartValue(0);
    opacityAnim->setEndValue(1);
    opacityAnim->setDuration(1000);
    opacityAnim->setEasingCurve(QEasingCurve(static_cast<QEasingCurve::Type>(m_easingCurve)));

    QPropertyAnimation* sizeAnim = new QPropertyAnimation(this, "size");
    sizeAnim->setStartValue(QSize(sizeHint().width(), 0));
    sizeAnim->setEndValue(this->sizeHint());
    sizeAnim->setDuration(1000);
    sizeAnim->setEasingCurve(QEasingCurve(static_cast<QEasingCurve::Type>(m_easingCurve)));

    QParallelAnimationGroup* animGroup = new QParallelAnimationGroup(this);
    animGroup->addAnimation(opacityAnim);
    animGroup->addAnimation(sizeAnim);
    animGroup->start(QAbstractAnimation::DeleteWhenStopped);
}

void Widget::on_fadeOutButton_clicked()
{

}

void Widget::on_flipButton_clicked()
{
    QPropertyAnimation *flipAnim = new QPropertyAnimation(this, "rotation");
    flipAnim->setDuration(5000);
    flipAnim->setEasingCurve(QEasingCurve::InQuad);
    flipAnim->setStartValue(0);
    flipAnim->setEndValue(180);
    connect(flipAnim, &QAbstractAnimation::finished, [this] () {
        m_fliping = false;
        m_flipLabel->hide();
        show();
    });

    flipAnim->start(QAbstractAnimation::DeleteWhenStopped);
    hide();
    m_fliping = true;
}

void Widget::on_newWindowButton_clicked()
{
    QPushButton* nwButton = m_ui->newWindowButton;
    QPoint nwButtonGlobalTopLeft = mapToGlobal(nwButton->geometry().topLeft());

    QWidget* fooWidget = new QWidget();

    QPropertyAnimation* resizeAnim = new QPropertyAnimation(fooWidget, "size");
    resizeAnim->setDuration(500);
    resizeAnim->setEasingCurve(static_cast<QEasingCurve::Type>(m_easingCurve));
    resizeAnim->setStartValue(nwButton->size());
    resizeAnim->setEndValue(QSize(500, 400));

    QPropertyAnimation* posAnim = new QPropertyAnimation(fooWidget, "pos");
    posAnim->setDuration(500);
    posAnim->setEasingCurve(static_cast<QEasingCurve::Type>(m_easingCurve));
    posAnim->setStartValue(nwButtonGlobalTopLeft);
    posAnim->setEndValue(QPoint(300, 200));

    QParallelAnimationGroup* animGroup = new QParallelAnimationGroup();
    animGroup->addAnimation(resizeAnim);
    animGroup->addAnimation(posAnim);
    animGroup->start(QAbstractAnimation::DeleteWhenStopped);

    connect(animGroup, &QAbstractAnimation::finished, [=] () {
        QTimer::singleShot(3000, fooWidget, SLOT(deleteLater()));
    });

    fooWidget->show();
}

void Widget::on_changeShapeButton_clicked()
{
    ChangeShapeCanvas* canvas = new ChangeShapeCanvas;
    canvas->show();
}

void Widget::on_slideTextButton_clicked()
{
    SlideTextAnimation* sta = new SlideTextAnimation;
    sta->show();
}

void Widget::on_layoutWindowsButton_clicked()
{
    LayoutWindowsAnimation* lwa = new LayoutWindowsAnimation;
    lwa->show();
}

void Widget::on_toolButton_clicked()
{
    QPropertyAnimation* shrinkAnim = new QPropertyAnimation(m_ui->toolButton, "iconSize");
    shrinkAnim->setEasingCurve(QEasingCurve::OutCubic);
    shrinkAnim->setDuration(300);
    shrinkAnim->setStartValue(QSize(64, 64));
    shrinkAnim->setEndValue(QSize(32, 32));

    QPropertyAnimation* enlargeAnim = new QPropertyAnimation(m_ui->toolButton, "iconSize");
    enlargeAnim->setEasingCurve(QEasingCurve::OutCubic);
    enlargeAnim->setDuration(300);
    enlargeAnim->setStartValue(QSize(32, 32));
    enlargeAnim->setEndValue(QSize(64, 64));

    QSequentialAnimationGroup* animGroup = new QSequentialAnimationGroup();
    animGroup->addAnimation(shrinkAnim);
    animGroup->addAnimation(enlargeAnim);
    animGroup->start(QAbstractAnimation::DeleteWhenStopped);
}

int getTaskBarHeight()
{
#ifdef Q_OS_WIN
//    return 35;
    RECT rect;
    HWND taskBar = FindWindow(L"Shell_traywnd", NULL);
    if(taskBar && GetWindowRect(taskBar, &rect))
        return rect.bottom - rect.top;
#else
    return 0;
#endif
}

void Widget::on_popupWindowButton_clicked()
{
    QWidget* widget = new QWidget;
    widget->resize(QSize(150, 100));
    widget->show();

    QDesktopWidget desktop;
    QRect desktopRect = desktop.availableGeometry();
    const int HorMargin = 10;

    QPropertyAnimation* posAnim = new QPropertyAnimation(widget, "pos");
    posAnim->setEasingCurve(QEasingCurve::OutCubic);
    posAnim->setDuration(500);
    posAnim->setStartValue(QPoint(desktopRect.bottomRight().x() - widget->width() - HorMargin, desktopRect.bottomRight().y() - getTaskBarHeight()));
    posAnim->setEndValue(QPoint(desktopRect.bottomRight().x() - widget->width() - HorMargin, desktopRect.bottomRight().y() - widget->height() - getTaskBarHeight()));

    QPropertyAnimation* opacityAnim = new QPropertyAnimation(widget, "windowOpacity");
    opacityAnim->setEasingCurve(QEasingCurve::OutCubic);
    opacityAnim->setDuration(500);
    opacityAnim->setStartValue(0);
    opacityAnim->setEndValue(1);

    QParallelAnimationGroup* animGroup = new QParallelAnimationGroup(this);
    animGroup->addAnimation(posAnim);
    animGroup->addAnimation(opacityAnim);
    animGroup->start(QAbstractAnimation::DeleteWhenStopped);

    connect(animGroup, &QAbstractAnimation::finished, [widget] () {
        QTimer::singleShot(1000, widget, SLOT(deleteLater()));
    });
}

void Widget::on_slideInButton_clicked()
{
    QDesktopWidget desktop;
    QRect desktopRect = desktop.availableGeometry();

    if (!m_colorBall) {
        m_colorBall = new ColorBall();
        m_colorBall->setColor(QColor(qrand() % 255, qrand() % 255, qrand() % 255));
    }

    m_colorBall->show();

    QPropertyAnimation* anim = new QPropertyAnimation(m_colorBall, "pos");
    anim->setEasingCurve(static_cast<QEasingCurve::Type>(m_easingCurve));
    anim->setDuration(500);
    anim->setStartValue(QPoint(desktopRect.width() + m_colorBall->width(), 20));
    anim->setEndValue(QPoint(m_colorBall->width()/*desktopRect.width() - m_colorBall->width() * 2*/, 20));
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void Widget::on_slideOutButton_clicked()
{
    QDesktopWidget desktop;
    QRect desktopRect = desktop.availableGeometry();

    if (!m_colorBall) {
        m_colorBall = new ColorBall();
        m_colorBall->setColor(QColor(qrand() % 255, qrand() % 255, qrand() % 255));
    }

    m_colorBall->show();

    QPropertyAnimation* anim = new QPropertyAnimation(m_colorBall, "pos");
    anim->setEasingCurve(static_cast<QEasingCurve::Type>(m_easingCurve));
    anim->setDuration(500);
    anim->setStartValue(m_colorBall->pos());
    anim->setEndValue(QPoint(desktopRect.width() + m_colorBall->width(), 20));
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void Widget::on_tagButton_clicked()
{
    TstTagWidget* tagWidget = new TstTagWidget;
    tagWidget->show();
}

void Widget::on_imageCarouselButton_clicked()
{

}

void Widget::on_bounceButton_clicked()
{
    BounceIndicator* bi = new BounceIndicator;
    bi->setAnimationStarted(true);
    bi->show();
}

void Widget::on_slideWidgetButton_clicked()
{
    SlideWidgetContainer* container = new SlideWidgetContainer();

    // populate tags
    for (int tagIndex = 0; tagIndex < 5; ++tagIndex) {
        TagWidget* tagWidget = new TagWidget(container);
        tagWidget->setStyleSheet(QString("background-color:rgb(%1, %2, %3);").arg(qrand() % 255).arg(qrand() % 255).arg(qrand() % 255));

        for (int i = 0; i < 100; ++i)
            tagWidget->addTag(QString("Tag %1").arg(i + 1));
        container->addWidget(tagWidget);
    }

    container->show();
}

void Widget::on_fadingCheckBox_toggled(bool checked)
{
    QList<QAbstractButton*> buttons = findChildren<QAbstractButton*>();
    const int MaxBlurRadius = 30;
    const int MinBlurRadius = 3;
    const int Duration = 1000;
    foreach (QAbstractButton* button, buttons) {
        QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(this);
        effect->setBlurRadius(15);
        effect->setOffset(0);
        button->setGraphicsEffect(checked ? effect : nullptr);

        if (checked) {
            QPropertyAnimation* anim = new QPropertyAnimation(effect, "blurRadius");
            anim->setDuration(Duration);
            anim->setEasingCurve(QEasingCurve::Linear);
            anim->setStartValue(MinBlurRadius);
            anim->setEndValue(MaxBlurRadius);
            connect(anim, &QAbstractAnimation::finished, [=] {
                QPropertyAnimation* reverseAnim = new QPropertyAnimation(effect, "blurRadius");
                reverseAnim->setDuration(Duration);
                reverseAnim->setEasingCurve(QEasingCurve::Linear);
                reverseAnim->setStartValue(MaxBlurRadius);
                reverseAnim->setEndValue(MinBlurRadius);
                reverseAnim->start();
                connect(reverseAnim, &QAbstractAnimation::finished, [=] {
                    anim->start();
                });
            });
            anim->start();
        }
    }
}

void Widget::on_tstFlowLayout_clicked()
{
    static TstFlowLayout* tstFlowLayout = nullptr;
    if (!tstFlowLayout)
        tstFlowLayout = new TstFlowLayout;
    tstFlowLayout->show();
}

void Widget::on_explodeButton_clicked()
{
    ExplodeAnimation* explodeAnim = new ExplodeAnimation;
    explodeAnim->show();
}

void Widget::on_tableSelectionButton_clicked()
{
    TableSelectionAnimation* tableSelectionAnimation = new TableSelectionAnimation();
    tableSelectionAnimation->show();
}

void Widget::on_ledDisplayButton_clicked()
{
    LedNumberAnimation* lna = new LedNumberAnimation;
    lna->show();
}

void Widget::on_slideMenuButton_clicked()
{
    SlideMenuAnimation* sma = new SlideMenuAnimation;
    sma->show();
}

void Widget::on_shadowWindowButton_clicked()
{
    ShadowWindow* sw = new ShadowWindow;
    sw->show();
}

void Widget::on_inputButton_clicked()
{
    InputDialog* inputDlg = new InputDialog;
    inputDlg->show();
}

void Widget::on_rainButton_toggled(bool checked)
{
    m_keepRaining = checked;
    makeItRain();
}

void delay(int millisecondsToWait)
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
}

void Widget::makeItRain()
{
    QDesktopWidget desktop;
    int desktopWidth = desktop.screen()->width();
    int desktopHeight = desktop.screen()->height();

    QPoint randomPos;
    while (m_keepRaining) {
        randomPos = QPoint(qrand() % desktopWidth, qrand() % desktopHeight);

        Circle* circle = new Circle();
        circle->move(randomPos);
        circle->show();

//#define RAINBOW_RAIN
#ifdef RAINBOW_RAIN
        circle->setColor(QColor(qrand() % 255, qrand() % 255, qrand() % 255));
#endif

        QPropertyAnimation* radiusAnim = new QPropertyAnimation(circle, "radius");
        radiusAnim->setEasingCurve(QEasingCurve::Linear);
        radiusAnim->setDuration(1000);
        radiusAnim->setStartValue(1);
        radiusAnim->setEndValue(80);

        QPropertyAnimation* opacityAnim = new QPropertyAnimation(circle, "windowOpacity");
        opacityAnim->setEasingCurve(QEasingCurve::Linear);
        opacityAnim->setDuration(1000);
        opacityAnim->setStartValue(1);
        opacityAnim->setEndValue(0);

        QParallelAnimationGroup* animGroup = new QParallelAnimationGroup();
        animGroup->addAnimation(radiusAnim);
        animGroup->addAnimation(opacityAnim);
        animGroup->start(QAbstractAnimation::DeleteWhenStopped);
        connect(animGroup, &QAbstractAnimation::finished, circle, &QWidget::deleteLater);

        delay(10);
    }
}

void Widget::on_flyAwayButton_clicked()
{
    FlyAwayAnimation* faa = new FlyAwayAnimation;
    faa->show();
}

void Widget::on_highlightWindowButton_clicked()
{
    static HighlighWindow* sHw = nullptr;
    if (!sHw) {
        sHw = new HighlighWindow(this);
    }
    sHw->show();
}
