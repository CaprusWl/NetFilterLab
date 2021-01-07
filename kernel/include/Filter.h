//
// Created by caprus on 2020/11/23.
//

#ifndef NETFIREWALL_FILTER_H
#define NETFIREWALL_FILTER_H

// proto type
#define PROTOTYPE_TCP 0
#define PROTOTYPE_UDP 1
#define PROTOTYPE_ICMP 2

// hook entrance type
#define HOOKTYPE_PRE_ROUTING 0
#define HOOKTYPE_LOCAL_IN 1
#define HOOKTYPE_FORWARD 2
#define HOOKTYPE_LOCAL_OUT 3
#define HOOKTYPE_POST_ROUTING 4

#include "Datagram.h"

struct Filter {
    unsigned int sourceAddr;
    int sourcePort;
    unsigned int destAddr;
    int destPort;
    char interface[20];
    int proto;
    char permit;
};

typedef struct Filter* FilterPtr;

// add a filter by client
void addFilter(int type, FilterPtr filterPtr);

// return true if datagram is permitted
char filterDatagram(int type, DatagramPtr datagramPtr);

void removeFilter(int type, int index);

#endif //NETFIREWALL_FILTER_H
