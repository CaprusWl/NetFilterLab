#ifndef KERNEL_MSG_HANDLER_H
#define KERNEL_MSG_HANDLER_H

#include <net/sock.h>
#include <linux/netlink.h>

#define NETLINK_NET_FIRE_WALL 17

// 发送消息给用户进程
int sendToUser(char *info, int pid);

// 从用户进程接受消息
void recvFromUser(struct sk_buff *skb);

#endif

