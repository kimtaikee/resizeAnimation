#include "slidetextanimation.h"
#include "ui_slidetextanimation.h"

#include <QLabel>

#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>

const int Margin = 10;

SlideTextAnimation::SlideTextAnimation(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::SlideTextAnimation)
{
    m_ui->setupUi(this);
    m_label = new QLabel(m_ui->frame);
    m_label->setScaledContents(true);
    m_label->setWordWrap(true);
}

SlideTextAnimation::~SlideTextAnimation()
{
    delete m_ui;
}

void SlideTextAnimation::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    m_label->setFixedWidth(m_ui->frame->width());
}

void SlideTextAnimation::on_goButton_clicked()
{
    m_label->setText(m_ui->textEdit->toPlainText());
    m_label->setFixedWidth(m_ui->frame->width() - 2 * Margin);
    m_label->adjustSize();
    startAnimation();
}

void SlideTextAnimation::on_textEdit_textChanged()
{
    on_goButton_clicked();
}

void SlideTextAnimation::startAnimation()
{
    if (!m_posAnim) {
        m_posAnim = new QPropertyAnimation(m_label, "pos");
        connect(m_posAnim, SIGNAL(finished()), m_posAnim, SLOT(start()));
    }

    m_posAnim->setDuration(m_ui->durationSpinBox->value());
    m_posAnim->setEasingCurve(static_cast<QEasingCurve::Type>(m_ui->easingCurveCombo->currentIndex()));
    m_posAnim->setStartValue(QPoint(Margin, m_ui->frame->height()));
    m_posAnim->setEndValue(QPoint(Margin, -m_label->height()));
    m_posAnim->start();
}
