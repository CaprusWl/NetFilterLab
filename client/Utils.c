//
// Created by caprus on 2020/11/26.
//

#include "Utils.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define IPPROTO_TCP 6 /* tcp */
#define IPPROTO_UDP 17 /* user datagram protocol */

unsigned int parseIPAddrFromStr(char *str) {
    if (strcmp(str, "0") == 0) {
        return 0;
    }
    int a, b, c, d;
    char addr[4];
    sscanf(str, "%d.%d.%d.%d", &a, &b, &c, &d);
    addr[0] = a, addr[1] = b, addr[2] = c, addr[3] = d;
    return *(unsigned int *) addr;
}

char *parseIPAddrToStr(unsigned int ipAddr) {
    if (ipAddr == 0) {
        return "0";
    }
    unsigned char a, b, c, d;
    d = ipAddr;
    c = ipAddr >> 8;
    b = ipAddr >> 16;
    a = ipAddr >> 24;

    char *str = (char *) malloc(sizeof(char) * 16);
    sprintf(str, "%d.%d.%d.%d", a, b, c, d);

    return str;
}

char *parseIPProtoStr(int protoType) {
    char *protoStr = (char *) malloc(sizeof(char) * 10);
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
