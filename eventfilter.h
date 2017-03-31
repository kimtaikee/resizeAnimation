#ifndef EVENTFILTER
#define EVENTFILTER

#include <QObject>

class QEvent;
class EventFilter : public QObject
{
    Q_OBJECT
public:
    explicit EventFilter(QObject* parent = nullptr);

    void addFilteredObject(QObject* obj);

signals:
    void filterEvent(QObject* obj, QEvent *e);

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    QObjectList m_targets;
};

#endif // EVENTFILTER

