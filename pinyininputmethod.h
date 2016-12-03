#ifndef PINYININPUTMETHOD_H
#define PINYININPUTMETHOD_H

#include <QObject>
#include <QStringList>

class CPinyinInputMethod: public QObject
{
Q_OBJECT
public:
    CPinyinInputMethod();
    ~CPinyinInputMethod();

signals:
    void pinyinTextChanged(const QString&);

public:
    void SearchCN(const QString &gemfield);
    void BinarySearchEN(const QString &gemfield);
    void Matching(const QString &gemfield, bool isEn = true);
    QStringList HanziModel;

private:
    QStringList lstEN;
};

#endif
