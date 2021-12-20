QT += core gui
QT += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11

INCLUDEPATH += "C:/npcap-sdk-1.06/Include"
INCLUDEPATH += "C:/Program Files (x86)/Windows Kits/10/Include/10.0.19041.0/um"
LIBS += "-LC:/npcap-sdk-1.06/Lib/x64" -lwpcap -lws2_32
LIBS += iphlpapi.lib

SOURCES += \
    CaptureThreads.cpp \
    ConfigWin.cpp \
    DevicesList.cpp \
    MainWin.cpp \
    PanelInfoLineSeries.cpp \
    RoutingTable.cpp \
    Strings.cpp \
    UnknownUtils.cpp \
    ViewAgents.cpp \
    main.cpp

HEADERS += \
    CaptureThreads.h \
    CaptureThreads_FCTS.h \
    DetectionEngine.h \
    EventsView.h \
    Headers.h \
    MainWin.h \
    ProcAndFuncs.h \
    QTableViewModel.h \
    RoutingTableModel.h \
    Strings.h \
    UnknownUtils.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
