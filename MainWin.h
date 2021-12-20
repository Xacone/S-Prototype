#ifndef MAINWIN_H
#define MAINWIN_H

#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include "QTableViewModel.h"
#include "RoutingTableModel.h"
#include <QMenuBar>
#include <QToolBar>
#include <QLineEdit>
#include <QIcon>
#include <QTableView>
#include <QFontDialog>
#include <QToolBar>
#include <QSplitter>
#include "pcap.h"
#include <QAction>
#include <QCheckBox>
#include <QProcess>
#include <QTextEdit>
#include <QGridLayout>
#include <Strings.h>
#include <QListWidget>
#include <QStatusBar>
#include <QTableWidget>
#include <cstdlib>
#include <QThread>
#include <QVBoxLayout>
#include <QChart>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QLabel>
#include <QTabWidget>
#include "EventsView.h"
#include <QGroupBox>
#include <QLineSeries>
#include <qthread.h>
#include <QBarSeries>
#include <QtCharts>
#include <QPushButton>
#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include "CaptureThreads.h"
#include "CaptureThreads_FCTS.h"
#include "ProcAndFuncs.h"

void only_one_win(QWidget*);
QList<QStringList>* routing_list();

class S_A_T : public QThread
{
    Q_OBJECT
    qreal pack_size = 0;
    qreal pack_nbr = 0;
    QTreeWidgetItem *dev;
public:
    S_A_T(QTreeWidgetItem* qtwi) : dev(qtwi) {};

    inline void run() override {
      while(true)
        {
            this->thread()->msleep(1000);
            if(dev->checkState(0))
            {
                emit throw_ps(pack_size/1000);
                emit throw_pn(pack_nbr);
                pack_size = 0;
                pack_nbr = 0;
            }
        }
    }

public slots:
    inline void append_to_ps(qreal v) { pack_size += v; }
    inline void append_to_pn() { pack_nbr += 1; }

signals:
    void throw_ps(qreal);
    void throw_pn(qreal);
};

class CustomGView : public QGraphicsView
{
private:
    QGraphicsScene *s;
public:
    CustomGView(QGraphicsScene* scene) : QGraphicsView(scene), s(scene) {}
};


class CustomConsole : public QTextEdit
{

    Q_OBJECT
private:
    QByteArray Buffer;
    QString StringBuffer;
    QString starter = "sproto>";
    bool user_moved_cursor = false;
    QPalette pal;
    QList<QString> PAST;
    Process_Handler PH;

public:

    CustomConsole() : QTextEdit() {
        PH.setStarter(starter);
        this->setText(Welcoming2());
        this->append(starter);
        this->setCursorWidth(10);
        pal.setColor(QPalette::Base, QColor("#2c3e50"));
        pal.setColor(QPalette::Text, QColor("#ffffff"));
        this->setPalette(pal);
        this->moveCursor(QTextCursor::End);
        connect(&PH, SIGNAL(SendOutput(QString)), this, SLOT(Output(QString)));
        connect(&PH, SIGNAL(started()), this, SLOT(ProcessStarted()));
        connect(&PH, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(ProcessEnded(int, QProcess::ExitStatus)));
    }

    QByteArray getBuffer() { return Buffer; }
    void setBuffer(QByteArray in) { Buffer = in; }

    QString getStarter() { return starter; }
    void setStarter(QString s) { starter = s; }

