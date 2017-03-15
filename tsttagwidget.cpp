#include "tsttagwidget.h"
#include "ui_tsttagwidget.h"
#include "tagwidget.h"

TstTagWidget::TstTagWidget(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::TstTagWidget)
{
    m_ui->setupUi(this);
    m_tagWidget = new TagWidget(this);
    m_ui->previewLayout->addWidget(m_tagWidget);

    // populate tags
    for (int i = 0; i < 100; ++i)
        m_tagWidget->addTag(QString("Tag %1").arg(i + 1));
}

TstTagWidget::~TstTagWidget()
{
    delete m_ui;
}

void TstTagWidget::on_pushButton_clicked()
{
    m_tagWidget->addTag(m_ui->tagEdit->text());
}

void TstTagWidget::on_tagEdit_returnPressed()
{
    m_tagWidget->addTag(m_ui->tagEdit->text());
}
