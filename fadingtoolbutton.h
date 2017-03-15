#ifndef FADINGTOOLBUTTON_H
#define FADINGTOOLBUTTON_H

#include <QToolButton>

class FadingToolButtonPrivate;
class FadingToolButton : public QToolButton
{
    Q_OBJECT
public:
    explicit FadingToolButton(QWidget* parent = nullptr);
    ~FadingToolButton();

protected:
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent* event);

private:
    FadingToolButtonPrivate* d_ptr;
    Q_DISABLE_COPY(FadingToolButton)
};

#endif // FADINGTOOLBUTTON_H