    void keyPressEvent(QKeyEvent *e) override
    {
        if(e->key() == Qt::Key_Return)
        {
                if(StringBuffer != "") { PAST.append(StringBuffer); }
                if(StringBuffer == "version")
                {
                    this->append(PH.VERSION());
                    this->append(starter);
                } else {
                    if(StringBuffer == "clear") {
                        this->setText("");
                        this->append(starter);
                        this->moveCursor(QTextCursor::End);
                    } else {
                        if(PH.state() == QProcess::Running) {
                            std::cout << "Running" << std::endl;
                            PH.kill();
                        } else {
                            if((StringBuffer.contains("netstat") || StringBuffer.contains("ping") || StringBuffer.contains("tracert") || StringBuffer.contains("arp") || StringBuffer.contains("ipconfig") || StringBuffer.contains("route")) && !(StringBuffer.contains("&") || StringBuffer.contains("|")))
                              {
                                 PH.WIN32_CMDPROCESS(StringBuffer);
                             } else {
                                if(StringBuffer.contains("history"))
                                {
                                    for(auto i : PAST) { this->append(i); }
                                    this->append(starter);
                                } else { // LE else
                                    this->append(starter);
                                }
                            }
                            this->moveCursor(QTextCursor::End);
                        }
                    }
                }

                StringBuffer = "";

        } else {
            switch(e->key())
            {
                case Qt::Key_Backspace:
                if((QChar)this->toPlainText().at(textCursor().position()-1) != ">")
                {
                     textCursor().deletePreviousChar();
                     StringBuffer.chop(1);
                }
                break;

                case Qt::Key_Left:
                    if((QChar)this->toPlainText().at(textCursor().position()-1) != ">")
                    {
                        this->moveCursor(QTextCursor::PreviousCharacter);
                        user_moved_cursor = true;
                    }
                break;

                case Qt::Key_Right:
                    this->moveCursor(QTextCursor::NextCharacter);
                    user_moved_cursor = true;
                break;

                default:
                    if(PH.state() != QProcess::Running) {
                        this->textCursor().insertText(QString(e->key()).toLower());
                        StringBuffer += QString(e->key()).toLower();
                    }
                break;
            }
        }
    }


    void mouseDoubleClickEvent(QMouseEvent *e) override { Q_UNUSED(e) }
    void mouseMoveEvent(QMouseEvent *e) override { Q_UNUSED(e) }
    void mousePressEvent(QMouseEvent *e) override { Q_UNUSED(e) }
    void mouseReleaseEvent(QMouseEvent *e) override { Q_UNUSED(e) }

public slots:
    void Output(QString in){
        this->setText(this->toPlainText()+in);
        this->moveCursor(QTextCursor::End);
    }

    void ProcessEnded(int dead, QProcess::ExitStatus dead2)
    {
        Q_UNUSED(dead)
        Q_UNUSED(dead2)
        this->append(starter);
    }

    void ProcessStarted() {}

};


class Win : public QMainWindow
{
    Q_OBJECT;

    //JsonWax jwax;

protected:

    /* ----------- GLOBAL USE ----------- */
    QList<QStringList> *_ROUTING_TABLE_RETRIEVED_ = routing_list();
    /* ---------------------------------- */

    int index_on_pcktsize_chart = 0;
    int index_on_tcp_chart = 0;
    int index_on_udp_chart = 0;
    int greatest_value_on_info_chart = 0;
    int index_on_ps_chart = 0;
    int index_on_pn_chart = 0;
    int index_of_method_pie = 0;

    QPointF single_point;
    QList<QPointF> ps_points; // Packet Size Points pour info chart
    QList<QPointF> ps_points2;

    // Device capture & Threads
    QMutex *mutx;
    pcap_if_t* all_devs;


    // General
    QPalette* _pal_;
    QFont *_font_;
    QFont *font_consolas;

    // Head
    QMenu *file;
    QMenu *network_devices;
    QMenu *edit;
    QMenu *tools;
    QMenu *modules;
    QMenu *view;
    QMenu *about;

    /* ----- File ----- */
    QAction *new_;
    QAction *new_focus;
    QAction *open_file;
    QAction *save_file;
    QAction *save_file_as;
    QMenu *open_recent;
    QAction *import_log;
    QAction *babye;

    /* ----- DEVICES ----- */
    QAction *dev_opt;
    QAction *routing_table;
    QAction *arp_table;
    QAction *DNS_servers;
    QAction *net_tcp_table;

    /* ----- CONFIG ----- */
    QAction *config;

    /* ----- STATS ----- */
    // TODO
    // WIN32 GANG LA PIRATERIE N'EST JAMAIS FINIE.

    /* ----- Tools ----- */
    QAction *get_agents_list;
    QAction *http_brief;
    QAction *stp_brief;
    QAction *dot_1q_brief;
    QAction *ftp_brief;
    QAction *https_brief;
    QAction *arp_brief;
    QAction *tcp_brief;

    /* ----- Modules ----- */
    QAction *honeyPot_Management;

    /* ----- View ----- */
    QAction *fullscreen_check;
    QAction *ssh_client_check;
    QAction *packet_capture_check;
    QAction *agent_console_check;
    QAction *brief_table_check;
  //  QAction *font_choose;

