#ifndef FLYAWAYANIMATION_H
#define FLYAWAYANIMATION_H

#include <QWidget>

namespace Ui
{
    class FlyAwayAnimation;
}

class FlyAwayAnimation : public QWidget
{
    Q_OBJECT
public:
    explicit FlyAwayAnimation(QWidget *parent = 0);
    ~FlyAwayAnimation();

protected:
    void closeEvent(QCloseEvent* e);

    QPixmap screenshot();

private:
    Ui::FlyAwayAnimation* m_ui = nullptr;
};

#endif // FLYAWAYANIMATION_H
