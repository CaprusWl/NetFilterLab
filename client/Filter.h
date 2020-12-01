//
// Created by caprus on 2020/11/23.
//

#ifndef NETFIREWALL_FILTER_H
#define NETFIREWALL_FILTER_H

struct Filter {
    unsigned int sourceAddr;
    int sourcePort;
    unsigned int destAddr;
    int destPort;
    char interface[20];
    char permit;
};

typedef struct Filter* FilterPtr;

#endif //NETFIREWALL_FILTER_H
