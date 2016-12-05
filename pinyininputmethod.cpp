#include "pinyininputmethod.h"
#include <QDateTime>
#include <QSettings>
#include <QDebug>
#include "pinyinime.h"
using namespace ime_pinyin;

CPinyinInputMethod::CPinyinInputMethod()
{
    HanziModel.clear();

    QSettings setter(":/dict/pinyinEx.ini", QSettings::IniFormat);

    lstEN = setter.value("pyEn", lstEN).toStringList();
    if (lstEN.size() <= 1)
    {
        qDebug() << "Can't load pyEn!";
        return;
    }
    bool ret = im_open_decoder("./dict/dict_pinyin.dat", "./dict/user.dat");
    if (!ret)
    {
        qDebug() << "open dict faild";
        return;
    }
}

CPinyinInputMethod::~CPinyinInputMethod()
{
    lstEN.clear();
    HanziModel.clear();
    im_close_decoder();
}

void CPinyinInputMethod::SearchCN(const QString &gemfield)
{
    HanziModel.clear();
    if (gemfield == "")
    {
        emit pinyinTextChanged("");
        return;
    }
    im_reset_search();
    int num = im_search(gemfield.toLatin1().data(), gemfield.size());
    const uint16 *pos;
    int size = im_get_spl_start_pos(pos);
    QString py = gemfield;
    for (int i = size-1; i > 0; i--)
        py.insert(pos[i], "'");
    py.replace("''", "'");
    emit pinyinTextChanged(py);
    if (num > 50) num = 50;
    char16 buf[20]={0};
    for (int i = 0; i < num; i++)
    {
        im_get_candidate(i, buf, 20);
        HanziModel << QString::fromUtf16(buf);
    }
}

void CPinyinInputMethod::BinarySearchEN(const QString &gemfield)
{
    emit pinyinTextChanged(gemfield);
    int min = 0;
    int max = lstEN.size();
    int idx = max / 2;

    while (true)
    {
        if (lstEN[idx].startsWith(gemfield, Qt::CaseInsensitive))
            break;
        if (max == min + 1 || max <= min || max == idx + 1 || max == idx || min == idx + 1 || min == idx )
            break;
        if (lstEN[idx].toLower() > gemfield)
            max = idx;
        else
            min = idx;
        idx = (max + min) / 2;
    }
    do{
        if (--idx < 0)
            break;
    }while(lstEN[idx].startsWith(gemfield, Qt::CaseInsensitive));

    ++idx;
    int cnt = 0;
    while(++cnt < 50)
    {
        if (idx >= lstEN.size())
            break;
        if (lstEN[idx].startsWith(gemfield, Qt::CaseInsensitive))
            HanziModel.append(lstEN[idx]);
        else
            break;
        idx++;
    }
}

void CPinyinInputMethod::Matching(const QString &gemfield, bool isEn)
{
    HanziModel.clear();
    if (!isEn) SearchCN(gemfield);
    else BinarySearchEN(gemfield);
}