    QMenu *tool_bar_position;

    QToolBar *tool_bar;

    /* ----- StatBar ----- */
    QLabel *stat_label;

    // Body

    QWidget *root_widget;
        QGridLayout *root_layout;
            QVBoxLayout *v_layout_1;
                QTabWidget *central_tab;

                    QWidget *_MAIN_panel_console;
                    QHBoxLayout *panel_console_layout;
                        CustomConsole *console;

                    QWidget *panel_info;
                    QVBoxLayout *v_layout_root;
                         QHBoxLayout *v_layout_1_0;
                         QTextEdit *info_text;
                         QListWidget *filtering_history;
                         QTextBrowser *text_browser;

                         QChart *chart_1;
                         QChartView *chart_view_1;
                         QLineSeries* courbe;
                         QValueAxis *x_axis; // n'est plus indispensable
                         QValueAxis *y_axis; // idem

                       QHBoxLayout *h_layout_for_charts;
                         QChart *tcp_chart;
                         QChartView *tcp_chart_view;
                         QLineSeries* tcp_chart_series;

                         QChart *udp_chart;
                         QChartView *udp_chart_view;
                         QLineSeries* udp_chart_series;

                    QWidget *panel_capture;
                        QVBoxLayout *v_layout_1_1;
                        QToolBar *cap_menu_bar;
                        QAction *play_cap;
                        QAction *stop_cap;
                        QAction *clear_cap;
                        QLabel *packet_count;

                        QTextEdit *cap_info;
                        QTableView *cap_table;
                            Model_CoworkerThread *MCT;
                            Packets_TableModel *temp;

                        QAction *cap_zoom_in;
                        QAction *cap_zoom_out;

                        QLineEdit *filter_input;

                        QWidget *panel_capture_hbox_widg;
                        QHBoxLayout *panel_capture_hbox;

                            QComboBox *LINE_SPEED;

                            QChart *pckt_per_sec;
                            QChartView *pckt_per_sec_view;
                            QLineSeries *pckt_per_sec_series;

                            QChart *size_per_sec;
                            QChartView *size_per_sec_view;
                            QLineSeries *size_per_sec_series;

                    QWidget *panel_http;

                    QToolBar *http_panel_menu_bar;
                    QLabel *http_req_nbr;
                    QLabel *http_srv_nbr;
                    QLabel *http_nbr;

                        QHBoxLayout *panel_http_layout;
                         QSplitter *http_brief_split;

                                QTreeWidget *http_brief_tree_view;

                                QtCharts::QChartView *chart_v1;
                                    QChart *http_srv_chart;
                                        QPieSeries *http_srv_pie;
                                             qreal label_length_index = 0.01;

                                QVBoxLayout *panel_http_layout2;

                                    QtCharts::QChartView *chart_v2;
                                        QChart *http_method_chart;
                                            QPieSeries *http_method_pie;

                                    QtCharts::QChartView *chart_v3;
                                        QChart *http_code_chart;
                                             QPieSeries *http_code_pie;

                    QWidget *panel_view_agents;
                        QHBoxLayout *panel_view_agents_hbox;
                            QListWidget *list_of_devices;
                                QList<QString> _DEVICES_DESC_LIST_;
                            CustomGView *graphics_view;
                                QGraphicsScene *graphic_scene;


                     /* --------- EVENTS --------- */
                     QWidget *evenements;
                        QVBoxLayout *v_layout_1_2;
                        EventView_TableModel *ETM;

                     QWidget *panel_wifi;
                        QVBoxLayout *v_layout_1_3;

                     QWidget *panel_console;
                        QVBoxLayout *v_layout_1_4;

         QWidget *hide_support;
            QVBoxLayout *v_layout_2;
                QTableWidget *event_view;


     /* -------------- ROUTING TABLE -------------- */
          QWidget *_ROUTING_TABLE_;
             QTableView *_ROUTING_VIEW_;
                Routing_TableModel *_ROUTING_MODEL_;


    /* -------------- FenÃªtre de configuration -------------- */

        QWidget *config_win;
            QHBoxLayout *config_root_layout;

