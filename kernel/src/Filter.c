//
// Created by caprus on 2020/11/23.
//

#include "../include/Filter.h"
#include "../include/Logger.h"
#include "../include/Datagram.h"
#include "../include/Utils.h"
#include "../include/Connection.h"

#include <linux/kernel.h>
#include <linux/skbuff.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/tcp.h>

FilterPtr preRoutingFilters[100];
int preRoutingFilterSize = 0;

FilterPtr localInFilters[100];
int localInFilterSize = 0;

FilterPtr forwardFilters[100];
int forwardFilterSize = 0;

FilterPtr localOutFilters[100];
int localOutFilterSize = 0;

FilterPtr postRoutingFilters[100];
int postRoutingFilterSize = 0;

FilterPtr *getFilterByType(int type) {
    FilterPtr *targetFilters;
    switch (type) {
        case HOOKTYPE_PRE_ROUTING:
            targetFilters = preRoutingFilters;
            break;
        case HOOKTYPE_LOCAL_IN:
            targetFilters = localInFilters;
            break;
        case HOOKTYPE_FORWARD:
            targetFilters = forwardFilters;
            break;
        case HOOKTYPE_LOCAL_OUT:
            targetFilters = localOutFilters;
            break;
        case HOOKTYPE_POST_ROUTING:
            targetFilters = postRoutingFilters;
            break;
        default:
            targetFilters = 0;
            break;
    }

    return targetFilters;
}

int getFilterSizeByType(int type) {
    int targetSize = 0;
    switch (type) {
        case HOOKTYPE_PRE_ROUTING:
            targetSize = preRoutingFilterSize;
            break;
        case HOOKTYPE_LOCAL_IN:
            targetSize = localInFilterSize;
            break;
        case HOOKTYPE_FORWARD:
            targetSize = forwardFilterSize;
            break;
        case HOOKTYPE_LOCAL_OUT:
            targetSize = localOutFilterSize;
            break;
        case HOOKTYPE_POST_ROUTING:
            targetSize = postRoutingFilterSize;
            break;
        default:
            targetSize = 0;
            break;
    }

    return targetSize;
}

void increaseFilterSizeByType(int type) {
    switch (type) {
        case HOOKTYPE_PRE_ROUTING:
            preRoutingFilterSize++;
            break;
        case HOOKTYPE_LOCAL_IN:
            localInFilterSize++;
            break;
        case HOOKTYPE_FORWARD:
            forwardFilterSize++;
            break;
        case HOOKTYPE_LOCAL_OUT:
            localOutFilterSize++;
            break;
        case HOOKTYPE_POST_ROUTING:
            postRoutingFilterSize++;
            break;
        default:
            break;
    }
}

void addFilter(int type, FilterPtr filterPtr) {
    FilterPtr* filters = getFilterByType(type);
    if (filters == 0) {
        loge("addFilter", "target filter is null");
        return;
    }
    int filterSize = getFilterSizeByType(type);
    for (; filterSize >= 0; filterSize--) {
        filters[filterSize + 1] = filters[filterSize];
    }
    filters[0] = filterPtr;
    increaseFilterSizeByType(type);
    clearConnection();
    logd("addFilter", "add successfully");
}

char isAny(char* str) {
    if (str == 0) {
        return 0;
    }

    return strcmp(str, "any") == 0;
}

char matchFilter(FilterPtr filterPtr, DatagramPtr datagramPtr) {
    if (!datagramPtr || !filterPtr) {
        return 0;
    }

    // 1. match interface
    if (!isAny(filterPtr->interface) && (datagramPtr->state->out != 0) && (strcmp(datagramPtr->state->out->name, filterPtr->interface) == 0)) {
        return 0;
    }

    // 2. match source ip addr
    struct iphdr* ipHead = ip_hdr(datagramPtr->skb);
    if (filterPtr->sourceAddr != 0 && ipHead->saddr != filterPtr->sourceAddr) {
        return 0;
    }

    // 3. match destination ip addr
    if (filterPtr->destAddr != 0 && ipHead->daddr != filterPtr->destAddr) {
        return 0;
    }

    // 4. match proto
    if (filterPtr->proto != -1 && filterPtr->proto != ipHead->protocol) {
        return 0;
    }

    // 5. match source and destination port
    struct tcphdr *tcpHead;
    tcpHead = (void *) ipHead + ipHead->ihl * 4;
    if (filterPtr->sourcePort != 0 && filterPtr->sourcePort != tcpHead->source) {
        return 0;
    }
    if (filterPtr->destPort != 0 && filterPtr->destPort != tcpHead->dest) {
        return 0;
    }

    return 1;
}

// return 1 if datagram is permitted
char filterDatagram(int type, DatagramPtr datagramPtr) {
    int resCode = 1;

    FilterPtr* filters = getFilterByType(type);
    int size = getFilterSizeByType(type);
    int i;
    for (i = 0; i < size; i++) {
        if (matchFilter(filters[i], datagramPtr)) {
            if (filters[i]->permit) {
                resCode = 1;
            } else {
                resCode = 0;
            }

            printk("match success: resCode: %d\n", resCode);

            break;
        }
    }

    if (resCode) {
        establishConnection(datagramPtr);
    }
    return resCode;
}
