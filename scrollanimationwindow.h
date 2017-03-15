#ifndef SCROLLANIMATIONWINDOW_H
#define SCROLLANIMATIONWINDOW_H

#include <QDialog>

namespace Ui
{
    class ScrollAnimationWindow;
}

class QPropertyAnimation;
class ScrollAnimationWindow : public QDialog
{
    Q_OBJECT
public:
    explicit ScrollAnimationWindow(QWidget *parent = 0);
    ~ScrollAnimationWindow();

private slots:
    void on_loadImageButton_clicked();
    void on_leftButton_clicked();
    void on_rightButton_clicked();
    void on_topButton_clicked();
    void on_bottomButton_clicked();

private:
    void startAnimation(QObject *target, const QByteArray &propertyName, const QVariant& startValue, const QVariant& endValue);

private:
    Ui::ScrollAnimationWindow *m_ui;
};

#endif // SCROLLANIMATIONWINDOW_H
