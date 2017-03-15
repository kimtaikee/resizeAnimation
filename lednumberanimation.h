#ifndef LEDNUMBERANIMATION_H
#define LEDNUMBERANIMATION_H

#include <QWidget>

namespace Ui
{
    class LedNumberAnimation;
}

class LedNumber;
class LedNumberAnimation : public QWidget
{
    Q_OBJECT
public:
    explicit LedNumberAnimation(QWidget *parent = 0);
    ~LedNumberAnimation();

private slots:
    void on_numberSpinBox_valueChanged(int arg1);

private:
    Ui::LedNumberAnimation *m_ui;
    LedNumber* m_led = nullptr;
};

#endif // LEDNUMBERANIMATION_H
