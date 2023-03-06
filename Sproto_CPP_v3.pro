QT += core gui qml quick quickcontrols2 widgets location webenginewidgets webengine gui positioning network charts sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11

INCLUDEPATH += "C:/Sproto_V3_UTILS/npcap-sdk-1.13/Include"
INCLUDEPATH += "C:/Program Files (x86)/Windows Kits/10/Include/10.0.19041.0/um"
LIBS += "-LC:/Sproto_V3_UTILS/npcap-sdk-1.13/Lib/x64" -lwpcap -lws2_32
LIBS += iphlpapi.lib

SOURCES += \
    CaptureThreads.cpp \
    ConfigWin.cpp \
    DevicesList.cpp \
    InitMap.cpp \
    InitStats.cpp \
    InitWlan.cpp \
    MainWin.cpp \
    PanelInfoLineSeries.cpp \
    RoutingTable.cpp \
    SprotoServers.cpp \
    Strings.cpp \
    TcpTable.cpp \
    UnknownUtils.cpp \
    ViewAgents.cpp \
    main.cpp

HEADERS += \
    CSVParsingUtils.h \
    CaptureThreads.h \
    CaptureThreads_FCTS.h \
    CsvUtils.h \
    DatabaseUtils.h \
    DetectionEngine.h \
    EventsView.h \
    Headers.h \
    InitStats.h \
    MainWin.h \
    ProcAndFuncs.h \
    QTableViewModel.h \
    RoutingTableModel.h \
    SprotoServers.h \
    Strings.h \
    TcpTableModel.h \
    UnknownUtils.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Icons/alert_1.png \
    Icons/analyze_1.png \
    Icons/bluetooth_1.png \
    Icons/brief_table.png \
    Icons/char1.ico \
    Icons/chart_1.ico \
    Icons/clear_1.png \
    Icons/config_1.png \
    Icons/data_1.png \
    Icons/devi.png \
    Icons/devices_1.ico \
    Icons/dns.ico \
    Icons/exit_1.png \
    Icons/focus_1.png \
    Icons/focus_2.png \
    Icons/font_size_1.png \
    Icons/full_screen_1.png \
    Icons/honeypot_1.png \
    Icons/http_chart.png \
    Icons/icons8_pie_chart_96px.png \
    Icons/icons8_server.ico \
    Icons/icons8_toggle_full_screen_64px.png \
    Icons/ip_routing.ico \
    Icons/json.ico \
    Icons/json.png \
    Icons/log_1.png \
    Icons/loupe.png \
    Icons/netcard_1.png \
    Icons/open_file.png \
    Icons/pause_1.png \
    Icons/pdf.ico \
    Icons/pdf.png \
    Icons/phishing_1.png \
    Icons/piechart.ico \
    Icons/piechart2.png \
    Icons/play_1.png \
    Icons/radar_1.png \
    Icons/rj45_1.png \
    Icons/save.png \
    Icons/save_as.png \
    Icons/search.ico \
    Icons/send.ico \
    Icons/send.png \
    Icons/servers_icn.ico \
    Icons/some_list.ico \
    Icons/ssh.png \
    Icons/terminal_1.png \
    Icons/thief_1.png \
    Icons/thief_escape.png \
    Icons/vpn_1.png \
    Icons/wifi_1.png \
    Icons/wolf_1.png \
    Icons/xml.ico \
    Icons/xml.png \
    Icons/zoom_in.png \
    Icons/zoom_out.png \
    Images/CONSOLE.png \
    Images/DNS.png \
    Images/HACKER.png \
    Images/LAPTOP.png \
    Images/NIC.png \
    Images/ROUTER.png \
    Images/SERVER.png \
    Images/SWITCH.png \
    Images/VPN 2.png \
    Images/VPN.png \
    Images/WEB.png \
    Images/splash.png \
    Images/yazed2.jpg \
    Map/s1.js \
    Map/s2.js \
    Map/s3.js \
    Map/s4.js \
    Map/test.html
