#include "tstflowlayout.h"
#include "ui_tstflowlayout.h"
#include "flowlayout.h"

#include <QToolButton>

TstFlowLayout::TstFlowLayout(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::TstFlowLayout)
{
    m_ui->setupUi(this);

    m_flowLayout = new FlowLayout();
    m_flowLayout->setAnimated(true);
    m_ui->previewGroupBox->setLayout(m_flowLayout);

    populateButtons();
}

TstFlowLayout::~TstFlowLayout()
{
    delete m_ui;
}

void TstFlowLayout::on_addButton_clicked()
{
    m_flowLayout->addWidget(createButton());
}

void TstFlowLayout::populateButtons()
{
    for (int i = 0; i < 50; ++i)
        m_flowLayout->addWidget(createButton());
}

QToolButton* TstFlowLayout::createButton()
{
    QToolButton* button = new QToolButton(this);
    button->setIconSize(QSize(32, 32));
    button->setAutoRaise(true);
    button->setIcon(QIcon(":/images/bug.png"));
    connect(button, &QAbstractButton::clicked, [this, button] {
        m_flowLayout->removeWidget(button);
        m_flowLayout->update();
        button->deleteLater();
    });

    return button;
}
