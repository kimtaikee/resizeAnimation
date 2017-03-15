#include "scrollanimationwindow.h"
#include "ui_scrollanimationwindow.h"

#include <QScrollBar>
#include <QFileDialog>
#include <QPropertyAnimation>

ScrollAnimationWindow::ScrollAnimationWindow(QWidget *parent) :
    QDialog(parent), m_ui(new Ui::ScrollAnimationWindow)
{
    m_ui->setupUi(this);
    m_ui->scrollArea->setWidgetResizable(true);
    setWindowTitle(tr("Scroll Animation"));
}

ScrollAnimationWindow::~ScrollAnimationWindow()
{
    delete m_ui;
}

void ScrollAnimationWindow::on_loadImageButton_clicked()
{
    QString imageFile = QFileDialog::getOpenFileName(this, tr("Load Image"), ".", "PNG Files(*.png);;JPG Files(*.jpg)");
    if (imageFile.isEmpty())
        return;

    QPixmap pixmap(imageFile);
    m_ui->imageLabel->setPixmap(pixmap);
}

void ScrollAnimationWindow::on_leftButton_clicked()
{
    auto horBar = m_ui->scrollArea->horizontalScrollBar();
    startAnimation(horBar, "value", horBar->value(), 0);
}

void ScrollAnimationWindow::on_rightButton_clicked()
{
    auto horBar = m_ui->scrollArea->horizontalScrollBar();
    startAnimation(horBar, "value", horBar->value(), horBar->maximum());
}

void ScrollAnimationWindow::on_topButton_clicked()
{
    auto verBar = m_ui->scrollArea->verticalScrollBar();
    startAnimation(verBar, "value", verBar->value(), 0);
}

void ScrollAnimationWindow::on_bottomButton_clicked()
{
    auto verBar = m_ui->scrollArea->verticalScrollBar();
    startAnimation(verBar, "value", verBar->value(), verBar->maximum());
}

void ScrollAnimationWindow::startAnimation(QObject *target, const QByteArray &propertyName, const QVariant& startValue, const QVariant& endValue)
{
    QPropertyAnimation* anim = new QPropertyAnimation(target, propertyName);
    anim->setDuration(1000);
    anim->setStartValue(startValue);
    anim->setEndValue(endValue);
    anim->setEasingCurve(QEasingCurve::OutCubic);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

