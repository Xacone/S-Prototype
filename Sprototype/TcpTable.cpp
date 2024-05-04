#include "MainWin.h"
#include <WS2tcpip.h>
#include "iphlpapi.h"
#include "TcpTableModel.h"
#include <iostream>

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

using namespace std;

QList<QStringList>* _TCP_DATA_;

QList<QStringList>* tcp_list()
{
    if(_TCP_DATA_ != NULL)
    {

    delete _TCP_DATA_;

    _TCP_DATA_ = new QList<QStringList>;
    DWORD dwSize = 0;
    DWORD dwRetVal = 0;
    char szLocalAddr[128];
    char szRemoteAddr[128];

    PMIB_TCPTABLE pTcpTable;
    struct in_addr IpAddr;

    int i;

    pTcpTable = (MIB_TCPTABLE*)MALLOC(sizeof(MIB_TCPTABLE));
    if (pTcpTable == NULL) {
        cout << "Error allocating memory\n" << endl;
        exit(-1); // TO ERR WIN !!
    }

    dwSize = sizeof(MIB_TCPTABLE);
        // Make an initial call to GetTcpTable to
        // get the necessary size into the dwSize variable
    if ((dwRetVal = GetTcpTable(pTcpTable, &dwSize, TRUE)) == ERROR_INSUFFICIENT_BUFFER) {
            FREE(pTcpTable);
            pTcpTable = (MIB_TCPTABLE*)MALLOC(dwSize);
            if (pTcpTable == NULL) {
                cout << "Error allocating memory\n" << endl;
                exit(-1); // TO ERR WIN !!
            }
    }


    if ((dwRetVal = GetTcpTable(pTcpTable, &dwSize, TRUE)) == NO_ERROR) {
            //cout  << "\tNumber of entries for TcpTable: %d\n" << (int)pTcpTable->dwNumEntries << endl;
            for (i = 0; i < (int)pTcpTable->dwNumEntries; i++) {
                QStringList *lst = new QStringList();
                IpAddr.S_un.S_addr = (u_long)pTcpTable->table[i].dwLocalAddr;
                strcpy_s(szLocalAddr, sizeof(szLocalAddr), inet_ntoa(IpAddr));
                IpAddr.S_un.S_addr = (u_long)pTcpTable->table[i].dwRemoteAddr;
                strcpy_s(szRemoteAddr, sizeof(szRemoteAddr), inet_ntoa(IpAddr));

                lst->push_back(szLocalAddr);
                lst->push_back(QString::number(ubs((u_short)pTcpTable->table[i].dwLocalPort)));
                lst->push_back(szRemoteAddr);
                lst->push_back(QString::number(ubs((u_short)pTcpTable->table[i].dwRemotePort)));


                switch (pTcpTable->table[i].dwState) {
                case MIB_TCP_STATE_CLOSED:
                    lst->push_back("CLOSED");
                    break;
                case MIB_TCP_STATE_LISTEN:
                    lst->push_back("LISTEN");
                    break;
                case MIB_TCP_STATE_SYN_SENT:
                    lst->push_back("SYN-SENT");
                    break;
                case MIB_TCP_STATE_SYN_RCVD:
                    lst->push_back("SYN-RECEIVED");
                    break;
                case MIB_TCP_STATE_ESTAB:
                    lst->push_back("ESTABLISHED");
                    break;
                case MIB_TCP_STATE_FIN_WAIT1:
                    lst->push_back("FIN-WAIT-1");
                    break;
                case MIB_TCP_STATE_FIN_WAIT2:
                    lst->push_back("FIN-WAIT-2 ");
                    break;
                case MIB_TCP_STATE_CLOSE_WAIT:
                    lst->push_back("CLOSE-WAIT");
                    break;
                case MIB_TCP_STATE_CLOSING:
                    lst->push_back("CLOSING");
                    break;
                case MIB_TCP_STATE_LAST_ACK:
                    lst->push_back("LAST-ACK");
                    break;
                case MIB_TCP_STATE_TIME_WAIT:
                    lst->push_back("TIME-WAIT");
                    break;
                case MIB_TCP_STATE_DELETE_TCB:
                    lst->push_back("DELETE-TCB");
                    break;
                default:
                    lst->push_back("UNKNOWN dwState value");
                    break;
                }

                _TCP_DATA_->append(*lst);
            }
        }
        else {
            printf("\tGetTcpTable failed with %d\n", dwRetVal);
            FREE(pTcpTable);
            exit(-1); // TO WIN ERR !!
        }


    if (pTcpTable != NULL) {
         FREE(pTcpTable);
         pTcpTable = NULL;
     }

    }

    return _TCP_DATA_;
}


void Win::_init_tcp_table()
{
    _TCP_TABLE_ = new QWidget();
        _TCP_TABLE_VIEW_ = new QTableView();
        _TCP_TABLE_MODEL_ = new Tcp_TableModel(*_TCP_TABLE_RETRIEVED_);

        QObject::connect(refresher, SIGNAL(here_is_tcp_net_table(QList<QStringList>*)), this, SLOT(refresh_tcp_net_table(QList<QStringList>*)));

        _TCP_TABLE_->setFixedSize(1000,700);

        QVBoxLayout *TCP_TABLE_VBOX = new QVBoxLayout();
        _TCP_TABLE_->setLayout(TCP_TABLE_VBOX);
        TCP_TABLE_VBOX->addWidget(_TCP_TABLE_VIEW_);
        _TCP_TABLE_VIEW_->setModel(_TCP_TABLE_MODEL_);
        _TCP_TABLE_VIEW_->setColumnWidth(0, 250);
        _TCP_TABLE_VIEW_->setColumnWidth(1, 150);
        _TCP_TABLE_VIEW_->setColumnWidth(2, 250);
        _TCP_TABLE_VIEW_->setColumnWidth(3, 150);
        _TCP_TABLE_VIEW_->setColumnWidth(3, 150);

        for(int i = 0 ; i < _TCP_TABLE_MODEL_->rowCount() ; i++)
        {
            _TCP_TABLE_VIEW_->setRowHeight(i,1);
        }

        //qDebug() << *tcp_list();
}


void Win::sh_tcp_sessions(bool p) { Q_UNUSED(p) _TCP_TABLE_->show(); }
