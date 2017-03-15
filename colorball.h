#ifndef COLORBALL_H
#define COLORBALL_H

#include <QWidget>

class ColorBall : public QWidget
{
    Q_OBJECT
public:
    explicit ColorBall(QWidget *parent = 0);

    void setColor(const QColor& clr);
    QColor color() const;

protected:
    void paintEvent(QPaintEvent *event);

private:
    QColor m_color = Qt::red;
};

#endif // COLORBALL_H
