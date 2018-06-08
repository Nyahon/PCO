QT       += core websockets
QT       -= gui

TARGET = fileserver
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    fileserver.cpp \
    filereader.cpp \
    requesthandler.cpp \
    responsedispatcherthread.cpp \
    requestdispatcherthread.cpp \
    requestworker.cpp \
    threadpool.cpp \
    tpworker.cpp

HEADERS += \
    fileserver.h \
    filereader.h \
    response.h \
    abstractbuffer.h \
    request.h \
    requesthandler.h \
    responsedispatcherthread.h \
    bufferimpl.h \
    requestdispatcherthread.h \
    requestworker.h \
    threadpool.h \
    runnable.h \
    runnableimpl.h \
    tpworker.h

EXAMPLE_FILES += fileclient.html
