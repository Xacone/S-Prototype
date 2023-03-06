#include "MainWin.h"
#include "InitStats.h"


//!\ A factoriser dans fichiers statistiques utils !!!! pas d'indépendance identique
//! //!\ A factoriser dans fichiers statistiques utils !!!! pas d'indépendance identique
//! //!\ A factoriser dans fichiers statistiques utils !!!! pas d'indépendance identique
//! //!\ A factoriser dans fichiers statistiques utils !!!! pas d'indépendance identique
//!\ A factoriser dans fichiers statistiques utils !!!! pas d'indépendance identique
//!\ A factoriser dans fichiers statistiques utils !!!! pas d'indépendance identique
//!\ A factoriser dans fichiers statistiques utils !!!! pas d'indépendance identique
//!\ A factoriser dans fichiers statistiques utils !!!! pas d'indépendance identique
//! //!\ A factoriser dans fichiers statistiques utils !!!! pas d'indépendance identique
//!\ A factoriser dans fichiers statistiques utils !!!! pas d'indépendance identique

QChartView* _LINE_CHART_(QString title) //!\ A factoriser dans fichiers statistiques utils !!!! pas d'indépendance identique
{
    QChartView* CHRTV = new QChartView();
    CHRTV->setRenderHint(QPainter::Antialiasing);

    QChart *chart = CHRTV->chart();
        //chart->setAnimationOptions(QChart::AllAnimations);
        chart->setTitle(title);
        chart->legend()->setVisible(true);

        CHRTV->setStyleSheet("background-color: #2c3e50;");

    return CHRTV;
}

QChartView* _PIE_CHART_(QString title, QPieSeries* qps) //!\ A factoriser dans fichiers statistiques utils !!!! pas d'indépendance identique
{
    QChartView* CHRTV = new QChartView();
    CHRTV->setRenderHint(QPainter::Antialiasing);

    QChart *chart = CHRTV->chart();
        //chart->setAnimationOptions(QChart::AllAnimations);
        chart->setTitle(title);
        chart->legend()->setVisible(true);

        CHRTV->setStyleSheet("background-color: #2c3e50; color: white;");
        CHRTV->chart()->setBackgroundBrush(QBrush(QColor("#2c3e50")));
        CHRTV->chart()->setTitleBrush(QBrush(QColor("white")));
        CHRTV->chart()->setPlotAreaBackgroundBrush(QBrush(QColor("white")));

        qps->setHoleSize(0.25);

        /*
            QPieSlice *test_s = new QPieSlice();
            test_s->setValue(50);
            test_s->setColor(QColor("#f1c40f"));

            QPieSlice *test_s2 = new QPieSlice();
            test_s2->setValue(50);
            test_s2->setColor(QColor("#8e44ad"));

        qps->append(test_s);
        qps->append(test_s2);

        */

        chart->addSeries(qps);

    return CHRTV;
}

QVBoxLayout* init_label(QLabel* l, QString title)
{
    l->setText("0");
    QLabel* ttl_title = new QLabel(title);
    QVBoxLayout* qvb_lb = new QVBoxLayout();

    QFont f = l->font();
    QFont ft = ttl_title->font();
    ttl_title->setStyleSheet("color: white;");

    f.setPointSize(85);
    f.setBold(true);
    l->setFont(f);
    l->setStyleSheet("color: white;");

    ft.setPointSize(17);
    ft.setBold(true);
    ttl_title->setFont(ft);

    qvb_lb->addWidget(ttl_title);
    qvb_lb->addWidget(l);

    return qvb_lb;
}


// DASHBOARD / STATS
void Win::_init_stats_panel()
{

    // LABELS
    _events_nbr = new QLabel();
    _agents_nbr = new QLabel();
    _critical_nbr = new QLabel();
    _magnitude_ = new QLabel();

    // PIE_SLICES
    L3_PS = new QPieSeries;
    L4_PS = new QPieSeries;
    L5_PS = new QPieSeries;
    QPieSeries *t1 = new QPieSeries;
    QPieSeries *t2 = new QPieSeries;

    TabWidget *TB = new TabWidget;

    panel_stats = new QWidget();
        panel_stats->setStyleSheet("background-color: #2c3e50;");
    panel_stats_gl = new QGridLayout();

    panel_stats_gl->addLayout(init_label(_events_nbr, "Nombre\nd'événements"), 0, 0);
    panel_stats_gl->addLayout(init_label(_agents_nbr, "Agents\nconnectés"), 0, 1);
    panel_stats_gl->addLayout(init_label(_critical_nbr, "Alertes\ncritiques"), 0, 2);
    panel_stats_gl->addLayout(init_label(_magnitude_, "Magnitude\nmoyenne"), 0, 3);

    _events_nbr->setText("0");
    _events_nbr->setStyleSheet("color: #ecf0f1;");
    _agents_nbr->setText("0");
    _agents_nbr->setStyleSheet("color: #ecf0f1;");
    _critical_nbr->setText("0");
    _critical_nbr->setStyleSheet("color: #ecf0f1;");
    _magnitude_->setText("0");
    _magnitude_->setStyleSheet("color: #ecf0f1;");

    panel_stats->setLayout(panel_stats_gl);

        QChartView *L3_PROTOC_STATS = _PIE_CHART_("<b>Couche Réseau</b>", L3_PS);
        QChartView *L4_PROTOC_STATS = _PIE_CHART_("<b>Couche Transport</b>", L4_PS);
        QChartView *L5_PROTOC_STATS = _PIE_CHART_("<b>Couche Applicative</b>", L5_PS);

        panel_stats_gl->addWidget(L3_PROTOC_STATS, 1, 0);
        panel_stats_gl->addWidget(L4_PROTOC_STATS, 1, 1);
        panel_stats_gl->addWidget(L5_PROTOC_STATS, 1, 2);

        //ChartView *tst2 = _PIE_CHART_("Couche 4", t2);
        //panel_stats_gl->addWidget(tst2, 1, 3);

        TB->addTab(panel_stats, "Dashboard");
        TB->addTab(info_text, "Logs");

    central_tab->addTab(TB, QIcon("C:/Sproto_CPP_v3/Icons/pie_stats.png"), "Stats");

}
