//
// Created by caprus on 2020/11/26.
//

#include "../include/Utils.h"

#include <linux/kernel.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/string.h>

unsigned int parseIPAddrFromStr(char* str) {
    if (strcmp(str, "0") == 0) {
        return 0;
    }
    int a, b, c, d;
    char addr[4];
    sscanf(str, "%d.%d.%d.%d", &a, &b, &c, &d);
    addr[0] = a, addr[1] = b, addr[2] = c, addr[3] = d;
    return *(unsigned int*)addr;
}

char* parseIPAddrToStr(unsigned int ipAddr) {
    if (ipAddr == 0) {
        return "0";
    }
    unsigned char a, b, c, d;
    d = ipAddr;
    c = ipAddr >> 8;
    b = ipAddr >> 16;
    a = ipAddr >> 24;

    char* str = kmalloc(sizeof(char) * 16, GFP_USER);
    sprintf(str, "%d.%d.%d.%d", d, c, b, a);

    return str;
}

char* parseIPProtoStr(int protoType) {
    char* protoStr = kmalloc(sizeof(char) * 10, GFP_USER);
    switch (protoType) {
        case IPPROTO_TCP:
            strcpy(protoStr, "tcp");
            break;
        case IPPROTO_UDP:
            strcpy(protoStr, "udp");
            break;
        case -1:
            strcpy(protoStr, "any");
            break;
        default:
            strcpy(protoStr, "undefined");
            break;
    }

    return protoStr;
}

int parseStrToIPProto(char *str) {
    if (strcmp(str, "tcp") == 0) {
        return IPPROTO_TCP;
    } else if (strcmp(str, "udp") == 0) {
        return IPPROTO_UDP;
    } else if (strcmp(str, "any") == 0) {
        return -1;
    } else {
        return -2;
    }
}
