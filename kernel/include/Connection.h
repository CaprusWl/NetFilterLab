//
// Created by caprus on 2020/11/16.
//

#ifndef NETFIREWALL_CONNECTION_H
#define NETFIREWALL_CONNECTION_H

#include "Datagram.h"

struct Connection {
    unsigned int sourceAddr;
    int sourcePort;
    unsigned int destAddr;
    int destPort;
    int proto;
};

typedef struct Connection *ConnectionPtr;

void convertDatagramToConnection(ConnectionPtr connectionPtr, DatagramPtr datagramPtr);

void clearConnection(void);

// return true if succeed
char establishConnection(DatagramPtr datagramPtr);

// return the pointer of the removed connection
ConnectionPtr removeConnection(ConnectionPtr connectionPtr);

char matchConnection(DatagramPtr datagramPtr);

char isExist(ConnectionPtr connectionPtr);

#endif //NETFIREWALL_CONNECTION_H
