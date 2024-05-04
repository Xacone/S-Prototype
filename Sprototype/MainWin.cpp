#include "MainWin.h"

using namespace std;

QWidget *_this_;
int cap_tab_fsize = 9;
int index_of_row_to_fill = 0;

void only_one_win(QWidget *widg)
{
    if(!widg->isVisible()) { widg->show(); } else {
        if(widg->isVisible()) { widg->activateWindow(); }
    }
}

void act_init(QAction *action, QIcon ico, QString title)
{
     action->setIcon(ico);
     action->setText(title);
     action->setToolTip(title);
}

Win::Win()
{
    _this_ = this;
    _pal_ = new QPalette();
    _font_ = new QFont("Calibri", 10);
    this->setFont(*_font_);

    // Json
   /* if(jwax.loadFile("C:/Users/Yazid/sproto_cpp_v01/sproto_test_conf.json")) { qDebug() << "Json Charged, grosse cérémonie."; } else {
        cout << "Erreur de chargement Json !!!" << endl;
    } */

    // Paramètres de l'application
    this->setWindowTitle("S-Prototype v0.1");
    this->showFullScreen();

    // Caractères spéciaux
    /* QString è(0xE8); // è
    QString é(0xE9); // é
    QString À(0xC0); // À */

    // Initialisations des fenêtres secondaires
    //conf_Win = new Config_win;

    // Icons
    QIcon server_icn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/icons8_server.ico");
    QIcon fullscreen_icn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/full_screen_1.png");
    QIcon font_size_icn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/font_size_1.png");
    QIcon zoom_in_icn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/zoom_in.png");
    QIcon zoom_out_icn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/zoom_out.png");
    QIcon connect_icn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/devices_1.ico");
    QIcon net_device_icn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/netcard_1.png");
    QIcon wolf_icn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/wolf_1.png");
    QIcon save_icn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/save.png");
    QIcon save_as_icn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/save_as.png");
    QIcon focus_2_icn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/focus_2.png");
    QIcon open_file_icn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/open_file.png");
    QIcon quit_icn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/exit_1.png");
    QIcon honeypot_icn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/honeypot_1.png");
    QIcon bluetooth_ocn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/bluetooth_1.png");
    QIcon wifi_icn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/wifi_1.png");
    QIcon log_icn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/log_1.png");
    QIcon clear_icn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/clear_1.png");
    QIcon brief_table_icn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/brief_table.png");
    QIcon play_icn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/play_1.png");
    QIcon stop_icn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/pause_1.png");
    QIcon ssh_client_icn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/ssh.png");
    QIcon data_icn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/data_1.png");
    QIcon radar_icn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/radar_1.png");
    QIcon terminal_icn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/terminal_1.png");
    QIcon config_icn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/config_1.png");
    QIcon alert_icn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/alert_1.png");
    QIcon analyze_icn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/analyze_1.png");
    QIcon chart_icn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/piechart2.png");
    QIcon routing_icn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/ip_routing.ico");
    QIcon dns_icn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/dns.ico");
    QIcon arp_icn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/some_list.ico");
    QIcon tcp_srv_icn("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/servers_icn.ico");
    QIcon globe("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/globe.png");
    QIcon loupe("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/loupe.png");

    QIcon pdf("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/pdf.png");
    QIcon xml("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/xml.png");
    QIcon json("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/json.png");
    QIcon send("C:/Users/1234Y/OneDrive/Documents/SPROTO V3/Sproto_CPP_v3-20220927T114951Z-001/Sproto_CPP_v3/Icons/send.png");

    // Composants du menu
    file = menuBar()->addMenu("&Fichier");
    network_devices = menuBar()->addMenu("&Interfaces");
    edit = menuBar()->addMenu("&Config");
    tools = menuBar()->addMenu("&Outils");
    modules = menuBar()->addMenu("&Modules");
    view = menuBar()->addMenu("&Vue");
    QString about_txt = "A propos";
    about = menuBar()->addMenu(about_txt);

    /* -------------------- FICHIER -------------------- */
    new_ = new QAction();
    new_->setText("Nouveau");
    new_->setIcon(wolf_icn);
    new_->setStatusTip("Nouveau");

    new_focus = new QAction();
    new_focus->setText("Nouveau focus");
    new_focus->setIcon(focus_2_icn);
    new_focus->setToolTip("Nouveau focus");

    open_file = new QAction();
    open_file->setText("Ouvrir un fichier");
    open_file->setIcon(open_file_icn);
    open_file->setToolTip("Ouvrir un fichier");

    save_file = new QAction();
    save_file->setText("Enregistrer");
    save_file->setIcon(save_icn);
    save_file->setToolTip("Enregistrer");

    save_file_as = new QAction();
    save_file_as->setText("Enregistrer sous");
    save_file_as->setIcon(save_as_icn);
    save_file_as->setToolTip("Enregistrer sous");

    import_log = new QAction(log_icn, "Ouvrir un fichier log", NULL);

    QString open_recent_text = "Ouvrir fichier recent";
    //.append(é); open_recent_text.append("cent");
    open_recent = new QMenu(open_recent_text);

    babye = new QAction("Qutter");
    babye->setIcon(quit_icn);

    file->addAction(new_);
    file->addAction(new_focus);
    file->addSeparator(); /*----------------------*/
    file->addAction(open_file);
    file->addAction(save_file);
    file->addAction(save_file_as);
    file->addSeparator(); /*----------------------*/
    file->addAction(import_log);
    file->addSeparator(); /*----------------------*/
    file->addMenu(open_recent);
    file->addSeparator(); /*----------------------*/
    file->addAction(babye);

    /* -------------------- DEVICES -------------------- */
    dev_opt = new QAction();
    act_init(dev_opt, connect_icn, "Options d'interfaces");
    network_devices->addAction(dev_opt);
    network_devices->addSeparator();

    routing_table = new QAction("Table de routage");
    routing_table->setIcon(routing_icn);
    network_devices->addAction(routing_table);

    arp_table = new QAction("Tables ARP");
    arp_table->setIcon(arp_icn);
    network_devices->addAction(arp_table);

    DNS_servers = new QAction("Serveurs DNS");
    network_devices->addAction(DNS_servers);
    DNS_servers->setIcon(dns_icn);

    net_tcp_table = new QAction("Sessions TCP");
    net_tcp_table->setIcon(tcp_srv_icn);
    network_devices->addAction(net_tcp_table);

    /* -------------------- CONFIG -------------------- */
    config = new QAction();
    act_init(config, config_icn, "Paramètres");
    edit->addAction(config);

    /* -------------------- TOOLS -------------------- */
    get_agents_list = new QAction();
    get_agents_list->setIcon(radar_icn);
    get_agents_list->setText("Agents actifs");
    tools->addAction(get_agents_list);

    action_map = new QAction();
    act_init(action_map, globe, "Carte");
    tools->addAction(action_map);

    /* -------------------- MODULES -------------------- */
    honeyPot_Management = new QAction();
    honeyPot_Management->setText("Honeypots");
    honeyPot_Management->setIcon(honeypot_icn);
    modules->addAction(honeyPot_Management);

    /* -------------------- VUE -------------------- */
    QString full_scren_txt;
    full_scren_txt = "Plein ecran";
    fullscreen_check = new QAction(full_scren_txt);
    fullscreen_check->setCheckable(true);
    fullscreen_check->setIcon(fullscreen_icn);
    view->addAction(fullscreen_check);
    fullscreen_check->setChecked(true);

    view->addSeparator();

    ssh_client_check = new QAction("SSH Client");
    ssh_client_check->setCheckable(true);
    ssh_client_check->setIcon(ssh_client_icn);
    view->addAction(ssh_client_check);

    packet_capture_check = new QAction("Capture");
    packet_capture_check->setCheckable(true);
    packet_capture_check->setIcon(data_icn);
    view->addAction(packet_capture_check);

    agent_console_check = new QAction("Console");
    agent_console_check->setCheckable(true);
    agent_console_check->setIcon(terminal_icn);
    view->addAction(agent_console_check);

    QString resume_title = QString::fromLocal8Bit("Vue des événements");
    brief_table_check = new QAction(resume_title);
    brief_table_check->setCheckable(true);
    brief_table_check->setIcon(brief_table_icn);
    view->addAction(brief_table_check);
    brief_table_check->setChecked(false);

    view->addSeparator();

    /* font_choose = new QAction("Taille et police");
    font_choose->setIcon(font_size_icn);
    view->addAction(font_choose); */

    /* --------- TOOL BAR --------- */
    // Composants de la Tool bar
    tool_bar = new QToolBar();
    tool_bar->setMovable(false);
    tool_bar->setFixedHeight(29);
    tool_bar->addAction(new_);
    tool_bar->addAction(new_focus);
    tool_bar->addAction(save_file);
    tool_bar->addAction(dev_opt);
    tool_bar->addAction(config);
    tool_bar->addAction(routing_table);
    tool_bar->addAction(net_tcp_table);
    tool_bar->addAction(arp_table);
    tool_bar->addAction(DNS_servers);
    tool_bar->addSeparator(); /* ------------------ */
    tool_bar->addAction(get_agents_list);
    tool_bar->addAction(action_map);
    tool_bar->addSeparator(); /* ------------------ */
    tool_bar->addAction(ssh_client_check);
    tool_bar->addAction(agent_console_check);
    tool_bar->addAction(packet_capture_check);
    tool_bar->addAction(brief_table_check);
    tool_bar->addSeparator(); /* ------------------ */
    tool_bar->addAction(honeyPot_Management);
    addToolBar(tool_bar);

    /*----------- BODY -----------*/
    root_widget = new QWidget();
        root_layout = new QGridLayout();

            v_layout_1 = new QVBoxLayout();
                central_tab = new QTabWidget();

                    panel_info = new QWidget();
                        v_layout_root = new QVBoxLayout;
                            v_layout_1_0 = new QHBoxLayout();
                                info_text = new QTextEdit();
                                filtering_history = new QListWidget();
                                text_browser = new QTextBrowser();

                    panel_capture = new QWidget();
                        v_layout_1_1 = new QVBoxLayout();
                            cap_menu_bar = new QToolBar();
                            play_cap = new QAction();
                            stop_cap = new QAction();
                            cap_info = new QTextEdit();
                            cap_table = new QTableView();
                            cap_table->setSelectionBehavior(QAbstractItemView::SelectRows);
                            QPalette pal;
                            pal.setColor(QPalette::Base, QColor());
                            cap_table->setFont(QFont("Calibri", cap_tab_fsize, QFont::Bold));
                            cap_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
                                MCT = new Model_CoworkerThread();
                                MCT->start();
                                cap_zoom_in = new QAction();
                            cap_zoom_out = new QAction();
                            packet_count = new QLabel("0");
                            clear_cap = new QAction();
                            LINE_SPEED = new QComboBox();

                            filter_input = new QLineEdit();
                            panel_capture_hbox_widg = new QWidget();
                            panel_capture_hbox = new QHBoxLayout;
                            panel_capture_hbox_widg->setLayout(panel_capture_hbox);

                                // --------------- PAQUETS PAR SECONDE --------------- //

                                LINE_SPEED->addItem("10Mbps");
                                LINE_SPEED->addItem("100Mbps");
                                LINE_SPEED->addItem("1Gbps");
                                LINE_SPEED->addItem("10Gbps");
                                LINE_SPEED->addItem("100Gbps");

                                // --------------- PAQUETS PAR SECONDE --------------- //
                                pckt_per_sec = new QChart();
                                pckt_per_sec_view = new QChartView(pckt_per_sec);
                                pckt_per_sec_series = new QLineSeries();

                                pckt_per_sec->legend()->hide();
                                pckt_per_sec->addSeries(pckt_per_sec_series);
                                pckt_per_sec->createDefaultAxes();

                                pckt_per_sec->setTitle("Paquets par seconde");
                                pckt_per_sec->setAnimationOptions(QChart::AllAnimations);
                                pckt_per_sec->axes(Qt::Horizontal).first()->setRange(0,60);
                                pckt_per_sec->axes(Qt::Horizontal).first()->setTitleText("Secondes");
                                pckt_per_sec->axes(Qt::Vertical).first()->setRange(0,500);
                                pckt_per_sec->axes(Qt::Vertical).first()->setTitleText("Paquets");
                                pckt_per_sec->setTitleFont(QFont("Calibri",12));
                                pckt_per_sec_series->setColor("#833471");
                                pckt_per_sec_view->setRenderHint(QPainter::Antialiasing);
                                panel_capture_hbox->addWidget(pckt_per_sec_view);

                                // --------------- TAILLE PAR SECONDE --------------- //
                                size_per_sec = new QChart();
                                size_per_sec_view = new QChartView(size_per_sec);
                                size_per_sec_series = new QLineSeries;

                                size_per_sec->legend()->hide();
                                size_per_sec->addSeries(size_per_sec_series);
                                size_per_sec->createDefaultAxes();

                                size_per_sec->setTitle(QString::fromLocal8Bit("Octets par seconde"));
                                size_per_sec->setAnimationOptions(QChart::AllAnimations);
                                size_per_sec->axes(Qt::Horizontal).first()->setRange(0,60);
                                size_per_sec->axes(Qt::Horizontal).first()->setTitleText("Secondes");
                                size_per_sec->axes(Qt::Vertical).first()->setRange(0,100000);
                                size_per_sec->axes(Qt::Vertical).first()->setTitleText("Octets x 1000");
                                size_per_sec->setTitleFont(QFont("Calibri", 12));
                                size_per_sec_series->setColor("#1289A7");
                                size_per_sec_view->setRenderHint(QPainter::Antialiasing);
                                panel_capture_hbox->addWidget(size_per_sec_view);

                    panel_view_agents = new QWidget();
                    _init_view_agents();

                    panel_http = new QWidget();
                        http_panel_menu_bar = new QToolBar();

                         panel_http_layout = new QHBoxLayout();
                          http_brief_split = new QSplitter();
                            http_brief_tree_view = new QTreeWidget();

                                    http_srv_chart = new QChart();
                                    chart_v1 = new QChartView(http_srv_chart);
                                    http_srv_pie = new QPieSeries();
                                        chart_v1->setStyleSheet("background-color: white;");

                         panel_http_layout2 = new QVBoxLayout();

                                    http_method_chart = new QChart();
                                    chart_v2 = new QChartView(http_method_chart);
                                    http_method_pie = new QPieSeries();
                                        chart_v2->setStyleSheet("background-color: white;");

                                    http_code_chart = new QChart();
                                    chart_v3 = new QChartView(http_code_chart);
                                    http_code_pie = new QPieSeries();
                                        chart_v3->setStyleSheet("background-color: white;");


                      // --------------- EVENEMEMENTS --------------- //

                      evenements = new QWidget;
                        events_h_lay = new QHBoxLayout();
                        events_toolb = new QToolBar();
                            v_layout_1_2 = new QVBoxLayout;
                                ETMTV = new QTableView();
                                    ETM = new EventView_TableModel(ETMTV);
                                QSplitter *s2 = new QSplitter();
                                ETM_TE = new QTextEdit();
                                ETM_TE2_TEST = new QTextEdit(); // Test !!

                                act_init(&show_associated_packets, loupe, QString::fromUtf8("Echange"));
                                act_init(&pdf_report, pdf, QString::fromUtf8("PDF"));
                                act_init(&json_report, json, QString::fromUtf8("JSON"));
                                act_init(&xml_report, xml, QString::fromUtf8("XML"));
                                act_init(&send_info, send, QString::fromUtf8("Envoyer"));

                                events_toolb->setOrientation(Qt::Vertical);
                                events_toolb->addAction(&show_associated_packets);
                                events_toolb->addSeparator();
                                events_toolb->addAction(&pdf_report);
                                events_toolb->addAction(&json_report);
                                events_toolb->addAction(&xml_report);
                                events_toolb->addSeparator();
                                events_toolb->addAction(&send_info);
                                events_toolb->setIconSize(QSize(32,32));
                                events_h_lay->addWidget(events_toolb);

                                ETMTV->verticalHeader()->setVisible(false);
                                ETMTV->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
                                ETMTV->verticalHeader()->setDefaultSectionSize(1);
                                ETMTV->setFont(QFont("Calibri", 9, QFont::Bold));
                                ETMTV->setEditTriggers(QAbstractItemView::NoEditTriggers);
                                ETMTV->setSelectionBehavior(QAbstractItemView::SelectRows);

                                s2->addWidget(ETM_TE);
                                s2->addWidget(ETM_TE2_TEST);
                                s2->setOrientation(Qt::Horizontal);

                            evenements->setLayout(events_h_lay);
                                events_h_lay->addLayout(v_layout_1_2, 0);

                            QSplitter *s1 = new QSplitter();
                                s1->setOrientation(Qt::Vertical);
                                s1->addWidget(ETMTV);
                                s1->addWidget(s2);

                            v_layout_1_2->addWidget(s1);

                        // --------------- EVENEMEMENTS --------------- //
                            //!\ Disloqué
                                panel_map = new QWidget();
                                    panel_map_vl = new QVBoxLayout();

                                    _init_map();

                       // --------------- Other INIT --------------- //

                        _init_routing_table();
                        //_init_tcp_table();

 /* -------------------------------------------------------- FNCTS -------------------------------------------------------- */
    central_tab->setMovable(false);

    root_widget->setLayout(root_layout);
        root_layout->addLayout(v_layout_1, 0, 1, 4, 1);

            v_layout_1->addWidget(central_tab);

                    _MAIN_panel_console = new QWidget();
                    panel_console_layout = new QHBoxLayout(_MAIN_panel_console);
                        console = new CustomConsole();
                        panel_console_layout->addWidget(console);
                        console->setCursorWidth(10);
                        console->setFont(QFont("consolas", 12, QFont::Bold));

                        central_tab->addTab(_MAIN_panel_console, "Console");

                    panel_info->setLayout(v_layout_root);

                        QHBoxLayout *qhbl = new QHBoxLayout;
                        filter_input->setStyleSheet("QLineEdit { border: 1px solid #7f8c8d; border-radius: 5px; }");
                        filter_input->setPlaceholderText("Syntaxe de filtrage de Winpcap");
                        filter_input->setToolTip("Syntaxe de filtrage de Winpcap");
                        qhbl->addWidget(filter_input);
                        v_layout_root->addLayout(qhbl);

                        v_layout_root->addLayout(v_layout_1_0);
                          //v_layout_1_0->addWidget(info_text);
                            info_text->setReadOnly(true);
                            info_text->append(Welcoming());
                            info_text->setFont(QFont("consolas", 10, QFont::Bold));
                            info_text->append(Warning(QString::fromLocal8Bit("Il faut faire attention parceque vous avez une version non signée de WinPcap.")));
                            info_text->append(Alert(QString::fromLocal8Bit("Malgré tout on reste rattaché au text-based, et la piraterie n'est jamais finie.")));

                            QSplitter *first_split = new QSplitter();
                            QSplitter *second_split = new QSplitter;

                            first_split->addWidget(info_text);
                            first_split->addWidget(second_split);

                            QVBoxLayout *qvbox1 = new QVBoxLayout();
                            v_layout_1_0->addLayout(qvbox1);

                            second_split->setOrientation(Qt::Vertical);
                            second_split->addWidget(filtering_history);
                            filtering_history->setFont(QFont("Calibri", 11));

                            text_browser->setOpenExternalLinks(false);
                            text_browser->setFont(QFont("consolas",10));
                            text_browser->setHtml(LearnMore());
                            second_split->addWidget(text_browser);

                            text_browser->resize(text_browser->width(), 1000);

                            qvbox1->addWidget(first_split);

                central_tab->addTab(panel_capture, "Capture sychrone");
                        panel_capture->setLayout(v_layout_1_1);
                        cap_info->append(" ");
                        cap_info->toPlainText();

                        v_layout_1_1->setMenuBar(cap_menu_bar);

                        play_cap->setIcon(play_icn);
                        play_cap->setDisabled(true);
                        cap_menu_bar->addAction(play_cap);

                        stop_cap->setIcon(stop_icn);
                        cap_menu_bar->addAction(stop_cap);

                        cap_menu_bar->addSeparator(); /* ------------ */

                        cap_menu_bar->addAction(clear_cap);
                        clear_cap->setIcon(clear_icn);
                        clear_cap->setText("Clear");

                        cap_menu_bar->addSeparator(); /* ------------ */
                        cap_menu_bar->addAction(cap_zoom_in);
                        cap_zoom_in->setIcon(zoom_in_icn);
                        cap_zoom_out->setIcon(zoom_out_icn);
                        cap_menu_bar->addAction(cap_zoom_out);
                        cap_menu_bar->addSeparator();
                        cap_menu_bar->addWidget(LINE_SPEED);

                        cap_menu_bar->addSeparator(); /* ------------ */

                        cap_menu_bar->addWidget(packet_count);
                        packet_count->setFont(QFont("Calibri", 12));

                        cap_menu_bar->setFixedHeight(30);

                        cap_info->setReadOnly(true);

                        QSplitter *cap_split = new QSplitter();

                        cap_split->addWidget(cap_table);
                        temp = new Packets_TableModel();
                        cap_table->setShowGrid(false);

                        QHeaderView *vertHeader = cap_table->verticalHeader();
                            vertHeader->setSectionResizeMode(QHeaderView::Fixed);
                            vertHeader->setDefaultSectionSize(1);

                        cap_split->addWidget(panel_capture_hbox_widg);
                        cap_split->setOrientation(Qt::Vertical);
                        v_layout_1_1->addWidget(cap_split);

                central_tab->addTab(panel_http, "HTTP Stats");

                    panel_http->setLayout(panel_http_layout);

                    panel_http_layout->addWidget(http_brief_tree_view);
                    QPalette http_tree_pal;
                    http_tree_pal.setColor(QPalette::Base, QColor("white"));
                    http_tree_pal.setColor(QPalette::Background, QColor("white"));
                            http_brief_tree_view->setAttribute(Qt::WA_StyledBackground, true);
                    http_brief_tree_view->setPalette(http_tree_pal);
                    http_brief_tree_view->setHeaderHidden(true);

                    panel_http_layout->addWidget(chart_v1);
                         http_srv_chart->setTitle(QString::fromUtf8("Répartition du flux HTTP"));
                         chart_v1->setRenderHint(QPainter::Antialiasing);
                         chart_v1->chart()->legend()->hide();
                         http_srv_chart->addSeries(http_srv_pie);
                         http_srv_chart->setAnimationOptions(QChart::AllAnimations);
                         http_srv_pie->setHoleSize(0);
                         http_srv_pie->setLabelsPosition(QPieSlice::LabelInsideHorizontal);

                    panel_http_layout2->addWidget(chart_v2);
                    panel_http_layout->addLayout(panel_http_layout2);

                        http_method_pie->append("GET", 0);
                        http_method_pie->slices().at(0)->setColor(QColor("#eb3b5a"));

                        http_method_pie->append("HEAD", 0);
                        http_method_pie->slices().at(1)->setColor(QColor("#fa8231"));

                        http_method_pie->append("POST", 0);
                        http_method_pie->slices().at(2)->setColor(QColor("#f7b731"));

                        http_method_pie->append("PUT", 0);
                        http_method_pie->slices().at(3)->setColor(QColor("#20bf6b"));

                        http_method_pie->append("DELETE", 0);
                        http_method_pie->slices().at(4)->setColor(QColor("#0fb9b1"));

                         http_method_chart->setTitle(QString::fromUtf8("Répartition des requêtes HTTP"));
                         http_method_chart->setAnimationOptions(QChart::AllAnimations);
                         chart_v2->setRenderHint(QPainter::Antialiasing);
                         http_method_chart->addSeries(http_method_pie);

                         chart_v3 = new QChartView(http_code_chart);
                         chart_v3->setRenderHint(QPainter::Antialiasing);
                         http_code_chart->addSeries(http_code_pie);

                         http_code_chart->setAnimationOptions(QChart::AllAnimations);
                         http_code_chart->setTitle(QString::fromUtf8(" Répartition des codes de réponse HTTP"));
                         http_code_chart->setAnimationOptions(QChart::AllAnimations);
                    panel_http_layout->addWidget(chart_v3);
                    chart_v3->setStyleSheet("background-color: white;");

                    http_brief_split->addWidget(http_brief_tree_view);
                    http_brief_tree_view->resize(this->width()/8, http_brief_tree_view->height());
                    http_brief_split->addWidget(chart_v1);
                    chart_v1->resize(this->width()/3, chart_v1->height());
                    http_brief_split->addWidget(chart_v2);
                    chart_v2->resize(this->width()/4, chart_v2->height());
                    http_brief_split->addWidget(chart_v3);
                    chart_v3->resize(this->width()/4, chart_v3->height());
                    http_brief_split->setOrientation(Qt::Horizontal);
                    panel_http_layout->addWidget(http_brief_split);

                    http_method_chart->setTitleFont(QFont("Calibri, 12"));
                    http_code_chart->setTitleFont(QFont("Calibri, 12"));
                    http_srv_chart->setTitleFont(QFont("Calibri, 12"));

                    central_tab->addTab(evenements, "Evénements");
                    ETMTV->setShowGrid(false);  // 9

                    central_tab->addTab(panel_view_agents, "Réseau");
                    central_tab->addTab(panel_info, "Filtrage");

    root_widget->show();
    this->setCentralWidget(root_widget);

    /*----------- STAT -----------*/

    stat_label = new QLabel();
    statusBar()->addWidget(stat_label);
    stat_label->setText("");

    // Fenêtre de configuration d'interfaces
    int_win = new QWidget();
        int_win->setFont(QFont("Calibri", 11));
        int_win->setFixedSize(1000,600);
        int_win->setWindowIcon(connect_icn);
        QString title_int_win = QString::fromLocal8Bit("Paramètres d'interfaces");  // = "Param"; title_int_win.append(è); title_int_win.append("tres d'interfaces");
        int_win->setWindowTitle(title_int_win);
        int_win_layout = new QHBoxLayout;
        int_win_group_box = new QGroupBox("Interfaces actives");
        int_win_group_box_layout = new QVBoxLayout;

        ret_device_list(); // A besoin de l'initialisation mais n'accepte pas les changements.

        int_win->setLayout(int_win_layout);
        int_win_layout->addWidget(int_win_group_box);
        int_win_group_box->setLayout(int_win_group_box_layout);
        int_win_group_box_layout->addWidget(int_win_tree_view);
        int_win_tree_view->setFont(QFont("Calibri", 12));

        panel_info_line_series();
        _init_stats_panel();
        _init_agent_panel();
        _init_wlan_panel();

            refresher->start();

    QObject::connect(action_map, SIGNAL(triggered(bool)), this, SLOT(sh_map(bool)));
    QObject::connect(fullscreen_check, SIGNAL(toggled(bool)), this, SLOT(fullscreen(bool)));
    QObject::connect(babye, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
    QObject::connect(cap_zoom_in, SIGNAL(triggered(bool)), this, SLOT(zoom_in_cap_panel()));
    QObject::connect(cap_zoom_out, SIGNAL(triggered(bool)), this, SLOT(zoom_out_cap_panel()));
    QObject::connect(clear_cap, SIGNAL(triggered(bool)), this, SLOT(clear_cap_panel()));
    QObject::connect(dev_opt, SIGNAL(triggered(bool)), this, SLOT(sh_devs_conf()));
    QObject::connect(stop_cap, SIGNAL(triggered(bool)), this, SLOT(stop_btn(bool)));
    QObject::connect(play_cap, SIGNAL(triggered(bool)), this, SLOT(play_btn(bool)));
    QObject::connect(filter_input, SIGNAL(returnPressed()), this, SLOT(retrieve_filter_value()));
    QObject::connect(http_brief_tree_view, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(slice_explosion(QTreeWidgetItem*, int)));
    QObject::connect(http_brief_tree_view, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(show_on_text_data_widget(QTreeWidgetItem*, int)));
    QObject::connect(http_srv_pie, SIGNAL(sumChanged()), this, SLOT(init_slices()));
    QObject::connect(config, SIGNAL(triggered(bool)), this, SLOT(sh_conf_win(bool)));
    QObject::connect(LINE_SPEED, SIGNAL(activated(int)), this, SLOT(SET_CHARTS_CAPACITY(int)));
    QObject::connect(filtering_history, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(set_filter_text(QListWidgetItem*)));
    QObject::connect(list_of_devices, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(SHOW_APPROPRIATE_VIEW(QListWidgetItem*)));
    QObject::connect(routing_table, SIGNAL(triggered(bool)), _ROUTING_TABLE_ , SLOT(show()));
    QObject::connect(net_tcp_table, SIGNAL(triggered(bool)), this, SLOT(sh_tcp_sessions(bool)));
    QObject::connect(ETMTV, SIGNAL(clicked(const QModelIndex&)), this, SLOT(SET_EVENTS_TEXT(const QModelIndex&)));

    init_conf_win();
}

QTextEdit* Win::getCapInfo() { return cap_info; }

void Win::fullscreen(bool b) { if(b) { this->showFullScreen(); } else { if(!b) {this->showNormal(); } } }

void Win::append_data_to_info_text(QString data) { info_text->append(data); }

void Win::zoom_in_cap_panel() {
    cap_tab_fsize += 1;
    cap_table->setFont(QFont(cap_table->font().toString(), cap_tab_fsize, QFont::Bold));
    for(int i = 0 ; i < 13 ; i++ ) { cap_table->setColumnWidth(i,cap_table->columnWidth(i)+10); }
}

void Win::zoom_out_cap_panel() {
    cap_tab_fsize -= 1;
    cap_table->setFont(QFont(cap_table->font().toString(), cap_tab_fsize, QFont::Bold));
    for(int i = 0 ; i < 13 ; i++ ) { cap_table->setColumnWidth(i,cap_table->columnWidth(i)-10); }
}

void Win::clear_cap_panel() {
    MCT->clear_ptm();
    cap_table->model()->deleteLater();
}

void Win::sh_devs_conf() { only_one_win(int_win); }

void Win::append_data_to_capture_cap_info(QTreeWidgetItem* qtwi, QString value) {
        if(!play_cap->isEnabled()) {  cap_info->append(value); }
}


QTableWidgetItem *qtwi;
bool isequal;

void Win::append_data_to_cap_table(QStringList* data)
{

}

void Win::play_btn(bool b)
{
    Q_UNUSED(b)
    play_cap->setDisabled(true);
    stop_cap->setEnabled(true);
    play_cap->setChecked(true);
}

void Win::stop_btn(bool b)
{
    Q_UNUSED(b)
    stop_cap->setDisabled(true);
    play_cap->setEnabled(true);
}
