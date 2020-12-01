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

void datagramToString(DatagramPtr datagramPtr, char* destStr);

// check if the datagram is going to establish connection
char isFirstDatagram(DatagramPtr datagramPtr);

#endif //NETFIREWALL_DATAGRAM_H
