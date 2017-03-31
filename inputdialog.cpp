#include "inputdialog.h"
#include "ui_inputdialog.h"
#include "eventfilter.h"

#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>

InputDialog::InputDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::InputDialog)
{
    m_ui->setupUi(this);

    // remove the question mark
    setWindowFlags(windowFlags() & (~Qt::WindowContextHelpButtonHint));

    EventFilter* evtFilter = new EventFilter(this);
    evtFilter->addFilteredObject(m_ui->lineEdit);
    evtFilter->addFilteredObject(m_ui->textEdit);

    m_ui->lineEdit->installEventFilter(evtFilter);
    m_ui->textEdit->installEventFilter(evtFilter);

    auto addDropShadow = [] (QWidget* widget) {
        QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
        effect->setOffset(0);
        effect->setColor(QColor(112, 181, 245));
        widget->setGraphicsEffect(effect);

        QPropertyAnimation* anim = new QPropertyAnimation(effect, "blurRadius");
        anim->setDuration(500);
        anim->setEasingCurve(QEasingCurve::OutCubic);
        anim->setStartValue(0);
        anim->setEndValue(20);
        anim->start(QAbstractAnimation::DeleteWhenStopped);
    };

    auto removeDropShadow = [] (QWidget* widget) {
        widget->setGraphicsEffect(nullptr);
    };

    connect(evtFilter, &EventFilter::filterEvent, [=, this] (QObject* obj, QEvent* evt) {
        if (evt->type() == QEvent::Enter) {
            if (obj == m_ui->lineEdit)
                addDropShadow(m_ui->lineEdit);
            else if (obj == m_ui->textEdit)
                addDropShadow(m_ui->textEdit);
        } else if (evt->type() == QEvent::Leave) {
            if (obj == m_ui->lineEdit)
                removeDropShadow(m_ui->lineEdit);
            else if (obj == m_ui->textEdit)
                removeDropShadow(m_ui->textEdit);
        }
    });
}

InputDialog::~InputDialog()
{
    delete m_ui;
}
