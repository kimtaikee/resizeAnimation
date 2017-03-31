#ifndef SHADOWWINDOW_H
#define SHADOWWINDOW_H

#include <QWidget>

class ShadowWindowPrivate;
class ShadowWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ShadowWindow(QWidget *parent = 0);
    ~ShadowWindow();

    void setShadowEnabled(bool enable);
    bool shadowEnabled() const;

    QSize sizeHint() const;

private:
    ShadowWindowPrivate* d_ptr;
    Q_DISABLE_COPY(ShadowWindow)
};

#endif // SHADOWWINDOW_H
