#include "UnknownUtils.h"
#define IPTOSBUFFERS    12
#include "iphlpapi.h"

using namespace std;

char *iptos(u_long in)
{
    static char output[IPTOSBUFFERS][3*4+3+1];
    static short which;
    u_char *p;

    p = (u_char *)&in;
    which = (which + 1 == IPTOSBUFFERS ? 0 : which + 1);
    _snprintf_s(output[which], sizeof(output[which]), sizeof(output[which]),"%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
    return output[which];
}

QString gethostname()
{
    char ac[255] = "Hostname";
    if (gethostname(ac, sizeof(ac)) == SOCKET_ERROR) {
        cerr << "Error " << WSAGetLastError() <<
                " when getting local host name." << endl;
    }

    return (QString)ac;
}

int ret_dev_list_by_winsock(QString ip_addr)
{
    char ac[80];

    if (gethostname(ac, sizeof(ac)) == SOCKET_ERROR) {
        cerr << "Error " << WSAGetLastError() <<
                " when getting local host name." << endl;
        return 1;
    }

    struct hostent *phe = gethostbyname(ac);
    if (phe == 0) {
        cerr << "Yow! Bad host lookup." << endl;
        return 1;
    }

    for (int i = 0; phe->h_addr_list[i] != 0; ++i) {
        struct in_addr addr;
        memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
        cout << inet_ntoa(addr) << endl;
        if(ip_addr == inet_ntoa(addr))
        {
            return 1;
        }
    }


    WSAData wsaData;
    if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
        return 255;
    }

    return 0;
}
