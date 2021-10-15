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
    unsigned int sourceAddr;    // 源ip
    int sourcePort;             // 源端口
    unsigned int destAddr;      // 目的ip
    int destPort;               // 目的端口
    char interface[20];         // 网卡接口
    int proto;                  // 网络协议
    char permit;                // 是否放行
};

typedef struct Filter* FilterPtr;

// 添加一个规则项
void addFilter(int type, FilterPtr filterPtr);

// 过滤报文，返回'1'表示该报文可以通过
char filterDatagram(int type, DatagramPtr datagramPtr);

// 删除指定规则项
void removeFilter(int type, int index);

#endif //NETFIREWALL_FILTER_H
