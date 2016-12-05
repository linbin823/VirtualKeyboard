#ifndef KEYBOARDFROM_H
#define KEYBOARDFROM_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "pinyininputmethod.h"

class KeyboardForm : public QDialog
{
    Q_OBJECT
public:
    explicit KeyboardForm(QWidget *parent = 0);
    ~KeyboardForm();

signals:
    void sendKeyToFocusItem(const QString &keyText);

public slots:
    void slotBtnClicked();
    void btnClicked();
    void slotHaiziBtnClicked();
    void setText(QString str);
    void shiftClicked();
    void changeInputMode();
    void changeSymbol();
    void space();
    void enter();
    void backSpace();
    void prevPage();
    void nextPage();

private:
    void mousePressEvent(QMouseEvent*e);
    void mouseMoveEvent(QMouseEvent*e);
    void mouseReleaseEvent(QMouseEvent*e);
    void displayHanzi();

private:
    QWidget* m_pyFrm, *m_btnFrm; // 拼音面板
    QLineEdit *m_txtPinYin;  // 真实拼音
    QLabel *m_labPyText;  // 分割拼音
    QList<QPushButton*> m_listHanzi;
    QList<QList<QPushButton*> >m_listCharsBtns; // A-Z Symbol
    QList<QList<QPushButton*> >m_listBtns;
    QVBoxLayout *m_mainLayout;
    QPushButton *m_btnChange, *m_btnShift, *m_btnSymbol, *m_btnSpace; // 显示切换输入法
    CPinyinInputMethod m_pinyinInput;

    enum InputMode{ImEn, ImCn, ImNum};
    InputMode m_inputMode;
    bool m_isShiftInput;
    int m_hanziPageCnt, m_curHanziPage;
    bool m_isMousePress;
    QPoint m_movePoint;
};
#endif // KEYBOARDFROM_H
