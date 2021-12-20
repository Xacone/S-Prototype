#include "MainWin.h"
#include "iphlpapi.h"
#include <WinSock2.h>
#include "RoutingTableModel.h"
#include <WS2tcpip.h>
#include <iostream>
#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

using namespace std;

PMIB_IPFORWARDTABLE pIpForwardTable;
DWORD dwSize = 0;
DWORD dwRetVal = 0;

char szDestIp[128];
char szMaskIp[128];
char szGatewayIp[128];
struct in_addr IpAddr;
QList<QStringList> *_ROUTING_DATA_ = new QList<QStringList>;


QList<QStringList>* routing_list() {

    int i;

    pIpForwardTable = (MIB_IPFORWARDTABLE *) MALLOC(sizeof (MIB_IPFORWARDTABLE));
    if (pIpForwardTable == NULL) {
        printf("Error allocating memory 1\n");
        exit(1);
    }

    if (GetIpForwardTable(pIpForwardTable, &dwSize, 0) == ERROR_INSUFFICIENT_BUFFER) {
        FREE(pIpForwardTable);
        pIpForwardTable = (MIB_IPFORWARDTABLE *) MALLOC(dwSize);
        if (pIpForwardTable == NULL) {
            printf("Error allocating memory 2\n");
            exit(1);
        }
    }

    if ((dwRetVal = GetIpForwardTable(pIpForwardTable, &dwSize, 0)) == NO_ERROR) {

        for (i = 0; i < (int) pIpForwardTable->dwNumEntries; i++) {
            QStringList *lst = new QStringList();
            IpAddr.S_un.S_addr = (u_long) pIpForwardTable->table[i].dwForwardDest;
            lst->push_back(inet_ntoa(IpAddr));
            IpAddr.S_un.S_addr = (u_long) pIpForwardTable->table[i].dwForwardMask;
            lst->push_back(inet_ntoa(IpAddr));
            IpAddr.S_un.S_addr = (u_long) pIpForwardTable->table[i].dwForwardNextHop;
            lst->push_back(inet_ntoa(IpAddr));
            lst->push_back(QString::number(pIpForwardTable->table[i].dwForwardIfIndex));

            switch (pIpForwardTable->table[i].dwForwardType) {
            case MIB_IPROUTE_TYPE_OTHER:
                lst->push_back("Autre");
                break;
            case MIB_IPROUTE_TYPE_INVALID:
                lst->push_back("Route invalide");
                break;
            case MIB_IPROUTE_TYPE_DIRECT:
                lst->push_back("Route directe");
                break;
            case MIB_IPROUTE_TYPE_INDIRECT:
                lst->push_back("Route indirecte");
                break;
            default:
                lst->push_back("Inconnu");
                break;
            }

            switch (pIpForwardTable->table[i].dwForwardProto) {
                                    case MIB_IPPROTO_OTHER:
                                        lst->push_back("Autre");
                                        break;
                                    case MIB_IPPROTO_LOCAL:
                                        lst->push_back("Local");
                                        break;
                                    case MIB_IPPROTO_NETMGMT:
                                        lst->push_back("Route statique établie lors de la configuration");
                                        break;
                                    case MIB_IPPROTO_ICMP:
                                        lst->push_back("Redirection ICMP");
                                        break;
                                    case MIB_IPPROTO_EGP:
                                        lst->push_back("EGP");
                                        break;
                                    case MIB_IPPROTO_GGP:
                                        lst->push_back("GGP");
                                        break;
                                    case MIB_IPPROTO_HELLO:
                                        lst->push_back("Protocole Hello");
                                        break;
                                    case MIB_IPPROTO_RIP:
                                        lst->push_back("RIP");
                                        break;
                                    case MIB_IPPROTO_IS_IS:
                                        lst->push_back("IS-IS");
                                        break;
                                    case MIB_IPPROTO_ES_IS:
                                        lst->push_back("ES-IS");
                                        break;
                                    case MIB_IPPROTO_CISCO:
                                        lst->push_back("Cisco IGRP");
                                        break;
                                    case MIB_IPPROTO_BBN:
                                        lst->push_back("BBN IGP + SPF");
                                        break;
                                    case MIB_IPPROTO_OSPF:
                                        lst->push_back("OSPF");
                                        break;
                                    case MIB_IPPROTO_BGP:
                                        lst->push_back("BGP");
                                        break;
                                    case MIB_IPPROTO_NT_AUTOSTATIC:
                                        lst->push_back("Route Windows auto statique");
                                        break;
                                    case MIB_IPPROTO_NT_STATIC:
                                        lst->push_back("Route Windows statique");
                                        break;
                                    case MIB_IPPROTO_NT_STATIC_NON_DOD:
                                        lst->push_back("Route Windows statique non basée sur les standards d'internet");
                                        break;
                                    default:
                                        printf("Inconnu");
                                        break;
                                    }

            lst->push_back(QString::number(pIpForwardTable->table[i].dwForwardMetric1));
            lst->push_back(QString::number(pIpForwardTable->table[i].dwForwardAge));

            _ROUTING_DATA_->append(*lst);
        }

    }

    return _ROUTING_DATA_;
}

void Win::_init_routing_table()
{

    _ROUTING_TABLE_ = new QWidget();
    _ROUTING_TABLE_->setWindowTitle("Table de routage");
    QDesktopWidget dw;
    _ROUTING_TABLE_->setFixedSize(1300,500);

        QVBoxLayout *_ROUTING_TABLE_VBOX_ = new QVBoxLayout();
        _ROUTING_TABLE_->setLayout(_ROUTING_TABLE_VBOX_);
        _ROUTING_VIEW_ = new QTableView();
        _ROUTING_VIEW_->resizeColumnsToContents();
        _ROUTING_TABLE_VBOX_->addWidget(_ROUTING_VIEW_);
                _ROUTING_MODEL_ = new Routing_TableModel(*_ROUTING_TABLE_RETRIEVED_);
                    _ROUTING_VIEW_->setModel(_ROUTING_MODEL_);
                    _ROUTING_VIEW_->setColumnWidth(0, 150);
                    _ROUTING_VIEW_->setColumnWidth(1, 150);
                    _ROUTING_VIEW_->setColumnWidth(2, 150);
                    _ROUTING_VIEW_->setColumnWidth(3, 40);
                    _ROUTING_VIEW_->setColumnWidth(4, 150);
                    _ROUTING_VIEW_->resizeColumnToContents(5);
                    _ROUTING_VIEW_->setColumnWidth(6, 150);
                    _ROUTING_VIEW_->setColumnWidth(7, 150);

                    for(int i = 0 ; i < _ROUTING_MODEL_->rowCount() ; i++)
                    {
                        _ROUTING_VIEW_->setRowHeight(i,1);
                    }

}
