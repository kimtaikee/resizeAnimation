#ifndef EXPLODEANIMATION_H
#define EXPLODEANIMATION_H

#include <QWidget>

namespace Ui
{
    class ExplodeAnimation;
}

class ExplodeAnimation : public QWidget
{
    Q_OBJECT
public:
    explicit ExplodeAnimation(QWidget *parent = 0);
    ~ExplodeAnimation();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ExplodeAnimation *m_ui;
};

#endif // EXPLODEANIMATION_H
