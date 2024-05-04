#ifndef UNKNOWNUTILS_H
#define UNKNOWNUTILS_H

#include "pcap.h"
#include <winsock.h>
#include <iostream>
#define DEV_BUFFER 256
#include <QString>
#include <vector>

char* iptos(u_long);
int ret_dev_list_by_winsock(QString);
QString gethostname();


#endif // UNKNOWNUTILS_H
