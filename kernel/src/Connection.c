//
// Created by caprus on 2020/11/16.
//

#include "../include/Connection.h"
#include "../include/Datagram.h"

#include <linux/kernel.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>

ConnectionPtr connections[500];
int connectionSize = 0;

void convertDatagramToConnection(ConnectionPtr connectionPtr, DatagramPtr datagramPtr) {
    struct iphdr *ipHead = ip_hdr(datagramPtr->skb);
    connectionPtr->sourceAddr = ipHead->saddr;
    connectionPtr->destAddr = ipHead->daddr;

    if (ipHead->protocol == IPPROTO_TCP) {
        struct tcphdr *tcpHead = (void *) ipHead + ipHead->ihl * 4;
        connectionPtr->sourcePort = tcpHead->source;
        connectionPtr->destPort = tcpHead->dest;
    } else if (ipHead->protocol == IPPROTO_UDP) {
        struct udphdr *udpHead = (void *) ipHead + ipHead->ihl * 4;
        connectionPtr->sourcePort = udpHead->source;
        connectionPtr->sourcePort = udpHead->dest;
    }
}

// return true if succeed
char establishConnection(DatagramPtr datagramPtr) {
    ConnectionPtr connectionPtr = (ConnectionPtr) kmalloc(sizeof(struct Connection), GFP_USER);
    if (!connectionPtr) {
        return 0;
    }

    char* tmpStr = (char*) kmalloc(sizeof(char) * 100, GFP_USER);
    datagramToString(datagramPtr, tmpStr);
    printk("establish connection: %s", tmpStr);
    kfree(tmpStr);

    convertDatagramToConnection(connectionPtr, datagramPtr);
    connections[connectionSize++] = connectionPtr;
    return 1;
}

// return the pointer of the removed connection
ConnectionPtr removeConnection(ConnectionPtr connectionPtr) {
    return 0;
}

char isExist(ConnectionPtr connectionPtr) {
    return 0;
}

char equals(ConnectionPtr ptr1, ConnectionPtr ptr2) {
    if (ptr1->sourceAddr == ptr2->sourceAddr &&
        ptr1->destAddr == ptr2->destAddr &&
        ptr1->sourcePort == ptr2->sourcePort &&
        ptr1->destAddr == ptr2->destAddr &&
        ptr1->proto == ptr2->proto) {

        return 1;
    }

    return 0;
}

char matchConnection(DatagramPtr datagramPtr) {
    char resCode = 0;

    ConnectionPtr tmpConnectionPtr = (ConnectionPtr) kmalloc(sizeof(struct Connection), GFP_USER);
    convertDatagramToConnection(tmpConnectionPtr, datagramPtr);
    int i = 0;
    for (i = 0; i < connectionSize; i++) {
        if (equals(tmpConnectionPtr, connections[i])) {
            resCode = 1;
        }
    }

    kfree(tmpConnectionPtr);
    return resCode;
}
