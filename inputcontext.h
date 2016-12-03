#ifndef MOCKUPINPUTCONTEXT_H
#define MOCKUPINPUTCONTEXT_H
#include <QRectF>
#include <qpa/qplatforminputcontext.h>
#include "keyeventdispatcher.h"
#include "KeyboardForm.h"

class InputContextPrivate;
class InputContext : public QPlatformInputContext
{
    Q_OBJECT
public:
    InputContext();
    ~InputContext();
    //retur true if plugin is enabled
    bool isValid() const;

    //this value will be available in QGuiApplication::inputMethod()->keyboardRectangle()
    QRectF keyboardRect() const;

    //this value will be available in QGuiApplication::inputMethod()->isVisible()
    bool isInputPanelVisible() const;

    //editor pointer
    void setFocusObject(QObject *object);
    static InputContext* Instance();
public slots:
    void hideInputPanel();
    //show and hide invoked by Qt when editor gets focus
    void showInputPanel();
public:
    InputContextPrivate *d;
};

class InputContextPrivate
{
public:
    InputContextPrivate();
    ~InputContextPrivate();
    KeyboardForm *KeyBoard;
    KeyEventDispatcher keyEventDispatcher;
};
#endif // MOCKUPINPUTCONTEXT_H
