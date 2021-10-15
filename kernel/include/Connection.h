//
// Created by caprus on 2020/11/16.
//

#ifndef NETFIREWALL_CONNECTION_H
#define NETFIREWALL_CONNECTION_H

#include "Datagram.h"

struct Connection {
    unsigned int sourceAddr;    // 源ip
    int sourcePort;             // 源端口
    unsigned int destAddr;      // 目的ip
    int destPort;               // 目的端口
    int proto;                  // 协议
};

typedef struct Connection *ConnectionPtr;

void convertDatagramToConnection(ConnectionPtr connectionPtr, DatagramPtr datagramPtr);

// 清空连接表
void clearConnection(void);

// 建立连接，返回'1'表示建立成功
char establishConnection(DatagramPtr datagramPtr);

// 在连接表中匹配报文，返回'1'表示匹配成功
char matchConnection(DatagramPtr datagramPtr);

#endif //NETFIREWALL_CONNECTION_H
