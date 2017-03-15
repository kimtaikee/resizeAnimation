#ifndef TAGWIDGET_H
#define TAGWIDGET_H

#include <QScrollArea>

class TagWidgetPrivate;
class TagWidget : public QScrollArea
{
    Q_OBJECT
public:
    explicit TagWidget(QWidget* parent = nullptr);
    ~TagWidget();

    void addTag(const QString& name);
    void removeTag(const QString& name);
    void clear();

    QStringList tags() const;

private:
    TagWidgetPrivate* d_ptr;
    Q_DISABLE_COPY(TagWidget)
};

#endif // TAGWIDGET_H
