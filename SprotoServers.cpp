
#include "MainWin.h"
#include "SprotoServers.h"


void Win::OPEN_DIAG(QListWidgetItem* QLWI)
{
    _WIN_AGENT_ *WAG = new _WIN_AGENT_(dc_srv->get_S_THREAD_CO(QLW->row(QLWI)));
    WAG->show();
}

void Win::remove_host()
{
    // TODO
}

void Win::append_host_to_list(QString HOST_NAME)
{
    _agents_nbr->setText(QString::number(_agents_nbr->text().toInt()+1));

    // WINDOWS
    // TODO : CHECK IF WIN OR LINUX
    QListWidgetItem *ql = new QListWidgetItem(QIcon("C:/Sproto_CPP_v3/Images/LAPTOP.png"), HOST_NAME);
    connect(QLW, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(OPEN_DIAG(QListWidgetItem*)));
    QLW->addItem(ql);
}

void Win::_init_agent_panel()
{
    agent_panel = new QWidget();
        agent_panel_vbox = new QVBoxLayout();
        agent_panel->setLayout(agent_panel_vbox);

        QLW = new QListWidget;
        agent_panel_vbox->addWidget(QLW);
            QLW->setFlow(QListView::LeftToRight);
            QLW->setWrapping(true);
            QLW->setSpacing(5);
            QLW->setIconSize(QSize(150,150));
            QLW->setViewMode(QListWidget::IconMode);

        central_tab->addTab(agent_panel, "Agents");
}
