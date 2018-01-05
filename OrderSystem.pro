#-------------------------------------------------
#
# Project created by QtCreator 2018-01-01T07:47:42
#
#-------------------------------------------------

QT       += core gui
LIBS += -I/usr/include/mysql
LIBS += -L/usr/lib/mysql
LIBS += -lmysqlclient
LIBS += -lpthread

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OrderSystem
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    function.cpp \
    login.cpp \
    register.cpp \
    count.cpp \
    ok.cpp \
    error.cpp \
    manager.cpp \
    comment.cpp \
    info.cpp \
    mw.cpp \
    mana_info.cpp \
    new_cooker.cpp \
    new_dish.cpp \
    new_server.cpp \
    check_order.cpp \
    new_desk.cpp \
    check_order_detail.cpp \
    waiting.cpp \
    exit.cpp

HEADERS += \
    function.h \
    linker.h \
    login.h \
    register.h \
    count.h \
    ok.h \
    error.h \
    manager.h \
    comment.h \
    info.h \
    mw.h \
    mana_info.h \
    new_cooker.h \
    new_dish.h \
    new_server.h \
    check_order.h \
    new_desk.h \
    check_order_detail.h \
    waiting.h \
    exit.h

FORMS += \
    login.ui \
    register.ui \
    count.ui \
    ok.ui \
    error.ui \
    manager.ui \
    comment.ui \
    info.ui \
    mw.ui \
    mana_info.ui \
    new_cooker.ui \
    new_dish.ui \
    new_server.ui \
    check_order.ui \
    new_desk.ui \
    check_order_detail.ui \
    waiting.ui \
    exit.ui
