#include "KeyboardForm.h"
#include <QKeyEvent>
#include <QFontDatabase>
#include <QApplication>

const char *kbLetter = "qwertyuiopasdfghjklzxcvbnm";
const char *kbSymbol = "1234567890=!@#$%^~*()-+/:;";

const int verticalSpacing = 10;
const int horizontalSpacing = 10;
const int margins = 10;
const int btnHeight = (250 - verticalSpacing*5)/4;
const int btnWidth = (1080 - margins)/11.5 - horizontalSpacing;

KeyboardForm::KeyboardForm(QWidget *parent) :
    QDialog(parent)
{
    setWindowModality(Qt::WindowModal);
    //setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint	| Qt::WindowDoesNotAcceptFocus);
    setWindowFlags(windowFlags() | Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint	| Qt::WindowDoesNotAcceptFocus);

    setWindowOpacity(1);
    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("QLabel{font: bold normal 24px 'Consolas'} QWidget QPushButton{border-image: url(:/images/btn1.png); border-width: 5; font: bold normal } QPushButton:pressed{border-image: url(:/images/btn3.png); border-width: 5;}");

    QFontDatabase::addApplicationFont(":/FontAwesome.otf");
    QFont icofont("FontAwesome");
    icofont.setPixelSize(32);

    QFont deffont("Consolas");
    deffont.setPixelSize(24);

    m_inputMode = ImEn;
    m_isMousePress = false;
    m_isShiftInput = false;
    m_mainLayout = new QVBoxLayout;
    m_mainLayout->setMargin(margins);
    m_mainLayout->setSpacing(horizontalSpacing);

    // 显示拼音 lineEdit
    m_pyFrm = new QWidget;
    m_txtPinYin = new QLineEdit;
    m_labPyText = new QLabel;
    m_labPyText->hide();
    m_labPyText->setStyleSheet("background: #a0ffffff; border-color: gray; border-width: 1px; border-style: solid; border-radius: 5px;");
    QHBoxLayout *hl1 = new QHBoxLayout;
    QVBoxLayout *vl = new QVBoxLayout;
    QVBoxLayout *mvl = new QVBoxLayout;
    mvl->setMargin(0);
    mvl->setSpacing(0);
    hl1->setMargin(0);
    hl1->setSpacing(horizontalSpacing);
    hl1->addWidget(m_labPyText);
    hl1->addWidget(m_txtPinYin);
    hl1->addStretch();
    m_txtPinYin->hide();
    connect(m_txtPinYin, SIGNAL(textChanged(QString)), SLOT(setText(QString)));

    // 汉字
    QHBoxLayout *hl2 = new QHBoxLayout;
    hl2->setSpacing(horizontalSpacing);
    for (int i = 0; i < 10; i++)
    {
        QPushButton *btn = new QPushButton;
        btn->setFont(deffont);
        btn->setStyleSheet("QPushButton{border: none; border-image: none; font: 20px} QPushButton:focus{color: #ff8000; padding: -20;}");
        hl2->addWidget(btn);
        m_listHanzi.append(btn);
        if (i != 0 && i != 9)
            connect(btn, SIGNAL(clicked()), SLOT(slotHaiziBtnClicked()));
    }
    m_listHanzi[0]->setText("\xC2\xAB");// "\xC2\xBB" : "\xC2\xAB"
    m_listHanzi[0]->setEnabled(false);
    m_listHanzi[0]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_listHanzi[9]->setText("\xC2\xBB");
    m_listHanzi[9]->setEnabled(false);
    m_listHanzi[9]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(m_listHanzi[0], SIGNAL(clicked()), SLOT(prevPage()));
    connect(m_listHanzi[9], SIGNAL(clicked()), SLOT(nextPage()));
    vl->addStretch();
    vl->addLayout(hl1);
    m_pyFrm->setLayout(hl2);
    //pyFrm->hide();
    m_pyFrm->setStyleSheet("background:#FFFFFF");
    vl->addWidget(m_pyFrm);
    mvl->addLayout(vl);

    // 字母
    QList<QPushButton*> list;
    QHBoxLayout *hl3 = new QHBoxLayout;
    hl3->setSpacing(horizontalSpacing);
    int idx = 0;
    for (int j = 0; j < 10; j++)
    {
        QPushButton *btn = new QPushButton(QString(QLatin1Char(kbLetter[idx++])));
        btn->setFixedSize(btnWidth, btnHeight);
        btn->setFont(deffont);
        connect(btn, SIGNAL(clicked()), SLOT(slotBtnClicked()));
        hl3->addWidget(btn);
        list.append(btn);
    }
    QPushButton *btnBack = new QPushButton("\uf060");
    btnBack->setFont(icofont);
    btnBack->setFixedSize(btnWidth*1.5, btnHeight);
    btnBack->setStyleSheet("QPushButton{color:#FFFFFF; border-image: url(:/images/btn2.png); border-width: 5;} QPushButton:pressed{border-image: url(:/images/btn3.png); border-width: 5;}");
    connect(btnBack, SIGNAL(clicked()), SLOT(backSpace()));
    hl3->addWidget(btnBack);

    m_mainLayout->addLayout(hl3);
    m_listBtns.append(list);
    m_listCharsBtns.append(list);

    list.clear();
    QHBoxLayout *hl6 = new QHBoxLayout;
    hl6->setSpacing(horizontalSpacing);
    for (int j = 0; j < 9; j++)
    {
        QPushButton *btn = new QPushButton(QString(QLatin1Char(kbLetter[idx++])));
        btn->setFont(deffont);
        btn->setFixedSize(btnWidth, btnHeight);
        connect(btn, SIGNAL(clicked()), SLOT(slotBtnClicked()));
        hl6->addWidget(btn);
        list.append(btn);
    }
    QPushButton *btnEnter = new QPushButton("ENTER");
    btnEnter->setFont(deffont);
    btnEnter->setFixedSize(btnWidth*2, btnHeight);
    btnEnter->setStyleSheet("QPushButton{color:#FFFFFF; border-image: url(:/images/btn2.png); border-width: 5;} QPushButton:pressed{border-image: url(:/images/btn3.png); border-width: 5;}");
    connect(btnEnter, SIGNAL(clicked()), SLOT(enter()));
    hl6->addWidget(btnEnter);
    m_mainLayout->addLayout(hl6);
    m_listBtns.append(list);
    m_listCharsBtns.append(list);

    list.clear();
    QHBoxLayout *hl5 = new QHBoxLayout;
    hl5->setSpacing(horizontalSpacing);

    m_btnShift = new QPushButton("\uf062");
    m_btnShift->setFont(icofont);
    m_btnShift->setFixedSize(btnWidth*1.5, btnHeight);
    m_btnShift->setStyleSheet("QPushButton{color:#FFFFFF; border-image: url(:/images/btn2.png); border-width: 5;} QPushButton:pressed{border-image: url(:/images/btn3.png); border-width: 5;}");
    connect(m_btnShift, SIGNAL(clicked()), SLOT(shiftClicked()));
    hl5->addWidget(m_btnShift);
    for (int j = 0; j < 7; j++)
    {
        QPushButton *btn = new QPushButton(QString(QLatin1Char(kbLetter[idx++])));
        btn->setFont(deffont);
        btn->setFixedSize(btnWidth, btnHeight);
        connect(btn, SIGNAL(clicked()), SLOT(slotBtnClicked()));
        hl5->addWidget(btn);
        list.append(btn);
    }
    QPushButton* btn = new QPushButton(",");
    btn->setFont(deffont);
    btn->setFixedSize(btnWidth, btnHeight);
    connect(btn, SIGNAL(clicked()), SLOT(btnClicked()));
    hl5->addWidget(btn);

    btn = new QPushButton(".");
    btn->setFont(deffont);
    btn->setFixedSize(btnWidth, btnHeight);
    connect(btn, SIGNAL(clicked()), SLOT(btnClicked()));
    hl5->addWidget(btn);

    btn = new QPushButton("/");
    btn->setFont(deffont);
    btn->setFixedSize(btnWidth, btnHeight);
    connect(btn, SIGNAL(clicked()), SLOT(btnClicked()));
    hl5->addWidget(btn);

    m_mainLayout->addLayout(hl5);
    m_listBtns.append(list);
    m_listCharsBtns.append(list);

    // last
    QHBoxLayout *hl4 = new QHBoxLayout;
    hl4->setSpacing(horizontalSpacing);
    QList<QPushButton*> list2;

    m_btnSymbol = new QPushButton(".123");
    m_btnSymbol->setFont(deffont);
    m_btnSymbol->setFixedSize(btnWidth*1.5, btnHeight);
    m_btnSymbol->setStyleSheet("QPushButton{color:#FFFFFF; border-image: url(:/images/btn2.png); border-width: 5;} QPushButton:pressed{border-image: url(:/images/btn3.png); border-width: 5;}");
    connect(m_btnSymbol, SIGNAL(clicked()), SLOT(changeSymbol()));
    list2.append(m_btnSymbol);
    hl4->addWidget(m_btnSymbol);

    m_btnChange = new QPushButton("\uf0ac");
    //btnChange->setIconSize(QSize(28, 28 ));
    m_btnChange->setFont(icofont);
    m_btnChange->setProperty("Mode", ImEn);
    m_btnChange->setFixedSize(btnWidth*1.5, btnHeight);
    m_btnChange->setStyleSheet("QPushButton{color:#FFFFFF; border-image: url(:/images/btn2.png); border-width: 5;} QPushButton:pressed{border-image: url(:/images/btn3.png); border-width: 5;}");
    connect(m_btnChange, SIGNAL(clicked()), SLOT(changeInputMode()));
    list2.append(m_btnChange);
    hl4->addWidget(m_btnChange);

    m_btnSpace = new QPushButton("英文");  // 空格
    m_btnSpace->setFont(deffont);
    m_btnSpace->setFixedHeight(btnHeight);
    connect(m_btnSpace, SIGNAL(clicked()), SLOT(space()));
    list2.append(m_btnSpace);
    hl4->addWidget(m_btnSpace);

    QPushButton *btnSplit = new QPushButton("'");
    btnSplit->setFont(deffont);
    btnSplit->setFixedSize(btnWidth*1.5, btnHeight);
    connect(btnSplit, SIGNAL(clicked()), SLOT(slotBtnClicked()));
    list2.append(btnSplit);
    hl4->addWidget(btnSplit);

    QPushButton *btnHide = new QPushButton("\uf11c\uf103");
    btnHide->setFont(icofont);
    btnHide->setFixedSize(btnWidth*1.5, btnHeight);
    btnHide->setStyleSheet("QPushButton{color:#FFFFFF; border-image: url(:/images/btn2.png); border-width: 5;} QPushButton:pressed{border-image: url(:/images/btn3.png); border-width: 5;}");
    connect(btnHide, SIGNAL(clicked()), SLOT(hide()));
    list2.append(btnHide);
    hl4->addWidget(btnHide);

    m_listBtns.append(list2);
    m_mainLayout->addLayout(hl4);
    m_btnFrm = new QWidget();
    m_btnFrm->setLayout(m_mainLayout);
    m_btnFrm->setStyleSheet("background:#D1D4DA;");
    mvl->addWidget(m_btnFrm);
    setLayout(mvl);
    connect(&m_pinyinInput, SIGNAL(pinyinTextChanged(QString)), SLOT(setText(QString)));
    m_hanziPageCnt = 0;
    m_pyFrm->setFixedHeight(40);
    setFixedHeight(m_pyFrm->height() + m_labPyText->height() + m_btnFrm->height());
}

