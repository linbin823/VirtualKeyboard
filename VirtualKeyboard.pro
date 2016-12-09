#-------------------------------------------------
#
# Project created by QtCreator 2013-04-04T23:11:38
#
#-------------------------------------------------

QT       += gui-private widgets xml sql multimedia

CONFIG += plugin

TARGET = VirtualKeyboard
TEMPLATE = lib

INCLUDEPATH += $$PWD/pinyin


DEFINES += VIRTUALKEYBOARD_LIBRARY

win32 {
    DESTDIR = C:/CL/Qt.reference.2016.VirtualKeyboard/build/platforminputcontexts
    OBJECTS_DIR = $$DESTDIR/obj
    MOC_DIR = $$DESTDIR/moc
}

SOURCES += \
    KeyboardForm.cpp \
    pinyininputmethod.cpp \
    pinyin/dictbuilder.cpp \
    pinyin/dictlist.cpp \
    pinyin/dicttrie.cpp \
    pinyin/lpicache.cpp \
    pinyin/matrixsearch.cpp \
    pinyin/mystdlib.cpp \
    pinyin/ngram.cpp \
    pinyin/pinyinime.cpp \
    pinyin/searchutility.cpp \
    pinyin/spellingtable.cpp \
    pinyin/spellingtrie.cpp \
    pinyin/splparser.cpp \
    pinyin/sync.cpp \
    pinyin/userdict.cpp \
    pinyin/utf16char.cpp \
    pinyin/utf16reader.cpp \
    inputcontext.cpp \
    keyeventdispatcher.cpp \
    platforminputcontextplugin.cpp

HEADERS +=\
    KeyboardForm.h \
    pinyininputmethod.h \
    pinyin/atomdictbase.h \
    pinyin/dictbuilder.h \
    pinyin/dictdef.h \
    pinyin/dictlist.h \
    pinyin/dicttrie.h \
    pinyin/lpicache.h \
    pinyin/matrixsearch.h \
    pinyin/mystdlib.h \
    pinyin/ngram.h \
    pinyin/pinyinime.h \
    pinyin/searchutility.h \
    pinyin/spellingtable.h \
    pinyin/spellingtrie.h \
    pinyin/splparser.h \
    pinyin/sync.h \
    pinyin/userdict.h \
    pinyin/utf16char.h \
    pinyin/utf16reader.h \
    inputcontext.h \
    platforminputcontextplugin.h \
    keyeventdispatcher.h \
    virtualkeyboard_global.h

RESOURCES += \
    res.qrc

