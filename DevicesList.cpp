#include "pcap.h"
#include <string_view>
#include "MainWin.h"
#include "CaptureThreads.h"
#include "UnknownUtils.h"
#include <QDateTime>
#include <iostream>
#include "Strings.h"
#include <QTreeWidgetItem>
#include <QThread>
#include <string>
#include <WinSock2.h>
#include "iphlpapi.h"

#define ARRAY_BUFF 256

using namespace std;

int Win::dev_verif_checking(QTreeWidgetItem* item, int v)
{
    Q_UNUSED(v)
    if(item->childCount() >= 1)
    {
        QString selected_device_desc = item->text(0);
        QString selected_device_name = item->child(0)->text(0);

        if(item->checkState(0))
        {
            info_text->append(Info(selected_device_desc) + " sur écoute.");
        } else {
            if(!item->checkState(0))
            {
                info_text->append(Info(selected_device_desc) + " n'est plus sur écoute.");
            }
        }
    }

    return 0;
}


void Win::ret_device_list()
{

    map<string, PIP_ADAPTER_INFO> PAI_MAP;
    int NIC_Y = 0;
    QIcon net_device("C:/Sproto_CPP_v3/Icons/netcard_1.png");
    pcap_if_t* single_dev;

    QList<QList<PIP_ADAPTER_INFO>> _IPHLPAPI_IP_DEVS_;
    IP_ADAPTER_INFO *pAdapterInfo;
    ULONG ulOutBufLen;
    DWORD dwRetVal;

    pAdapterInfo = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
    ulOutBufLen = sizeof (pAdapterInfo);

    if(GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) != ERROR_SUCCESS) {
        free(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO*)malloc(ulOutBufLen);
    }

    if((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) != ERROR_SUCCESS) {
        cout << "GetAdaptersInfo call failed with " << dwRetVal << endl;
    }

    PIP_ADAPTER_INFO info = pAdapterInfo;

    char* errbuff[PCAP_ERRBUF_SIZE];
    int i = 0;

    int getdevs = pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &all_devs, *errbuff);
    if(getdevs == -1) { cout << "Erreur" << endl; }

    int_win_tree_view = new QTreeWidget();
    int_win_tree_view->setHeaderHidden(true);

    single_dev = all_devs;

    stat_label->setText(gethostname());
    while(single_dev != NULL)
    {
            QString _MAC_ADDR_;
                QString _GRAPHIC_ITEM_TEXT_DATA_;
                QList<QString> _GRAPHIC_ITEM_GATEWAYS;
                QList<QString> _GRAPHIC_ITEM_WEB_;
                QList<QString> _GRAPHIC_ITEM_DNS_;
                QList<QString> _GRAPHIC_ITEM_DHCP_;
            auto a = single_dev->addresses;
            i++;

            QList<PIP_ADAPTER_INFO> _adapinfo_;
            _adapinfo_.push_back(info);
            _IPHLPAPI_IP_DEVS_.push_back(_adapinfo_);

            // CHANTIER
            PAI_MAP[string(single_dev->name).substr(20,38)] = info;

            cout << string(single_dev->name).substr(20,38) << " - " << PAI_MAP[string(single_dev->name).substr(20,38)]->Description << endl;

            //cout << " " << i << " - " << single_dev->name << " - " << single_dev->description << endl;
            //PAI_MAP[string(single_dev->name).substr(20,38)] = info;
            //cout << PAI_MAP[string(single_dev->name).substr(20,38)]->Description << "\n\n";

            QString index = QString::number(i);
            QString dev_name = (QString)"[ " + index + (QString)" ] " + single_dev->description;

            _GRAPHIC_ITEM_TEXT_DATA_ += (QString)_IPHLPAPI_IP_DEVS_[i-1].at(0)->Description + "\n";
            QString dev_NIC_name = (QString)_IPHLPAPI_IP_DEVS_[i-1].at(0)->AdapterName;

            info_text->append(Info("Interface " + QString(_IPHLPAPI_IP_DEVS_[i-1].at(0)->Description) + " trouvée."));

            string dev_name_to_string = single_dev->name;
            const char* dev_name_to_char = dev_name_to_string.c_str();

            QTreeWidgetItem *dev_item = new QTreeWidgetItem();
                QTreeWidgetItem *dev_item_name = new QTreeWidgetItem();

            dev_item->setText(0, dev_name);
                dev_item_name->setText(0, dev_NIC_name);

            dev_item->addChild(dev_item_name);
                int_win_tree_view->addTopLevelItem(dev_item);

                dev_item->setDisabled(true);

                // Affichage des adresses et des infos
                while(a != NULL)
                {
                    switch(a->addr->sa_family)
                    {
                      case AF_INET:
                      {
                        _IP_ADDR_STRING *ADDR_FIRST_INDEX = &_IPHLPAPI_IP_DEVS_[i-1].at(0)->IpAddressList;
                        this->list_of_devices->addItem((QString)_IPHLPAPI_IP_DEVS_[i-1].at(0)->Description);

                        while(ADDR_FIRST_INDEX)
                        {
                            QString TWO;
                            for(int _MAC_I = 0 ; _MAC_I < 6 ; _MAC_I++)
                            {
                                TWO = QString("%11").arg((int)_IPHLPAPI_IP_DEVS_[i-1].at(0)->Address[_MAC_I], 1, 16).toUpper();
                                if(TWO.size()==1) { TWO.prepend("0"); }
                                if(_MAC_I!=5) { TWO.append(":"); }
                                _MAC_ADDR_.append(TWO);
                            }

                            // @MAC
                            QString dev_mac_addr = "Adresse physique:\t" + _MAC_ADDR_;
                            _GRAPHIC_ITEM_TEXT_DATA_ += _MAC_ADDR_ + "\n";

                            // @IP
                            QString dev_ip_addr = "Adresse IP:\t\t" + (QString)ADDR_FIRST_INDEX->IpAddress.String + "\nMasque:\t\t" + (QString)ADDR_FIRST_INDEX->IpMask.String;
                            _GRAPHIC_ITEM_TEXT_DATA_ += (QString)ADDR_FIRST_INDEX->IpAddress.String + "\n";


                            // DHCP
                            if(_IPHLPAPI_IP_DEVS_[i-1].at(0)->DhcpEnabled) {
                                dev_ip_addr += "\nDHCP Activé";
                                QDateTime _DHCP_t;
                                dev_ip_addr += "\n\tServeur DHCP:\t" + (QString)_IPHLPAPI_IP_DEVS_[i-1].at(0)->DhcpServer.IpAddress.String;
                                _DHCP_t.setTime_t(_IPHLPAPI_IP_DEVS_[i-1].at(0)->LeaseObtained);
                                dev_ip_addr += "\n\tBail obtenu:\t\t" + _DHCP_t.toString();
                                _DHCP_t.setTime_t(_IPHLPAPI_IP_DEVS_[i-1].at(0)->LeaseExpires);
                                dev_ip_addr += "\n\tExpiration:\t\t" + _DHCP_t.toString();
                            }

                            QTreeWidgetItem *dev_item_mac = new QTreeWidgetItem();
                            dev_item_mac->setText(0, dev_mac_addr);
                            dev_item->addChild(dev_item_mac);

                            if((QString)_IPHLPAPI_IP_DEVS_[i-1].at(0)->Description != "0.0.0.0")
                            {
                                QTreeWidgetItem *dev_item_ip = new QTreeWidgetItem();
                                dev_item_ip->setText(0, dev_ip_addr);
                                dev_item->addChild(dev_item_ip);
                                ADDR_FIRST_INDEX = ADDR_FIRST_INDEX->Next;
                            }
                        }

                        _IP_ADDR_STRING *GATEWAY_FIRST_INDEX = &_IPHLPAPI_IP_DEVS_[i-1].at(0)->GatewayList;

                        QString gateway = "Passerelle(s): ";
                        while(GATEWAY_FIRST_INDEX)
                        {
                                gateway += "\n\t " + (QString)GATEWAY_FIRST_INDEX->IpAddress.String;

                                if(_IPHLPAPI_IP_DEVS_[i-1].at(0)->DhcpEnabled && (string)_IPHLPAPI_IP_DEVS_[i-1].at(0)->DhcpServer.IpAddress.String == (string)GATEWAY_FIRST_INDEX->IpAddress.String)
                                {
                                    _GRAPHIC_ITEM_GATEWAYS.append(QString(GATEWAY_FIRST_INDEX->IpAddress.String) + " \nDHCP");
                                } else {
                                    _GRAPHIC_ITEM_GATEWAYS.append(GATEWAY_FIRST_INDEX->IpAddress.String);
                            }

                            GATEWAY_FIRST_INDEX = GATEWAY_FIRST_INDEX->Next;
                        }

                        QTreeWidgetItem *dev_item_gateway = new QTreeWidgetItem();
                        dev_item_gateway->setText(0, gateway);
                        dev_item->addChild(dev_item_gateway);

                        QGraphicsPixmapItem* NIC = add_new_item_to_graphic_view("C:/Sproto_CPP_v3/Images/NIC.png",(QString)_IPHLPAPI_IP_DEVS_[i-1].at(0)->Description,_GRAPHIC_ITEM_TEXT_DATA_,index,0,NIC_Y);
                        NIC->setData(0, (QString)_IPHLPAPI_IP_DEVS_[i-1].at(0)->Description);
                            if(!_GRAPHIC_ITEM_GATEWAYS.empty())
                            {
                                int GATE_X = 380;
                                int GATE_Y = NIC_Y;
                                for(int GTWY = 0 ; GTWY < _GRAPHIC_ITEM_GATEWAYS.size() ; GTWY++ )
                                {
                                    if((QString)_GRAPHIC_ITEM_GATEWAYS.at(GTWY) != "0.0.0.0")
                                    {
                                        //GATE_X += 450;
                                        QGraphicsPixmapItem* RTR = add_new_item_to_graphic_view("C:/Sproto_CPP_v3/Images/ROUTER.png",(QString)_IPHLPAPI_IP_DEVS_[i-1].at(0)->Description,_GRAPHIC_ITEM_GATEWAYS.at(GTWY),index,GATE_X,GATE_Y);
                                        RTR->setData(0, (QString)_IPHLPAPI_IP_DEVS_[i-1].at(0)->Description);
                                        CONNECT(NIC, RTR, (QString)_IPHLPAPI_IP_DEVS_[i-1].at(0)->Description);
                                        GATE_Y += 200;
                                    }
                                }
                            }

                        if(ret_dev_list_by_winsock((QString)iptos(((struct sockaddr_in *)a->addr)->sin_addr.s_addr)) == 1) {
                            dev_item->setDisabled(false);
                        }

                       // if(info->Next->Description != info->Description) {
                             info = info->Next;
                        //
                        break;
                       }
                 }
                    a = a->next;
            }

                dev_item->setFlags(dev_item->flags() | Qt::ItemIsUserCheckable);
                dev_item->setCheckState(0, Qt::Unchecked);

                Capture_WorkerThread *cwt_1 = new Capture_WorkerThread(single_dev, dev_item, index, dev_name_to_char);
                    cwt_1->start();

                S_A_T *sat = new S_A_T(dev_item);
                sat->start();
                QObject::connect(cwt_1, SIGNAL(packet_notify()), sat, SLOT(append_to_pn()));
                QObject::connect(cwt_1, SIGNAL(here_is_packet_size(qreal)), sat, SLOT(append_to_ps(qreal)));
                QObject::connect(sat, SIGNAL(throw_pn(qreal)), this, SLOT(assert_point_to_pckt_per_sec_chart(qreal)));
                QObject::connect(sat, SIGNAL(throw_ps(qreal)), this, SLOT(assert_point_to_size_per_sec_chart(qreal)));
                QObject::connect(cwt_1, SIGNAL(test_signal(QTreeWidgetItem*, QString)), this, SLOT(append_data_to_capture_cap_info(QTreeWidgetItem*, QString)));
                QObject::connect(this, SIGNAL(filter(QString, QLineEdit*)), cwt_1, SLOT(apply_filter(QString, QLineEdit*)));
                QObject::connect(cwt_1, SIGNAL(send_to_http_brief(QTreeWidgetItem*, QString)), this, SLOT(add_data_to_http_brief_simple(QTreeWidgetItem*, QString)));
                QObject::connect(cwt_1, SIGNAL(send_to_http_srv_chart(QString)), this, SLOT(add_slice_to_srv_pie(QString)));
                QObject::connect(cwt_1, SIGNAL(send_http_code(QString)), this, SLOT(add_slice_to_http_srv_code(QString)));
                QObject::connect(cwt_1, SIGNAL(SEND_TO_CAP_TABLE(QStringList*)), MCT, SLOT(here_is_new_packets(QStringList*)));
                QObject::connect(MCT, SIGNAL(here_is_new_ptm(Packets_TableModel*)), this, SLOT(refresh_model(Packets_TableModel*)));
                QObject::connect(cwt_1, SIGNAL(here_is_a_valid_filter_to_store(QString)), this, SLOT(add_new_valid_filter(QString)));
                QObject::connect(cwt_1, SIGNAL(ready()), this, SLOT(resize_cols()));
                //QObject::connect(cwt_1, SIGNAL(SEND_TO_EVENTS_SIG(QStringList*)), ETM, SLOT(ADD_TO_LIST(QStringList*)));

        single_dev = single_dev->next;
    }


    cout << "----------------------------------------" << endl;
    for(int i = 0 ; i < _IPHLPAPI_IP_DEVS_.size() ; i++){
        for(int j = 0 ; j < _IPHLPAPI_IP_DEVS_.at(i).size() ; j++ )
        {
             qDebug() << i << " - " << _IPHLPAPI_IP_DEVS_.at(i).at(j)->AdapterName << " - " << _IPHLPAPI_IP_DEVS_.at(i).at(j)->Description;
        }
    }


    QObject::connect(int_win_tree_view, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(dev_verif_checking(QTreeWidgetItem*, int)));

};