KeyboardForm::~KeyboardForm()
{
    delete m_mainLayout;
}

void KeyboardForm::slotBtnClicked()
{
    QString text = ((QPushButton*)sender())->text();
    if (m_inputMode == ImNum || m_isShiftInput)
        sendKeyToFocusItem(((QPushButton*)sender())->text());
    else
    {
        QString str = m_txtPinYin->text() + text;
        m_txtPinYin->setText(str);
        m_pinyinInput.Matching(str, m_inputMode == ImEn);
        if (m_pinyinInput.HanziModel.size())
        {
            m_hanziPageCnt = m_pinyinInput.HanziModel.size() / 8 + int(m_pinyinInput.HanziModel.size() % 8 > 0);
            m_curHanziPage = 1;
        }
        else
            m_hanziPageCnt = 0;
        displayHanzi();
    }
}

void KeyboardForm::btnClicked()
{
    sendKeyToFocusItem(((QPushButton*)sender())->text());
}

void KeyboardForm::slotHaiziBtnClicked()
{
    sendKeyToFocusItem(((QPushButton*)sender())->text());
    m_txtPinYin->clear();
    m_labPyText->clear();
    m_labPyText->hide();
    m_hanziPageCnt = 0;
    displayHanzi();
}

void KeyboardForm::setText(QString str)
{
    m_labPyText->setVisible(str.size());
    m_labPyText->setText(str);
}