            // Choix
            QTreeWidget *config_tree;
                QTreeWidgetItem *global;
                    QTreeWidgetItem *global_pref; // prÃ©fÃ©rences
                QTreeWidgetItem *capture;
                    QTreeWidgetItem *capture_pref;
                    QTreeWidgetItem *capture_param_int;
                    QTreeWidgetItem *capture_filtrage;
                QTreeWidgetItem *protoc;
                    QTreeWidgetItem *protoc_Ether;
                    QTreeWidgetItem *protoc_IP4;
                    QTreeWidgetItem *protoc_ARP;
                    QTreeWidgetItem *protoc_ICMP;
                    QTreeWidgetItem *protoc_DOT1Q;
                QTreeWidgetItem *agents;
                QTreeWidgetItem *rapports;

            // Options
            QVBoxLayout *options_layout;

                QWidget *opt_global;
                    QWidget *opt_global_pref;

                QWidget *opt_capture;
                QCheckBox *show_packet_len;
                QCheckBox *show_packet_index;
                QCheckBox *show_packet_color;
                QComboBox *cap_mode;
                    QWidget *opt_capture_pref;
                    QWidget *opt_capture_param_int;
                    QWidget *opt_capture_filtrage;

                QWidget *opt_protoc;
                    QWidget *opt_protoc_Ether;
                    QWidget *opt_protoc_IP4;
                    QWidget *opt_protoc_ARP;
                    QWidget *opt_protoc_ICMP;
                    QWidget *opt_protoc_DOT1Q;

                QWidget *opt_agents;

                QWidget *opt_rapports;

    /* -------------- FenÃªtre de configuration d'interfaces -------------- */
    QWidget *int_win;
        QHBoxLayout *int_win_layout;
        QGroupBox *int_win_group_box;
            QVBoxLayout *int_win_group_box_layout;
                QTreeWidget *int_win_tree_view;

     /* -------------- FenÃªtre de donnÃ©es simple -------------- */
        QWidget *text_data_widget;
            QVBoxLayout *text_data_layout;
                QTextEdit *text_data;

public:

        Win();

        void init_conf_win();
        void _init_view_agents();
        void _init_routing_table();
        //void _init_arp_table();
        //void _init_dns_table();
        //void _init_sessions_table();
        void ret_device_list();
        void panel_info_line_series();

        QTextEdit* getCapInfo();


public slots:

        /*
        void JSON_show_packet_size(int);
        void JSON_show_packet_index(int);
        void JSON_show_packet_coloration(int);
        void JSON_select_cap_mode(int);
        */

       // inline void

        inline void set_cap_mode(int v) //
        {
            if(v == 0) { cap_info->setVisible(true); cap_table->setVisible(false);} else if(v == 1) {
                cap_info->setVisible(false); cap_table->setVisible(true);
            }

           // JSON_select_cap_mode(v);
        }

        inline void add_checkbox_to_config(QCheckBox* w, QLayout* l) { l->addWidget(w); w->setChecked(true); }

        inline void widget_associated_to_choice(QTreeWidgetItem* qtwi, int dead)
        {
            int cur_indx = config_tree->currentIndex().row();
            if(config_tree->currentItem()->parent() == NULL)
            {
                if(cur_indx == 0) { opt_global->setVisible(true); } else { opt_global->setVisible(false); }
                if(cur_indx == 1) { opt_capture->setVisible(true); } else { opt_capture->setVisible(false); }
                if(cur_indx == 2) { opt_protoc->setVisible(true); } else { opt_protoc->setVisible(false); }
                if(cur_indx == 3) { opt_agents->setVisible(true); } else { opt_agents->setVisible(false); }
                if(cur_indx == 4) { opt_rapports->setVisible(true); } else { opt_rapports->setVisible(false); }
            }
        }

        inline void assert_point_to_size_per_sec_chart(qreal y)
        {
            if(size_per_sec_series->points().size() >= 60)
            {
                size_per_sec_series->clear();
                size_per_sec_series->append(0,y*8);
                index_on_ps_chart = 1;
            } else {
                size_per_sec_series->append(index_on_ps_chart, y*8);
                index_on_ps_chart += 1;
            }
        }

