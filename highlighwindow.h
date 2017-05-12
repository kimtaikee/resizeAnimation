#ifndef HIGHLIGHWINDOW_H
#define HIGHLIGHWINDOW_H

#include <QWidget>

class HighlighWindow : public QWidget
{
    Q_OBJECT
public:
    explicit HighlighWindow(QWidget *parent = 0);
    ~HighlighWindow();
};

#endif // HIGHLIGHWINDOW_H
