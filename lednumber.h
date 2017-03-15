#ifndef LEDNUMBER_H
#define LEDNUMBER_H

#include <QWidget>

class LedUnit;
class LedNumber : public QWidget
{
    Q_OBJECT
public:
    explicit LedNumber(QWidget *parent = 0);

    void setNumber(int number);
    int number() const;

protected:
    void resizeEvent(QResizeEvent* event);

private:
    void init();
    void layoutUnits();

private:
    int m_number = 0;
    QList<LedUnit*> m_units;
};

#endif // LEDNUMBER_H
