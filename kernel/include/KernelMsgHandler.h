#ifndef KERNEL_MSG_HANDLER_H
#define KERNEL_MSG_HANDLER_H

#include <net/sock.h>
#include <linux/netlink.h>

#define NETLINK_NET_FIRE_WALL 17

int sendToUser(char *info, int pid);
void recvFromUser(struct sk_buff *skb);

#endif

