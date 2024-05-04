
#include "MainWin.h"

void Win::init_conf_win()
{
    config_win = new QWidget();
    config_win->setFont(QFont("Calibi", 10));
        config_root_layout = new QHBoxLayout();
            config_tree = new QTreeWidget();
                global = new QTreeWidgetItem();
                    global_pref = new QTreeWidgetItem(global);
                capture = new QTreeWidgetItem();
                    capture_param_int = new QTreeWidgetItem(capture);
                    capture_filtrage = new QTreeWidgetItem(capture);
                protoc = new QTreeWidgetItem();
                    protoc_Ether = new QTreeWidgetItem(protoc);
                    protoc_IP4 = new QTreeWidgetItem(protoc);
                    protoc_ARP = new QTreeWidgetItem(protoc);
                    protoc_ICMP = new QTreeWidgetItem(protoc);
                    protoc_DOT1Q = new QTreeWidgetItem(protoc);
                agents = new QTreeWidgetItem();
                rapports = new QTreeWidgetItem();

                config_tree->header()->hide();

                global->setText(0,"Global");
                    global_pref->setText(0,"Préférences");
                capture->setText(0,"Capture");
                    capture_param_int->setText(0,"Interfaces");
                    capture_filtrage->setText(0,"Filtrage");
                protoc->setText(0,"Protocoles");
                    protoc_Ether->setText(0,"Ethernet");
                    protoc_IP4->setText(0,"IPv4");
                    protoc_ARP->setText(0,"ARP");
                    protoc_ICMP->setText(0,"ICMP");
                    protoc_DOT1Q->setText(0,"802.1Q");
                agents->setText(0,"Agents");
                rapports->setText(0,"Rapports");

                options_layout = new QVBoxLayout();

                opt_global = new QWidget();
                QVBoxLayout *opt_global_layout = new QVBoxLayout();
                opt_global->setLayout(opt_global_layout);
                opt_global_layout->addWidget(new QLabel("cc"));
                opt_global->setVisible(false);

                    opt_global_pref = new QWidget();

                opt_capture = new QWidget();
                QVBoxLayout *opt_capture_layout = new QVBoxLayout();
                opt_capture->setLayout(opt_capture_layout);
                opt_capture->setVisible(false);

                    QGroupBox *opt_capture_group_1 = new QGroupBox("Affichage");
                    QVBoxLayout *opt_capture_layout_1 = new QVBoxLayout();
                    show_packet_len = new QCheckBox("Afficher la taille des paquets");
                    show_packet_index = new QCheckBox("Afficher la numérotation");
                    show_packet_color = new QCheckBox("Coloration");

                    /* show_packet_len->setChecked((int)jwax.value({"cap_opt", "show_packet_size"}).toInt());
                        QObject::connect(show_packet_len, SIGNAL(stateChanged(int)), this, SLOT(JSON_show_packet_size(int)));
                    show_packet_index->setChecked(jwax.value({"cap_opt", "show_packet_index"}).toBool());
                        QObject::connect(show_packet_index, SIGNAL(stateChanged(int)), this, SLOT(JSON_show_packet_index(int)));
                    show_packet_color->setChecked(jwax.value({"cap_opt", "show_packet_coloration"}).toBool());
                        QObject::connect(show_packet_color, SIGNAL(stateChanged(int)), this, SLOT(JSON_show_packet_coloration(int)));
                    */

                    cap_mode = new QComboBox();
                    cap_mode->setToolTip("Sélectionnez un mode<br>d'affichage");
                    cap_mode->setFixedWidth(100);
                    cap_mode->addItem("Mode texte");
                    cap_mode->addItem("Mode tableau");
                    opt_capture_layout_1->addWidget(cap_mode);


                    // show_packet_color->setChecked(jwax.value({"cap_opt", "show_packet_coloration"}).toBool());

                    opt_capture_layout_1->addWidget(show_packet_len);
                    opt_capture_layout_1->addWidget(show_packet_index);
                    opt_capture_layout_1->addWidget(show_packet_color);

                    opt_capture_group_1->setLayout(opt_capture_layout_1);
                    opt_capture_layout->addWidget(opt_capture_group_1);

                    opt_capture_pref = new QWidget();
                    opt_capture_param_int = new QWidget();
                    opt_capture_filtrage = panel_info;

                    opt_capture_layout_1->addWidget(opt_capture_filtrage);
                    opt_capture_filtrage->setVisible(false);

                opt_protoc = new QWidget();
                QVBoxLayout *opt_protoc_layout = new QVBoxLayout();
                opt_protoc->setLayout(opt_protoc_layout);
                opt_protoc_layout->addWidget(new QLabel("cdd"));
                opt_protoc->setVisible(false);

                    opt_protoc_Ether = new QWidget();
                    opt_protoc_IP4 = new QWidget();
                    opt_protoc_ARP = new QWidget();
                    opt_protoc_ICMP = new QWidget();
                    opt_protoc_DOT1Q = new QWidget();

               opt_agents = new QWidget();
               QVBoxLayout *opt_agents_layout = new QVBoxLayout();
               opt_agents->setLayout(opt_agents_layout);
               opt_agents_layout->addWidget(new QLabel("la piraterie n'est jamais finie"));
               opt_agents->setVisible(false);

               opt_rapports = new QWidget();
               QVBoxLayout *opt_rapports_layout = new QVBoxLayout();
               opt_rapports->setLayout(opt_rapports_layout);
               opt_rapports_layout->addWidget(new QLabel("In moi je trust"));
               opt_rapports->setVisible(false);

            QList<QTreeWidgetItem*> top_level_items = {global, capture, protoc, agents, rapports};
            config_tree->addTopLevelItems(top_level_items);

            config_root_layout->addWidget(config_tree, 2);

            _font_ = new QFont("Calibri", 85);

            options_layout->addWidget(opt_global);
            options_layout->addWidget(opt_capture);
            options_layout->addWidget(opt_protoc);
            options_layout->addWidget(opt_agents);
            options_layout->addWidget(opt_rapports);

            config_root_layout->addLayout(options_layout, 8);

        config_win->setLayout(config_root_layout);


        QObject::connect(config_tree, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(widget_associated_to_choice(QTreeWidgetItem*, int)));
        //QObject::connect(cap_mode, SIGNAL(activated(int)), this, SLOT(set_cap_mode(int)));

}
