#include "inputdialog.h"
#include "ui_inputdialog.h"
#include "eventfilter.h"

#include <QGraphicsDropShadowEffect>

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
        effect->setBlurRadius(20);
        effect->setOffset(0);
        effect->setColor(QColor(112, 181, 245));
        widget->setGraphicsEffect(effect);
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
