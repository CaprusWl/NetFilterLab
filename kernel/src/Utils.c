//
// Created by caprus on 2020/11/26.
//

#include "../include/Utils.h"

#include <linux/kernel.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>

unsigned int parseIPAddrFromStr(char* str) {
    int a, b, c, d;
    char addr[4];
    sscanf(str, "%d.%d.%d.%d", &a, &b, &c, &d);
    addr[0] = a, addr[1] = b, addr[2] = c, addr[3] = d;
    return *(unsigned int*)addr;
}

char* parseIPAddrToStr(unsigned int ipAddr) {
    unsigned char a, b, c, d;
    d = ipAddr;
    c = ipAddr >> 8;
    b = ipAddr >> 16;
    a = ipAddr >> 24;

    char* str = kmalloc(sizeof(char) * 16, GFP_USER);
    sprintf(str, "%d.%d.%d.%d", a, b, c, d);

    return str;
}

char* parseIPProtoStr(int protoType) {
    char* protoStr = kmalloc(sizeof(char) * 10, GFP_USER);
    switch (protoType) {
        case IPPROTO_TCP:
            protoStr = "tcp";
            break;
        case IPPROTO_UDP:
            protoStr = "udp";
            break;
        default:
            protoStr = "undefined";
            break;
    }

    return protoStr;
}
