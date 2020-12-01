#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <linux/netlink.h>
#include <sys/types.h>
#include <unistd.h>

#include "Filter.h"
#include "FilterConvertor.h"

#define NETLINK_NET_FIRE_WALL 17
#define MSG_LEN	256

void sendMessageToKernel(char* data);
void setCustomFilter();
void printFilterTable();
unsigned int parseIPAddrFromStr(char* str);

char *default_data = "Netlink Test Default Data";

struct FilterMsg {
	struct nlmsghdr hdr;
	char data[MSG_LEN];
};

struct u_packet_info {
	struct nlmsghdr hdr;
	char msg[MSG_LEN];
};

void setCustomFilter() {
    struct Filter filter;
    char addr[20];

    printf("\nset source ip (0 for any): ");
    scanf("%s", addr);
    filter.sourceAddr = parseIPAddrFromStr(addr);

    printf("\nset source port (0 for any): ");
    scanf("%d", &(filter.sourcePort));

    printf("\nset destination ip (0 for any): ");
    scanf("%s", addr);
    filter.destAddr = parseIPAddrFromStr(addr);

    printf("\nset destination port (0 for any): ");
    scanf("%d", &(filter.destPort));

    printf("\nset permit (1 for permit, 0 for deny): ");
    scanf("%d", &(filter.permit));

    sendMessageToKernel(convertFilterToString(&filter));
}

int main()
{
    printf("Welcome to use NetFireWall\n");
    printf("Please make your choice: (1) set a filter (2) print filter table (3) exit\n");
    int choice = 0;
    scanf("%d", &choice);
    while (choice != 3) {
        if (choice == 1) {
            setCustomFilter();
        } else if (choice == 2) {
            printFilterTable();
        } else {
            printf("Not support\n");
        }

        printf("Please make your choice: (1) set a filter (2) print filter table (3) exit\n");
        scanf("%d", &choice);
    }
	return 0;
}

void printFilterTable() {
}

void sendMessageToKernel(char* data) {
    int dlen;
    struct sockaddr_nl local;
    struct sockaddr_nl kpeer;
    int skfd, ret, kpeerlen = sizeof(struct sockaddr_nl);
    struct nlmsghdr *message;
    struct u_packet_info info;
    char *retval;

    dlen = strlen(data) + 1;

    skfd = socket(PF_NETLINK, SOCK_RAW, NETLINK_NET_FIRE_WALL);
    if (skfd < 0) {
        printf("can not create a netlink socket\n");
        return;
    }

    memset(&local, 0, sizeof(local));
    local.nl_family = AF_NETLINK;
    local.nl_pid = getpid();
    local.nl_groups = 0;
    if (bind(skfd, (struct sockaddr *) &local, sizeof(local)) != 0) {
        printf("bind() error\n");
        return;
    }
    memset(&kpeer, 0, sizeof(kpeer));
    kpeer.nl_family = AF_NETLINK;
    kpeer.nl_pid = 0;
    kpeer.nl_groups = 0;

    message = (struct nlmsghdr *) malloc(sizeof(struct FilterMsg));
    if (message == NULL) {
        printf("malloc() error\n");
        return;
    }

    memset(message, '\0', sizeof(struct nlmsghdr));
    message->nlmsg_len = NLMSG_SPACE(dlen);
    message->nlmsg_flags = 0;
    message->nlmsg_type = 0;
    message->nlmsg_seq = 0;
    message->nlmsg_pid = local.nl_pid;

    retval = memcpy(NLMSG_DATA(message), data, strlen(data));

    printf("message sendto kernel, content: '%s', len: %d\n", (char *) NLMSG_DATA(message), message->nlmsg_len);
    ret = sendto(skfd, message, message->nlmsg_len, 0, (struct sockaddr *) &kpeer, sizeof(kpeer));
    if (!ret) {
        perror("sendto:");
        exit(-1);
    }

    ret = recvfrom(skfd, &info, sizeof(struct u_packet_info), 0, (struct sockaddr *) &kpeer, &kpeerlen);
    if (!ret) {
        perror("recvfrom:");
        exit(-1);
    }

    printf("message recvfrom kernel, content: '%s'\n", (char *) info.msg);

    close(skfd);
}

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
