#include "lednumberanimation.h"
#include "ui_lednumberanimation.h"
#include "lednumber.h"

LedNumberAnimation::LedNumberAnimation(QWidget *parent) :
    QWidget(parent), m_ui(new Ui::LedNumberAnimation)
{
    m_ui->setupUi(this);

    m_led = new LedNumber(m_ui->groupBox_2);
    m_ui->previewLayout->addWidget(m_led);
}

LedNumberAnimation::~LedNumberAnimation()
{
    delete m_ui;
}

void LedNumberAnimation::on_numberSpinBox_valueChanged(int arg1)
{
    m_led->setNumber(arg1);
}
