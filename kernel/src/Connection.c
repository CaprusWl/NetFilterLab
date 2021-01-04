//
// Created by caprus on 2020/11/16.
//

#include "../include/Connection.h"
#include "../include/Datagram.h"

#include <linux/kernel.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>

#define MAX_HASH_SIZE 0x7fffff
#define MAX_KEY_SIZE 31

ConnectionPtr connections[MAX_KEY_SIZE][500];
int connectionSize[MAX_KEY_SIZE];
int totalConnectionSize = 0;

int hashCode(ConnectionPtr connectionPtr);
char equals(ConnectionPtr ptr1, ConnectionPtr ptr2);

void convertDatagramToConnection(ConnectionPtr connectionPtr, DatagramPtr datagramPtr) {
    struct iphdr *ipHead = ip_hdr(datagramPtr->skb);
    connectionPtr->sourceAddr = ipHead->saddr;
    connectionPtr->destAddr = ipHead->daddr;

    struct tcphdr *tcpHead = (void *) ipHead + ipHead->ihl * 4;
    connectionPtr->sourcePort = tcpHead->source;
    connectionPtr->destPort = tcpHead->dest;

    if (ipHead->protocol == IPPROTO_TCP) {
        connectionPtr->proto = IPPROTO_TCP;
    } else if (ipHead->protocol == IPPROTO_UDP) {
        connectionPtr->proto = IPPROTO_UDP;
    }
}

// return true if succeed
char establishConnection(DatagramPtr datagramPtr) {
    ConnectionPtr connectionPtr = (ConnectionPtr) kmalloc(sizeof(struct Connection), GFP_USER);
    if (!connectionPtr) {
        return 0;
    }

    convertDatagramToConnection(connectionPtr, datagramPtr);

    int key = hashCode(connectionPtr) % MAX_KEY_SIZE;
    connections[key][connectionSize[key]] = connectionPtr;
    connectionSize[key]++;
    totalConnectionSize++;
    return 1;
}

void clearConnection(void) {
    int i;
    for (i = 0; i < MAX_KEY_SIZE; i++) {
        connectionSize[i] = 0;
    }
}

// return the pointer of the removed connection
ConnectionPtr removeConnection(ConnectionPtr connectionPtr) {
    return 0;
}

// return true if is same connection
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

// return hash code of a connection
int hashCode(ConnectionPtr ptr) {
    int hashCode = 0;
    hashCode += (33 * hashCode + (ptr->sourceAddr % MAX_HASH_SIZE)) % MAX_HASH_SIZE;
    hashCode += (33 * hashCode + (ptr->sourcePort % MAX_HASH_SIZE)) % MAX_HASH_SIZE;
    hashCode += (33 * hashCode + (ptr->destAddr % MAX_HASH_SIZE)) % MAX_HASH_SIZE;
    hashCode += (33 * hashCode + (ptr->destPort % MAX_HASH_SIZE)) % MAX_HASH_SIZE;
    hashCode += (33 * hashCode + (ptr->proto % MAX_HASH_SIZE)) % MAX_HASH_SIZE;

    return hashCode;
}

// match connection with hash table
char matchConnection(DatagramPtr datagramPtr) {
    char resCode = 0;

    struct Connection connection;
    convertDatagramToConnection(&connection, datagramPtr);

    int key = hashCode(&connection) % MAX_KEY_SIZE;

    int i;
    for (i = 0; i < connectionSize[key]; i++) {
        if (equals(&connection, connections[key][i])) {
            resCode = 1;
        }
    }

    return resCode;
}