void KeyboardForm::shiftClicked()
{
    m_isShiftInput = !m_isShiftInput;
    m_inputMode = (InputMode)m_btnChange->property("Mode").toInt();
    m_btnSpace->setText(m_inputMode == ImCn ? "拼音" : "英文");
    m_btnSymbol->setText(".123");
    m_btnShift->setStyleSheet(tr("QPushButton{color:#FFFFFF; border-image: url(:/images/btn%1.png); border-width: 5;} QPushButton:pressed{border-image: url(:/images/btn3.png); border-width: 5;}").arg(m_isShiftInput?3:2));
    m_hanziPageCnt = 0;
    m_txtPinYin->clear();
    displayHanzi();

    for (int i = 0, idx = 0; i < m_listCharsBtns.size(); i++)
        foreach (QPushButton* btn, m_listCharsBtns[i])
            btn->setText(QString(QLatin1Char(m_isShiftInput ? kbLetter[idx] - 32 : kbLetter[idx]))), idx++;
}

void KeyboardForm::changeInputMode()
{
    m_btnChange->setProperty("Mode", m_inputMode = m_btnChange->property("Mode").toInt() == ImEn ? ImCn : ImEn);
    //m_pyFrm->setVisible(true);
    m_hanziPageCnt = 0;
    m_txtPinYin->clear();
    displayHanzi();
    m_btnSpace->setText(m_inputMode == ImCn ? "拼音" : "英文");
    m_isShiftInput = false;
    m_btnShift->setStyleSheet("QPushButton{color:#FFFFFF; border-image: url(:/images/btn2.png); border-width: 5;} QPushButton:pressed{border-image: url(:/images/btn3.png); border-width: 5;}");
    for (int i = 0, idx = 0; i < m_listCharsBtns.size(); i++)
        foreach (QPushButton* btn, m_listCharsBtns[i])
            btn->setText(QString(QLatin1Char(kbLetter[idx]))), idx++;
}

