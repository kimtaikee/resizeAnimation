#ifndef TSTTAGWIDGET_H
#define TSTTAGWIDGET_H

#include <QWidget>

namespace Ui
{
    class TstTagWidget;
}

class TagWidget;
class TstTagWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TstTagWidget(QWidget *parent = 0);
    ~TstTagWidget();

private slots:
    void on_pushButton_clicked();
    void on_tagEdit_returnPressed();

private:
    Ui::TstTagWidget *m_ui;
    TagWidget* m_tagWidget = nullptr;
};

#endif // TSTTAGWIDGET_H
