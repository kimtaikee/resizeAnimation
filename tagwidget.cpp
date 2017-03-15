#include "tagwidget.h"
#include "flowlayout.h"

#include <QMap>
#include <QLabel>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QPainter>

static const int TagMargin = 5;
static const int RoundRadius = 6;

#define COLOR_SCHEME1
#ifdef COLOR_SCHEME1
static const QColor NormalBackgroundColor = QColor(240, 240, 240);
static const QColor HoverBackgroundColor = QColor(49, 101, 148);
static const QColor NormalTextColor = QColor(69, 149, 212);
static const QColor HoverTextColor = QColor(250, 250, 250);
static const QColor BorderColor = QColor(211, 211, 211);
#else
static const QColor NormalBackgroundColor = QColor(254, 197, 86);
static const QColor HoverBackgroundColor = QColor(255, 238, 100);
static const QColor NormalTextColor = QColor(156, 124, 117);
static const QColor HoverTextColor = QColor(156, 124, 117);
static const QColor BorderColor = QColor(239, 187, 98);
#endif

class Tag : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
public:
    explicit Tag(QWidget* parent = nullptr);

    void setText(const QString& text);
    QString text() const;

    void setTextColor(const QColor& clr);
    QColor textColor() const;

    void setBackgroundColor(const QColor& clr);
    QColor backgroundColor() const;

    void setHoverBackgroundColor(const QColor& clr);
    QColor hoverBackgroundColor() const;

protected:
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent *event);
    void paintEvent(QPaintEvent* event);

protected:
    QString m_text;
    QColor m_backgroundColor = NormalBackgroundColor;
    QColor m_textColor = NormalTextColor;
};

Tag::Tag(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
}

void Tag::setText(const QString& text)
{
    if (m_text != text) {
        m_text = text;
        int textLen = fontMetrics().width(text);
        setFixedSize(QSize(textLen + 2 * TagMargin, fontMetrics().height() + 2 * TagMargin));
        update();
    }
}

QString Tag::text() const
{
    return m_text;
}

void Tag::setTextColor(const QColor& clr)
{
    if (m_textColor != clr) {
        m_textColor = clr;
        update();
    }
}

QColor Tag::textColor() const
{
    return m_textColor;
}

void Tag::setBackgroundColor(const QColor& clr)
{
    if (m_backgroundColor != clr) {
        m_backgroundColor = clr;
        update();
    }
}

QColor Tag::backgroundColor() const
{
    return m_backgroundColor;
}

void Tag::enterEvent(QEvent* event)
{
    QWidget::enterEvent(event);

    QPropertyAnimation* bgColorAnim = new QPropertyAnimation(this, "backgroundColor");
    bgColorAnim->setEasingCurve(QEasingCurve::OutCubic);
    bgColorAnim->setDuration(1000);
    bgColorAnim->setStartValue(NormalBackgroundColor);
    bgColorAnim->setEndValue(HoverBackgroundColor);

    QPropertyAnimation* textColorAnim = new QPropertyAnimation(this, "textColor");
    textColorAnim->setEasingCurve(QEasingCurve::OutCubic);
    textColorAnim->setDuration(1000);
    textColorAnim->setStartValue(NormalTextColor);
    textColorAnim->setEndValue(HoverTextColor);

    QParallelAnimationGroup* animGroup = new QParallelAnimationGroup();
    animGroup->addAnimation(bgColorAnim);
    animGroup->addAnimation(textColorAnim);
    animGroup->start(QAbstractAnimation::DeleteWhenStopped);
}

void Tag::leaveEvent(QEvent *event)
{
    QWidget::leaveEvent(event);

    QPropertyAnimation* bgColorAnim = new QPropertyAnimation(this, "backgroundColor");
    bgColorAnim->setEasingCurve(QEasingCurve::OutCubic);
    bgColorAnim->setDuration(1000);
    bgColorAnim->setStartValue(HoverBackgroundColor);
    bgColorAnim->setEndValue(NormalBackgroundColor);

    QPropertyAnimation* textColorAnim = new QPropertyAnimation(this, "textColor");
    textColorAnim->setEasingCurve(QEasingCurve::OutCubic);
    textColorAnim->setDuration(1000);
    textColorAnim->setStartValue(HoverTextColor);
    textColorAnim->setEndValue(NormalTextColor);

    QParallelAnimationGroup* animGroup = new QParallelAnimationGroup();
    animGroup->addAnimation(bgColorAnim);
    animGroup->addAnimation(textColorAnim);
    animGroup->start(QAbstractAnimation::DeleteWhenStopped);
}

void Tag::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    // draw background
    painter.save();
    painter.setBrush(QBrush(m_backgroundColor));
    painter.setPen(QPen(BorderColor, 1));
    painter.drawRoundedRect(rect(), RoundRadius, RoundRadius);
    painter.restore();

    // draw text
    painter.save();
    painter.setPen(QPen(m_textColor, 1));
    painter.drawText(rect(), m_text, Qt::AlignHCenter | Qt::AlignVCenter);
    painter.restore();
}

class TagWidgetPrivate
{
public:
    void init();

    TagWidget* q_ptr;
    QWidget* container;
    FlowLayout* layout;

    QMap<QString, Tag*> tags;
};

void TagWidgetPrivate::init()
{
    container = new QWidget(q_ptr);
    container->setStyleSheet("background-color:white;");
    q_ptr->setWidget(container);
    q_ptr->setWidgetResizable(true);

    layout = new FlowLayout;
    container->setLayout(layout);
}

TagWidget::TagWidget(QWidget* parent) : QScrollArea(parent)
{
    d_ptr = new TagWidgetPrivate;
    d_ptr->q_ptr = this;
    d_ptr->init();
}

TagWidget::~TagWidget()
{
    delete d_ptr;
}

void TagWidget::addTag(const QString& name)
{
    if (d_ptr->tags.contains(name))
        return;

    Tag* tag = new Tag(this);
    tag->setText(name);
    d_ptr->layout->addWidget(tag);
    d_ptr->tags.insert(name, tag);
}

void TagWidget::removeTag(const QString& name)
{
    if (!d_ptr->tags.contains(name))
        return;

    Tag* tag = d_ptr->tags.value(name);
    delete tag;
    d_ptr->tags.remove(name);
}

void TagWidget::clear()
{
    qDeleteAll(d_ptr->tags.values());
    d_ptr->tags.clear();
}

QStringList TagWidget::tags() const
{
    return d_ptr->tags.keys();
}

#include "tagwidget.moc"