void KeyboardForm::changeSymbol()
{
    if  (m_btnSymbol->text() == ".123") {
        m_btnSymbol->setText("返回");
        m_hanziPageCnt = 0;
        m_txtPinYin->clear();
        //m_pyFrm->hide();
        m_isShiftInput = false;
        m_btnShift->setStyleSheet("QPushButton{color:#FFFFFF; border-image: url(:/images/btn2.png); border-width: 5;} QPushButton:pressed{border-image: url(:/images/btn3.png); border-width: 5;}");
        displayHanzi();
        if (m_inputMode == ImCn)
            m_listBtns.removeAt(0);
        m_inputMode = ImNum;
        m_btnSpace->setText("数字");
        for (int i = 0, idx = 0; i < m_listCharsBtns.size(); i++)
            foreach (QPushButton* btn, m_listCharsBtns[i])
                btn->setText(QString(QLatin1Char(kbSymbol[idx++])));
    }
    else {
        m_btnSymbol->setText(".123");
        m_inputMode = (InputMode)m_btnChange->property("Mode").toInt();
        m_btnSpace->setText(m_inputMode == ImCn ? "拼音" : "英文");
        for (int i = 0, idx = 0; i < m_listCharsBtns.size(); i++)
            foreach (QPushButton* btn, m_listCharsBtns[i])
                btn->setText(QString(QLatin1Char(kbLetter[idx++])));
    }
}

void KeyboardForm::space()
{
    sendKeyToFocusItem(" ");
}

void KeyboardForm::enter()
{
    if (m_txtPinYin->text().size())
    {
        sendKeyToFocusItem(m_txtPinYin->text());
        m_txtPinYin->clear();
        m_labPyText->clear();
        m_labPyText->hide();
    }
    else
        sendKeyToFocusItem("\n");
}

