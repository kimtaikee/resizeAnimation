#ifndef SLIDETEXTANIMATION_H
#define SLIDETEXTANIMATION_H

#include <QWidget>

namespace Ui
{
    class SlideTextAnimation;
}

class QLabel;
class QPropertyAnimation;
class SlideTextAnimation : public QWidget
{
    Q_OBJECT
public:
    explicit SlideTextAnimation(QWidget *parent = 0);
    ~SlideTextAnimation();

protected:
    void resizeEvent(QResizeEvent* event);

private slots:
    void on_goButton_clicked();
    void on_textEdit_textChanged();
    void startAnimation();

private:
    Ui::SlideTextAnimation *m_ui;
    QLabel* m_label = nullptr;
    QPropertyAnimation* m_posAnim = nullptr;
};

#endif // SLIDETEXTANIMATION_H
