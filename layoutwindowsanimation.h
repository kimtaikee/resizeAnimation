#ifndef LAYOUTWINDOWSANIMATION_H
#define LAYOUTWINDOWSANIMATION_H

#include <QWidget>

namespace Ui
{
    class LayoutWindowsAnimation;
}

class LayoutWindowsAnimation : public QWidget
{
    Q_OBJECT
public:
    explicit LayoutWindowsAnimation(QWidget *parent = 0);
    ~LayoutWindowsAnimation();

private slots:
    void on_addWindowButton_clicked();
    void on_cascadeButton_clicked();

private:
    Ui::LayoutWindowsAnimation *ui;
};

#endif // LAYOUTWINDOWSANIMATION_H
