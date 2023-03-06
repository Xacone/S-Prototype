#include "MainWin.h"
#include <QQmlApplicationEngine>
#include <QtWebEngine/QtWebEngine>
#include <QWebEngineView>
#include <QWebEngineSettings>

void Win::_init_map()
{
    /* -------------------- DB -------------------- */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Sproto_V3_UTILS/sproto_test_db.db");
    bool opened = db.open();
    qDebug() << "DB OPENED : " << opened << "\n";

    //ipgeoloc = new IpGeoLoc(db);
    //ipgeoloc->Query("197.247.128.161");
    /* -------------------- DB -------------------- */



    panel_map->setLayout(panel_map_vl);
    QWEV_MAP1 = new QWebEngineView(); // To optimize ??
    panel_map_vl->addWidget(QWEV_MAP1);
    QWEV_MAP1->load(QUrl("file:///C:/Sproto_V3_UTILS/SPROTO_MAP_BAC_A_SABLE/Untitled-2.html"));
    QObject::connect(QWEV_MAP1->page(), SIGNAL(loadFinished(bool)), this, SLOT(init_js_map1(bool)));
}

void Win::init_js_map1(bool b)
{
    Q_UNUSED(b)
    QWEV_MAP1->page()->runJavaScript("setOrigin();");
}

void Win::refresh_js_map1(QList<QStringList>* qlist)
{
    for(QStringList data : *qlist)
    {
        if(data.at(2) !=  "0.0.0.0" && data.at(2) != "127.0.0.1") { ipgeoloc->Query(data.at(2)); }
    }
}

