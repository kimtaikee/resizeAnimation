#include "bounceindicator.h"

#include <QPainter>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QTime>

inline QColor randomColor()
{
    srand(QTime::currentTime().msecsSinceStartOfDay());
    return QColor(qrand() % 255, qrand() % 255, qrand() % 255);
}

static const QSize ItemSize = QSize(30, 30);
static const int TopMargin = 10;
static const int BounceDuration = 200;
static const QEasingCurve::Type EasingCurve = QEasingCurve::Linear;

class BounceItem : public QWidget
{
    Q_OBJECT
public:
    explicit BounceItem(QWidget* parent = nullptr);
    void setColor(const QColor& clr) { m_color = clr; update(); }
    QColor color() const { return m_color; }

protected:
    void paintEvent(QPaintEvent* event);

private:
    QColor m_color = Qt::blue;
};

BounceItem::BounceItem(QWidget *parent) : QWidget(parent)
{
    setFixedSize(ItemSize);
}

void BounceItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(m_color));
    painter.drawEllipse(rect());
}

class BounceIndicatorPrivate
{
public:
    void layoutItems();
    void makeBounce(int index);

    BounceIndicator* q_ptr;
    bool started = false;
    QList<BounceItem*> items;
    QPropertyAnimation* headAnimation = nullptr;
    QParallelAnimationGroup* parallelAnimGroup = nullptr;
};

void BounceIndicatorPrivate::layoutItems()
{
    int itemCount = items.size();
    static const int ItemSpace = 30;
    int horSpace = ItemSpace;
    for (int i = 0; i < items.size(); ++i) {
        items.at(i)->move(horSpace, (q_ptr->height() / 2)  - (ItemSize.height() / 2));
        horSpace += ItemSize.width() + ItemSpace;
    }
}

void BounceIndicatorPrivate::makeBounce(int index)
{
    if (index >= items.size())
        return;

    BounceItem* item = items.at(index);
    int x = item->x();
    int end = 20;
    int start = 50;

    QPropertyAnimation* anim = new QPropertyAnimation(item, "pos");
    anim->setEasingCurve(EasingCurve);
    anim->setDuration(BounceDuration);
    anim->setStartValue(QPoint(x, start));
    anim->setEndValue(QPoint(x, end));
    anim->start();

    if (index == 0 && !headAnimation)
        headAnimation = anim;

    q_ptr->connect(anim, &QAbstractAnimation::finished, [this, item, x, index, anim, start, end] () {
        QPropertyAnimation* reverseAnim = new QPropertyAnimation(item, "pos");
        reverseAnim->setEasingCurve(EasingCurve);
        reverseAnim->setDuration(BounceDuration);
        reverseAnim->setStartValue(QPoint(x, end));
        reverseAnim->setEndValue(QPoint(x, start));
        reverseAnim->start();

        makeBounce(index + 1);

        if (index == (items.size() - 1))
            q_ptr->connect(reverseAnim, SIGNAL(finished()), headAnimation, SLOT(start()));

        q_ptr->connect(reverseAnim, &QAbstractAnimation::finished, [anim] () {
//            anim->start();
        });
    });
}

BounceIndicator::BounceIndicator(QWidget *parent) : QWidget(parent)
{
    d_ptr = new BounceIndicatorPrivate;
    d_ptr->q_ptr = this;
    setNumberOfItems(7);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

BounceIndicator::~BounceIndicator()
{
    delete d_ptr;
}

void BounceIndicator::setAnimationStarted(bool start)
{
    if (start) {

        if (d_ptr->items.isEmpty())
            return;

        int startIndex = 0;
        d_ptr->makeBounce(startIndex);

    } else {

    }
}

bool BounceIndicator::animationStarted() const
{
    return false;
}

void BounceIndicator::setNumberOfItems(int number)
{
    if (d_ptr->items.size() != number) {
        int delta = number - d_ptr->items.size();
        if (delta > 0) {
            for (int i = 0; i < delta; ++i) {
                BounceItem* item = new BounceItem(this);
                item->setColor(randomColor());
                d_ptr->items.append(item);
            }
        } else {
            for (int i = 0 ; i < qAbs(delta); ++i) {
                BounceItem* bi = d_ptr->items.takeLast();
                delete bi;
                d_ptr->items.pop_back();
            }
        }

        d_ptr->layoutItems();
    }
}

int BounceIndicator::numberOfItems() const
{
    return d_ptr->items.size();
}

QSize BounceIndicator::sizeHint() const
{
    return QSize(300, 80);
}

void BounceIndicator::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    d_ptr->layoutItems();
}

#include "bounceindicator.moc"
