QT += widgets serialport
requires(qtConfig(combobox))

TARGET = terminal
TEMPLATE = app

SOURCES += \
    conf.c \
    main.cpp \
    mainwindow.cpp \
    queue.c \
    settingsdialog.cpp \
    console.cpp \
    uartprocthread.cpp \
    uartrecvthread.cpp

HEADERS += \
    conf.h \
    mainwindow.h \
    queue.h \
    settingsdialog.h \
    console.h \
    uartprocthread.h \
    uartrecvthread.h

FORMS += \
    mainwindow.ui \
    settingsdialog.ui

RESOURCES += \
    terminal.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/serialport/terminal
INSTALLS += target
