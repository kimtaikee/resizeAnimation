#include "flyawayanimation.h"
#include "ui_flyawayanimation.h"

#include <QDesktopWidget>
#include <QPropertyAnimation>
#include <QCloseEvent>
#include <QClipboard>

#ifdef Q_OS_WIN
#include <windows.h>

// Borrowed from https://causeyourestuck.io/2016/01/12/screenshot-c-win32-api/
void takeScreenshot(POINT a, POINT b)
{
    // copy screen to bitmap
    HDC     hScreen = GetDC(NULL);
    HDC     hDC     = CreateCompatibleDC(hScreen);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, abs(b.x-a.x), abs(b.y-a.y));
    HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
    BOOL    bRet    = BitBlt(hDC, 0, 0, abs(b.x-a.x), abs(b.y-a.y), hScreen, a.x, a.y, SRCCOPY);

    // save bitmap to clipboard
    OpenClipboard(NULL);
    EmptyClipboard();
    SetClipboardData(CF_BITMAP, hBitmap);
    CloseClipboard();

    // clean up
    SelectObject(hDC, old_obj);
    DeleteDC(hDC);
    ReleaseDC(NULL, hScreen);
    DeleteObject(hBitmap);
}

int titleBarHeight()
{
    return (GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYCAPTION) +
        GetSystemMetrics(SM_CXPADDEDBORDER));
}

QSize widgetSize(QWidget* widget)
{
    if (!widget)
        return QSize();

    RECT rect;
    int width, height;
    if(GetWindowRect((HWND)widget->winId(), &rect)) {
        width = rect.right - rect.left;
        height= rect.bottom - rect.top;
    }

    return QSize(width, height);
}
#endif // Q_OS_WIN

FlyAwayAnimation::FlyAwayAnimation(QWidget *parent) : QWidget(parent)
{
    m_ui = new Ui::FlyAwayAnimation;
    m_ui->setupUi(this);
}

FlyAwayAnimation::~FlyAwayAnimation()
{
    delete m_ui;
}

void FlyAwayAnimation::closeEvent(QCloseEvent *e)
{
    QLabel* label = new QLabel();
    QPixmap oriScreenshot = screenshot();

    label->setWindowFlags(Qt::ToolTip);
    label->setAttribute(Qt::WA_TranslucentBackground);
    label->setPixmap(oriScreenshot);
    label->move(mapToGlobal(this->pos()));
    label->resize(this->size());
    label->show();

    QDesktopWidget desktop;
    QWidget* screen = desktop.screen();
    QPoint endPos(screen->width(), 0);
    QRect startGeo(geometry());

#ifdef Q_OS_WIN
    startGeo = QRect(QPoint(startGeo.topLeft().x() - GetSystemMetrics(SM_CXSIZEFRAME),
                            startGeo.topLeft().y() - titleBarHeight()), widgetSize(this));
#endif

    QPropertyAnimation* anim = new QPropertyAnimation(label, "geometry");
    anim->setDuration(1000);
    anim->setEasingCurve(QEasingCurve::OutCubic);
    anim->setStartValue(startGeo);
    anim->setEndValue(QRect(endPos, QSize(0, 0)));
    anim->start(QAbstractAnimation::DeleteWhenStopped);
    connect(anim, &QAbstractAnimation::finished, label, &QWidget::deleteLater);
    connect(anim, &QAbstractAnimation::stateChanged, [=] (QAbstractAnimation::State newState, QAbstractAnimation::State oldState) {
        if (newState == QAbstractAnimation::Stopped)
            label->deleteLater();
    });

    connect(anim, &QPropertyAnimation::valueChanged, [=] {
        QPixmap scaledScreenshot = oriScreenshot.scaled(label->size());

        // if the scaled pixmap is null the stop the animation immediately, and delete the label
        if (scaledScreenshot.isNull()) {
            anim->stop();
            return;
        }
        label->setPixmap(scaledScreenshot);
    });

    e->accept();
}

QPixmap FlyAwayAnimation::screenshot()
{
#ifdef Q_OS_WIN
    QPoint globalTopLeft = this->pos();
    QSize wSize = widgetSize(this);

    POINT topLeft {globalTopLeft.x(), globalTopLeft.y() };
    POINT bottomRight{globalTopLeft.x() + wSize.width(),
                globalTopLeft.y() + wSize.height()};
    takeScreenshot(topLeft, bottomRight);
#endif

    return QApplication::clipboard()->pixmap();
}
