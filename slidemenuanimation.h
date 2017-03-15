#ifndef SLIDEMENUANIMATION_H
#define SLIDEMENUANIMATION_H

#include <QWidget>

class QMenu;
class SlideMenuAnimation : public QWidget
{
    Q_OBJECT
    enum Direction { Left, Right };
public:
    explicit SlideMenuAnimation(QWidget *parent = 0);

protected:
    void contextMenuEvent(QContextMenuEvent *event);
    void keyPressEvent(QKeyEvent* event);

private:
    void slideIn(Direction d);
    void slideOut(Direction d);
    void expand(const QPoint& globalPos);
    void populateMenu();

private:
    QMenu* m_menu;
    QPoint m_globalPos;
    Direction m_direction = Left;
};

#endif // SLIDEMENUANIMATION_H
