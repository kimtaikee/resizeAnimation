#ifndef TABLESELECTIONANIMATION_H
#define TABLESELECTIONANIMATION_H

#include <QWidget>

namespace Ui
{
    class TableSelectionAnimation;
}

class Frame;
class TableSelectionAnimation : public QWidget
{
    Q_OBJECT
public:
    explicit TableSelectionAnimation(QWidget *parent = 0);
    ~TableSelectionAnimation();

private:
    void populateTable();

private:
    Ui::TableSelectionAnimation *m_ui;
    Frame* m_frame = nullptr;
};

#endif // TABLESELECTIONANIMATION_H
