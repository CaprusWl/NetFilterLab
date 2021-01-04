//
// Created by caprus on 2020/11/23.
//

#include "../include/Datagram.h"
#include "../include/Utils.h"
#include "../include/Logger.h"

#include <linux/string.h>
#include <linux/kernel.h>
#include <linux/ip.h>
#include <linux/tcp.h>

void printDatagramInfo(DatagramPtr datagramPtr, char *context) {
    char infoStr[100];

    struct iphdr* ipHead = ip_hdr(datagramPtr->skb);

    char* sip = parseIPAddrToStr(ipHead->saddr);
    char* dip = parseIPAddrToStr(ipHead->daddr);
    char* protoStr = parseIPProtoStr(ipHead->protocol);

    struct tcphdr *tcpHead = (void *) ipHead + ipHead->ihl * 4;
    int sport = tcpHead->source;
    int dport = tcpHead->dest;

    sprintf(infoStr, "DatagramInfo: sip: %s, dip: %s, sport: %d, dport:%d, proto: %s\n", sip, dip, sport, dport, protoStr);
    logd(context, infoStr);
}

char isFirstDatagram(DatagramPtr datagramPtr) {
    struct iphdr *ipHead = ip_hdr(datagramPtr->skb);
    if (ipHead->protocol == IPPROTO_TCP) {
        struct tcphdr *tcpHead = (void *) ipHead + ipHead->ihl * 4;
        return tcpHead->syn;
    }

    return 1;
}