        inline void assert_point_to_pckt_per_sec_chart(qreal y)
        {
            if(pckt_per_sec_series->points().size() >= 60)
            {
                pckt_per_sec_series->clear();
                pckt_per_sec_series->append(0,y);
                index_on_pn_chart = 1;
            } else {
                pckt_per_sec_series->append(index_on_pn_chart, y);
                index_on_pn_chart += 1;
            }
        }

        void SET_CHARTS_CAPACITY(int val)
        {
            switch(val)
            {
                case 0:
                size_per_sec->axes(Qt::Vertical).first()->setRange(0,1250);
                pckt_per_sec->axes(Qt::Vertical).first()->setRange(0,500);
                break;

                case 1:
                size_per_sec->axes(Qt::Vertical).first()->setRange(0,12500);
                pckt_per_sec->axes(Qt::Vertical).first()->setRange(0,5000);
                break;

                case 2:
                size_per_sec->axes(Qt::Vertical).first()->setRange(0,125000);
                pckt_per_sec->axes(Qt::Vertical).first()->setRange(0,50000);
                break;

                case 3:
                size_per_sec->axes(Qt::Vertical).first()->setRange(0,1250000);
                pckt_per_sec->axes(Qt::Vertical).first()->setRange(0,500000);
                break;

                case 4:
                size_per_sec->axes(Qt::Vertical).first()->setRange(0,12500000);
                pckt_per_sec->axes(Qt::Vertical).first()->setRange(0,500000);
                break;

                default:
                    break;
            }
        }

        void init_slices()
        {
            for(int i = 0 ; i < http_srv_pie->slices().size() ; i++)
            {
                if(http_srv_pie->slices().at(i)->percentage() < 0.025)
                {
                    http_srv_pie->slices().at(i)->setLabelVisible(false);
                } else {
                    http_srv_pie->slices().at(i)->setLabel(http_srv_pie->slices().at(i)->label());
                    http_srv_pie->slices().at(i)->setLabelVisible(true);
                }
            }
        }

        void add_slice_to_http_srv_code(QString http_hdr)
        {
            QList<QPieSlice*> qpslist = http_code_pie->slices();

            int j = 0;
            bool exist = false;
            QRegExp exp("10[0-3]|2[0-2][0-6]|3[01][0-8]|4[0-5][0-9]|5[0-2][0-9]");
            QString code = http_hdr.mid(0,3);

            if(code.contains(exp))
            {
                QPieSlice* target;

                for(int i = 0 ; i < qpslist.length() ; i++)
                {
                    if(qpslist.at(i)->label() == code)
                    {
                        j = i;
                        exist = true;
                        break;
                    } else {
                        continue;
                    }
                }

                if(exist) {
                    target = http_code_pie->slices().at(j);
                    target->setValue(target->value() + 1);
                } else {
                    target = new QPieSlice();
                    target->setLabel(code);
                    target->setValue(1);
                    target->setLabelVisible(true);
                }

                http_code_pie->append(target);
            }
        }

        void add_slice_to_srv_pie(QString ip_addr) // Je t'aime
        {
            QPieSlice *target;
            QList<QPieSlice*> qpslist = http_srv_pie->slices();

            int j = 0;
            bool exist = false;

            for(int i = 0 ; i < qpslist.length() ; i++)
            {
                if(qpslist.at(i)->label() == ip_addr)
                {
                    j = i;
                    exist = true;
                    break;
                } else {
                    continue;
                }
            }

            if(exist)
            {
                target = http_srv_pie->slices().at(j);
                target->setValue(target->value() + 1);
            } else {
                target = new QPieSlice();
                target->setLabel(ip_addr);
                target->setValue(1);
                target->setLabelVisible(true);
                target->setLabelArmLengthFactor(label_length_index);
                //label_length_index += 0.02;
            }

            http_srv_pie->append(target);
        }

