#ifndef BOUNCEINDICATOR_H
#define BOUNCEINDICATOR_H

#include <QWidget>

class BounceIndicatorPrivate;
class BounceIndicator : public QWidget
{
    Q_OBJECT
public:
    explicit BounceIndicator(QWidget *parent = 0);
    ~BounceIndicator();

public slots:
    void setAnimationStarted(bool start);
    bool animationStarted() const;

    void setNumberOfItems(int number);
    int numberOfItems() const;

protected:
    QSize sizeHint() const;
    void resizeEvent(QResizeEvent* event);

private:
    BounceIndicatorPrivate* d_ptr;
    Q_DISABLE_COPY(BounceIndicator)
};

#endif // BOUNCEINDICATOR_H
