#ifndef TSTFLOWLAYOUT_H
#define TSTFLOWLAYOUT_H

#include <QWidget>

namespace Ui
{
    class TstFlowLayout;
}

class FlowLayout;
class QToolButton;
class TstFlowLayout : public QWidget
{
    Q_OBJECT
public:
    explicit TstFlowLayout(QWidget *parent = 0);
    ~TstFlowLayout();

private slots:
    void on_addButton_clicked();

private:
    void populateButtons();
    QToolButton* createButton();

private:
    Ui::TstFlowLayout *m_ui;
    FlowLayout* m_flowLayout;
};

#endif // TSTFLOWLAYOUT_H
