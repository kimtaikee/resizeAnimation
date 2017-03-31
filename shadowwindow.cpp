#include "shadowwindow.h"

#include <QGraphicsDropShadowEffect>
#include <QLabel>
#include <QTextEdit>

class ShadowWindowPrivate
{
public:
    void init();

    ShadowWindow* q_ptr;
    bool enabled = true;
};

void ShadowWindowPrivate::init()
{
    q_ptr->setWindowTitle(QObject::tr("Shadow Window"));

    q_ptr->setWindowFlags(Qt::FramelessWindowHint);
    q_ptr->setAttribute(Qt::WA_TranslucentBackground);

    QGraphicsDropShadowEffect *wndShadow = new QGraphicsDropShadowEffect;
    wndShadow->setBlurRadius(9.0);
    wndShadow->setColor(QColor(0, 0, 0, 160));
    wndShadow->setOffset(4.0);
    q_ptr->setGraphicsEffect(wndShadow);
}

ShadowWindow::ShadowWindow(QWidget *parent) : QWidget(parent)
{
    d_ptr = new ShadowWindowPrivate;
    d_ptr->q_ptr = this;
    d_ptr->init();
}

ShadowWindow::~ShadowWindow()
{
    delete d_ptr;
}

void ShadowWindow::setShadowEnabled(bool enable)
{
    if (d_ptr->enabled != enable) {
        d_ptr->enabled = enable;
        if (enable) {
            QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
            shadowEffect->setBlurRadius(15);
            shadowEffect->setOffset(0);
            setGraphicsEffect(shadowEffect);
        } else {
            setGraphicsEffect(nullptr);
        }
    }
}

bool ShadowWindow::shadowEnabled() const
{
    return d_ptr->enabled;
}

QSize ShadowWindow::sizeHint() const
{
    return QSize(400, 400);
}


