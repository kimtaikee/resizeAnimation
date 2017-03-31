#include "eventfilter.h"

EventFilter::EventFilter(QObject *parent) : QObject(parent)
{

}

void EventFilter::addFilteredObject(QObject *obj)
{
    m_targets.append(obj);
}

bool EventFilter::eventFilter(QObject *obj, QEvent *e)
{
    bool ret = QObject::eventFilter(obj, e);

    if (m_targets.contains(obj))
        emit filterEvent(obj, e);

    return ret;
}