        void add_data_to_http_brief_simple(QTreeWidgetItem* qtwi, QString http_hdr)
        {
            QTreeWidgetItem *target;
            QList<QTreeWidgetItem*> exist = http_brief_tree_view->findItems(qtwi->text(0),0,0);
            if(exist.size() == 0)
            {
                target = qtwi;
            } else {
                target = exist.at(0);
            }

            if(http_hdr.mid(0,3) == "GET") { http_method_pie->slices().at(0)->setLabelVisible(); http_method_pie->slices().at(0)->setValue(http_method_pie->slices().at(0)->value()+1); } else {
                if(http_hdr.mid(0,4) == "HEAD") { http_method_pie->slices().at(1)->setLabelVisible(); http_method_pie->slices().at(1)->setValue(http_method_pie->slices().at(1)->value()+1); } else {
                    if(http_hdr.mid(0,4) == "POST") { http_method_pie->slices().at(2)->setLabelVisible(); http_method_pie->slices().at(2)->setValue(http_method_pie->slices().at(2)->value()+1); } else {
                        if(http_hdr.mid(0,3) == "PUT") { http_method_pie->slices().at(3)->setLabelVisible(); http_method_pie->slices().at(3)->setValue(http_method_pie->slices().at(3)->value()+1); } else {
                            if(http_hdr.mid(0,6) == "DELETE") { http_method_pie->slices().at(4)->setLabelVisible(); http_method_pie->slices().at(4)->setValue(http_method_pie->slices().at(4)->value()+1); }
                        }
                    }
                }
            }

            QTreeWidgetItem *http_hdr_itm = new QTreeWidgetItem();
            http_hdr = http_hdr.mid(0, http_hdr.length()-9);
            http_hdr_itm->setText(0, http_hdr);

            target->addChild(http_hdr_itm);

            http_brief_tree_view->addTopLevelItem(target);
        }

        void add_data_to_http_brief(QString ip_addr, QString req_type, QString time, QString http_code, QString http_header)
        {
            QTreeWidgetItem *target;

                QList<QTreeWidgetItem*> exist = http_brief_tree_view->findItems(ip_addr,0,0);
                if(exist.size() == 0)
                {
                    target = new QTreeWidgetItem();
                    target->setText(0,ip_addr);
                    http_brief_tree_view->addTopLevelItem(target);
                } else {
                    target = exist.at(0);
                }

                QTreeWidgetItem* req_type_child = new QTreeWidgetItem();
                req_type_child->setText(0,req_type);
                    QTreeWidgetItem* http_header_child = new QTreeWidgetItem();
                    http_header_child->setText(0,http_header);
                    req_type_child->addChild(http_header_child);

                target->addChild(req_type_child);
         }

         void slice_explosion(QTreeWidgetItem* widg, int dead)
         {
            QPieSlice *target;
            QList<QPieSlice*> qpslist = http_srv_pie->slices();
            for(int i = 0; i < qpslist.size(); i++) { http_srv_pie->slices().at(i)->setExploded(false); }

            int j = 0;
            bool exist = false;
            for(int i = 0 ; i < qpslist.length() ; i++)
            {
                if(qpslist.at(i)->label() == widg->text(0) || (widg->parent() && qpslist.at(i)->label() == widg->parent()->text(0)))
                {
                    j = i;
                    exist = true;
                    break;
                } else {
                    continue;
                }
            }

            if(exist)
            {
                target = http_srv_pie->slices().at(j);
                target->setExploded(true);
            }
         }

         void apply_new_model(QAbstractTableModel* mod)
         {
             cap_table->setModel(mod);
         }

         void show_on_text_data_widget(QTreeWidgetItem* widg, int dead)
         {
             if(widg->childCount() == 0)
             {
                 text_data_widget = new QWidget();
                     text_data_layout = new QVBoxLayout();
                         text_data = new QTextEdit();
                         text_data->setReadOnly(true);
                         text_data->setFont(QFont("calibri", 11));

                     text_data_layout->addWidget(text_data);
                 text_data_widget->setLayout(text_data_layout);

                 text_data->setText(widg->text(0));
                 text_data_widget->showMaximized();
             }
         }

         void add_new_valid_filter(QString v) {

             for(auto items : filtering_history->findItems(v, Qt::MatchExactly))
             {
                 if(items->text() == v) { return; }
             }

             filtering_history->addItem(v);
             filtering_history->scrollToBottom();
         }

         void refresh_model(Packets_TableModel* mod)
         {
            packet_count->setText(QString::number(mod->getpackrlist().size()));
            if(!play_cap->isEnabled())
            {
                temp = new Packets_TableModel();
                temp->ADD_TO_LIST2(mod->getpackrlist());
                if(cap_table->verticalScrollBar()->sliderPosition() == cap_table->verticalScrollBar()->maximum()) { cap_table->scrollToBottom(); }
                cap_table->setModel(temp);
                resize_cols();
            }
         }

