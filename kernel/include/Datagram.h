//
// Created by caprus on 2020/11/23.
//

#ifndef NETFIREWALL_DATAGRAM_H
#define NETFIREWALL_DATAGRAM_H

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/sched.h>
#include <net/sock.h>
#include <linux/netlink.h>
#include <linux/skbuff.h>

struct Datagram {
    struct sk_buff *skb;
    const struct nf_hook_state *state;
};

typedef struct Datagram *DatagramPtr;

// 打印报文信息
void printDatagramInfo(DatagramPtr datagramPtr, char* context);

// 是否是建立连接的报文，返回'1'表示是
char isFirstDatagram(DatagramPtr datagramPtr);

#endif //NETFIREWALL_DATAGRAM_H