void KeyboardForm::backSpace()
{
    if (m_inputMode == ImNum || m_isShiftInput)
        sendKeyToFocusItem("\x7F");
    else
    {
        QString text = m_txtPinYin->text();
        if (text.size())
        {
            text.remove(text.size()-1, 1);
            m_txtPinYin->setText(text);
            m_pinyinInput.Matching(text, m_inputMode == ImEn);
            if (m_pinyinInput.HanziModel.size())
            {
                m_hanziPageCnt = m_pinyinInput.HanziModel.size() / 8 + int(m_pinyinInput.HanziModel.size() % 8 > 0);
                m_curHanziPage = 1;
            }
            else
                m_hanziPageCnt = 0;
            displayHanzi();
        }
        else
        {
            m_txtPinYin->clear();
            m_labPyText->clear();
            m_labPyText->hide();
            sendKeyToFocusItem("\x7F");
        }
    }
}

void KeyboardForm::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        m_isMousePress = true;
        m_movePoint = e->pos();
    }
}

void KeyboardForm::mouseMoveEvent(QMouseEvent *e)
{
    if(m_isMousePress)
    {
        QPoint move_pos = e->globalPos();
        this->move(move_pos - m_movePoint);
    }
}

void KeyboardForm::mouseReleaseEvent(QMouseEvent *e)
{
    m_isMousePress = false;
}

void KeyboardForm::displayHanzi()
{
    if (m_hanziPageCnt <= 0)
    {
        m_listHanzi[0]->setEnabled(false);
        m_listHanzi[9]->setEnabled(false);
        for (int i = 0; i < 8; i++)
        {
            m_listHanzi[i+1]->setText("");
            m_listHanzi[i+1]->setEnabled(false);
        }
    }
    else if (m_hanziPageCnt == 1)
    {
        m_listHanzi[0]->setEnabled(false);
        m_listHanzi[9]->setEnabled(false);
        int len = m_pinyinInput.HanziModel.size();
        for (int i = 0; i < len; i++)
        {
            m_listHanzi[i+1]->setText(m_pinyinInput.HanziModel[i]);
            m_listHanzi[i+1]->setEnabled(true);
        }
        for (int i = len; i < 8; i++)
        {
            m_listHanzi[i+1]->setText("");
            m_listHanzi[i+1]->setEnabled(false);
        }
    }
    else if (m_curHanziPage == 1)
    {
        m_listHanzi[0]->setEnabled(false);
        m_listHanzi[9]->setEnabled(true);
        for (int i = 0; i < 8; i++)
        {
            m_listHanzi[i+1]->hide();
            m_listHanzi[i+1]->setText(m_pinyinInput.HanziModel[i]);
            m_listHanzi[i+1]->setEnabled(true);
            m_listHanzi[i+1]->show();
        }
    }
    else if (m_curHanziPage == m_hanziPageCnt)
    {
        m_listHanzi[0]->setEnabled(true);
        m_listHanzi[9]->setEnabled(false);
        int len = m_pinyinInput.HanziModel.size() % 8;
        int idx = (m_hanziPageCnt - 1) * 8;
        for (int i = 0; i < len; i++)
        {
            m_listHanzi[i+1]->setText(m_pinyinInput.HanziModel[idx + i]);
            m_listHanzi[i+1]->setEnabled(true);
        }
        for (int i = len; i < 8; i++)
        {
            m_listHanzi[i+1]->setText("");
            m_listHanzi[i+1]->setEnabled(false);
        }
    }
    else
    {
        m_listHanzi[0]->setEnabled(true);
        m_listHanzi[9]->setEnabled(true);
        int idx = (m_curHanziPage - 1) * 8;
        for (int i = 0; i < 8; i++)
        {
            m_listHanzi[i+1]->setText(m_pinyinInput.HanziModel[idx + i]);
            m_listHanzi[i+1]->setEnabled(true);
        }
    }
}

void KeyboardForm::prevPage()
{
    m_curHanziPage--;
    displayHanzi();
}

void KeyboardForm::nextPage()
{
    m_curHanziPage++;
    displayHanzi();
}
