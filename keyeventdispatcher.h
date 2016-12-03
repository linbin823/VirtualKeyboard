#ifndef MOCKUPKEYEVENTDISPATCHER_H
#define MOCKUPKEYEVENTDISPATCHER_H

#include <QObject>

class KeyEventDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit KeyEventDispatcher(QObject *parent = 0);
signals:
    
public slots:
    QObject * getFocusItem(){return m_focusItem;}
    void setFocusItem(QObject *focusItem);
    void sendKeyToFocusItem(const QString &keyText);
private:
    QObject * m_focusItem;
};

#endif // MOCKUPKEYEVENTDISPATCHER_H
