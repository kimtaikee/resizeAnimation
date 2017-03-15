#ifndef FRAME_H
#define FRAME_H

#include <QWidget>

class Frame : public QWidget
{
    Q_OBJECT
public:
    explicit Frame(QWidget *parent = 0);

    void setColor(const QColor& clr);
    QColor color() const;

protected:
    void paintEvent(QPaintEvent* event);

private:
    QColor m_color = Qt::blue;
};

#endif // FRAME_H
