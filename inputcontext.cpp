#include <QtDebug>
#include <QEvent>
#include <QApplication>
#include <QDesktopWidget>
#include <QtWidgets/QMainWindow>
#include <QInputDialog>
#include "inputcontext.h"
#include "pinyininputmethod.h"

#define WINDOW_HEIGHT QApplication::desktop()->height()
static InputContext *instance = NULL;

InputContextPrivate::InputContextPrivate() : KeyBoard(0)
{
}

InputContextPrivate::~InputContextPrivate()
{
    if (KeyBoard)
        delete KeyBoard;
}

InputContext* InputContext::Instance()
{
    return instance;
}

InputContext::InputContext() :
    QPlatformInputContext()
{
    d = new InputContextPrivate();
    instance = this;
}

InputContext::~InputContext()
{
}

bool InputContext::isValid() const
{
    return true;
}

QRectF InputContext::keyboardRect() const
{
    return (d->KeyBoard) ? d->KeyBoard->rect() : QRectF();
}

void InputContext::showInputPanel()
{
    if (!d->KeyBoard) {
        d->KeyBoard = new KeyboardForm();
        connect(d->KeyBoard, SIGNAL(sendKeyToFocusItem(QString)), &d->keyEventDispatcher, SLOT(sendKeyToFocusItem(QString)));
    }
    d->KeyBoard->show();
    d->KeyBoard->move(d->KeyBoard->x(), WINDOW_HEIGHT - d->KeyBoard->height());

    QPlatformInputContext::showInputPanel();
}

void InputContext::hideInputPanel()
{
    if (d->KeyBoard)
        d->KeyBoard->hide();
    QPlatformInputContext::hideInputPanel();
}

bool InputContext::isInputPanelVisible() const
{
    return (d->KeyBoard) ? d->KeyBoard->isVisible() : false;
}


void InputContext::setFocusObject(QObject *object)
{
    d->keyEventDispatcher.setFocusItem(object);
}
