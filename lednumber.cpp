#include "lednumber.h"
#include "ledunit.h"

#include <QMap>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>

static QMap<int, QList<int> > sNumber2PatternMap;
LedNumber::LedNumber(QWidget *parent) : QWidget(parent)
{
    init();
}

void LedNumber::setNumber(int number)
{
    if (m_number != number) {
        m_number = number;

        foreach (LedUnit* unit, m_units) {
            unit->setColor(unit->offColor());
            unit->setOn(false);
        }

        QList<int> ledIndexes = sNumber2PatternMap.value(number);

#define PARALLEL_ANIMATION
#ifdef PARALLEL_ANIMATION
        foreach (int index, ledIndexes)
            m_units.at(index)->setOn(true);
#elif defined(SEQUENCIAL_ANIMATION)
//        QSequentialAnimationGroup* animGroup = new QSequentialAnimationGroup(this);
//        foreach (int index, ledIndexes) {
//            LedUnit* unit = m_units.at(index);
//            QPropertyAnimation* anim = new QPropertyAnimation(unit, "color");
//            anim->setDuration(50);
//            anim->setEasingCurve(QEasingCurve::OutCubic);
//            anim->setStartValue(unit->offColor());
//            anim->setEndValue(unit->onColor());
//            animGroup->addAnimation(anim);
//        }
//        animGroup->start(QAbstractAnimation::DeleteWhenStopped);
#else

#endif
    }
}

int LedNumber::number() const
{
    return m_number;
}

void LedNumber::resizeEvent(QResizeEvent* event)
{
    layoutUnits();
    QWidget::resizeEvent(event);
}

void LedNumber::init()
{
    sNumber2PatternMap.insert(0, QList<int>() << 0 << 1 << 2 << 3 << 4 << 5 << 9 << 10 << 14 << 15 << 19 << 20 << 21 << 22 << 23 << 24);
    sNumber2PatternMap.insert(1, QList<int>() << 2 << 7 << 12 << 17 << 22);
    sNumber2PatternMap.insert(2, QList<int>() << 0 << 1 << 2 << 3 << 4 << 9 << 10 << 11 << 12 << 13 << 14 << 15 << 20 << 21 << 22 << 23 << 24);
    sNumber2PatternMap.insert(3, QList<int>() << 0 << 1 << 2 << 3 << 4 << 9 << 10 << 11 << 12 << 13 << 14 << 19 << 20 << 21 << 22 << 23 << 24);
    sNumber2PatternMap.insert(4, QList<int>() << 0 << 2 << 5 << 7 << 10 << 11 << 12 << 13 << 14 << 17 << 22);
    sNumber2PatternMap.insert(5, QList<int>() << 0 << 1 << 2 << 3 << 4 << 5 << 10 << 11 << 12 << 13 << 14 << 19 << 20 << 21 << 22 << 23 << 24);
    sNumber2PatternMap.insert(6, QList<int>() << 0 << 1 << 2 << 3 << 4 << 5 << 10 << 11 << 12 << 13 << 14 << 15 << 19 << 20 << 21 << 22 << 23 << 24);
    sNumber2PatternMap.insert(7, QList<int>() << 0 << 1 << 2 << 3 << 4 << 9 << 14 << 19 << 24);
    sNumber2PatternMap.insert(8, QList<int>() << 0 << 1 << 2 << 3 << 4 << 5 << 9 << 10 << 11 << 12 << 13 << 14 << 15 << 19 << 20 << 21 << 22 << 23 << 24);
    sNumber2PatternMap.insert(9, QList<int>() << 0 << 1 << 2 << 3 << 4 << 5 << 9 << 10 << 11 << 12 << 13 << 14 << 19 << 20 << 21 << 22 << 23 << 24);

    const int UnitCount = 25;
    for (int i = 0; i < UnitCount; ++i)
        m_units.append(new LedUnit(this));
    setNumber(m_number);
}

void LedNumber::layoutUnits()
{
    int cols = 5;
    int rows = 5;
    int unitWidth = this->width() / 5;
    int unitHeight = this->height() / 5;
    int x = 0;
    int y = 0;
    int index = 0;
    for (int row = 0; row < rows; ++row) {
        x = 0;
        for (int col = 0; col < cols; ++col) {
            LedUnit* unit = m_units.at(index++);
            unit->move(x, y);
            unit->setFixedSize(unitWidth, unitHeight);
            x += unitWidth;
        }

        y += unitHeight;
    }
}
