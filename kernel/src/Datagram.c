//
// Created by caprus on 2020/11/23.
//

#include "../include/Datagram.h"
#include "../include/Utils.h"

#include <linux/string.h>
#include <linux/kernel.h>
#include <linux/ip.h>

void datagramToString(DatagramPtr datagramPtr, char* destStr) {
    struct iphdr* ipHead = ip_hdr(datagramPtr->skb);

    char* sip = parseIPAddrToStr(ipHead->saddr);
    char* dip = parseIPAddrToStr(ipHead->daddr);
    char* protoStr = parseIPProtoStr(ipHead->protocol);

    sprintf(destStr, "DatagramInfo: sip: %s, dip: %s, proto: %s\n", sip, dip, protoStr);
}

char isFirstDatagram(DatagramPtr datagramPtr) {
    return 1;
}
