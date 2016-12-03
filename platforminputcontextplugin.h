#ifndef MOCKUPPLATFORMINPUTCONTEXTPLUGIN_H
#define MOCKUPPLATFORMINPUTCONTEXTPLUGIN_H

#include "virtualkeyboard_global.h"
#include <qpa/qplatforminputcontextplugin_p.h>

class VIRTUALKEYBOARDSHARED_EXPORT PlatformInputContextPlugin: public QPlatformInputContextPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QPlatformInputContextFactoryInterface" FILE "Qt5Input.json")

public:
    QPlatformInputContext *create(const QString&, const QStringList&);
};

#endif // MOCKUPPLATFORMINPUTCONTEXTPLUGIN_H