         void resize_cols()
         {
             cap_table->setColumnWidth(0,67);
             cap_table->setColumnWidth(1,49);
             cap_table->setColumnWidth(2,57);
             cap_table->setColumnWidth(3,236);
             cap_table->setColumnWidth(4,50);
             cap_table->setColumnWidth(5,480);
             cap_table->setColumnWidth(6,67);
             cap_table->setColumnWidth(7,55);
             cap_table->setColumnWidth(8,101);
             cap_table->setColumnWidth(9,352);
             cap_table->setColumnWidth(10,102);
             cap_table->setColumnWidth(11,301);
         }

         void set_filter_text(QListWidgetItem* in) { filter_input->setText(in->text()); }

            void fullscreen(bool);
            void zoom_in_cap_panel();
            void zoom_out_cap_panel();
            void clear_cap_panel();
            void sh_table_brief(bool b) { if(b) {hide_support->setVisible(true); root_layout->addWidget(hide_support, 5, 1, 2, 1); } else { hide_support->setVisible(false); root_layout->addWidget(hide_support, 5, 1, 0, 0);} };
            inline void sh_conf_win(bool) { only_one_win(config_win); }
            void sh_devs_conf();
            void play_btn(bool);
            void stop_btn(bool);

            /* -------------- DEV LIST SLOTS -------------- */
            int dev_verif_checking(QTreeWidgetItem*, int);
            void append_data_to_capture_cap_info(QTreeWidgetItem*,QString);
            void append_data_to_info_text(QString);
            void append_data_to_cap_table(QStringList*);


            inline void retrieve_filter_value()
            {
                QString get_filter = filter_input->text();
                emit filter(get_filter, filter_input);
            }

            void CONNECT(QGraphicsPixmapItem* q1, QGraphicsPixmapItem* q2, QString data)
            {
                QGraphicsLineItem *line = new QGraphicsLineItem(q1->pos().x()+63, q1->pos().y()+63, q2->pos().x()+63, q2->pos().y()+63);
                line->setPen(QPen(QColor("#303952"),2));
                line->setZValue(-1);
                line->setData(0, data);
                graphic_scene->addItem(line);
                line->setVisible(false);
            }

            QGraphicsPixmapItem* add_new_item_to_graphic_view(QString path, QString data, QString text, QString tooltip, qreal pos1, qreal pos2)
            {
                auto pix = new QPixmap(path);
                auto *item = new QGraphicsPixmapItem();
                pix->scaledToHeight(pix->height(), Qt::SmoothTransformation);
                item->setPixmap(*pix);
                auto proxy = new QGraphicsProxyWidget(item);

                auto *label = new QLabel(text);
                label->setAlignment(Qt::AlignVCenter);
                label->setStyleSheet("background-color: white");
                label->setFont(QFont(label->font().toString(), 11));

                proxy->setWidget(label);
                proxy->setPos(0,130);
                proxy->setToolTip(tooltip);

                item->setData(0,data);
                proxy->setData(0,data);

                item->setPos(pos1,pos2);
                graphic_scene->addItem(item);

                item->setVisible(false);
                proxy->setVisible(false);

                return item;
            }

            void SHOW_APPROPRIATE_VIEW(QListWidgetItem *item)
            {
                for(int i = 0 ; i < graphic_scene->items().size() ; i++)
                {
                    if(graphic_scene->items().at(i)->data(0) == item->text())
                    {
                       graphic_scene->items().at(i)->setVisible(true);
                    } else {
                       graphic_scene->items().at(i)->setVisible(false);
                    }
                }
            }


signals:
    void filter(QString, QLineEdit*);
};


class Graphics_view_zoom : public QObject {

    Q_OBJECT

public:
  Graphics_view_zoom(QGraphicsView* view);
  void gentle_zoom(double factor);
  void set_modifiers(Qt::KeyboardModifiers modifiers);
  void set_zoom_factor_base(double value);

private:
  QGraphicsView* _view;
  Qt::KeyboardModifiers _modifiers;
  double _zoom_factor_base;
  QPointF target_scene_pos, target_viewport_pos;
  bool eventFilter(QObject* object, QEvent* event);

signals:
  void zoomed();
};


#endif // MAINWIN_H
