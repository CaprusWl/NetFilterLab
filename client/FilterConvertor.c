//
// Created by caprus on 2020/12/2.
//

#include "Utils.h"
#include "FilterConvertor.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int readAsInt(char* str);

FilterPtr convertStrToFilter(char *str) {
    FilterPtr filterPtr = (FilterPtr) malloc(sizeof(struct Filter));
    if (!str) {
        return filterPtr;
    }

    int p;
    char c;

    char fieldName[20];
    int fieldNameIndex;
    char fieldValue[20];
    int fieldValueIndex;
    for (p = 0, c = str[0]; c != '\0'; c = str[++p]) {
        fieldNameIndex = 0;
        for (c = str[p]; c != ':'; c = str[++p]) {
            fieldName[fieldNameIndex++] = c;
        }
        fieldName[fieldNameIndex] = '\0';

        // skip the ':' and space
        p += 2;

        fieldValueIndex = 0;
        for (c = str[p]; c != ',' && c != '\0'; c = str[++p]) {
            fieldValue[fieldValueIndex++] = c;
        }
        fieldValue[fieldValueIndex] = '\0';

        // skip the space
        p += 1;

        if (strcmp(fieldName, "sip") == 0) {
            filterPtr->sourceAddr = parseIPAddrFromStr(fieldValue);
        } else if (strcmp(fieldName, "dip") == 0) {
            filterPtr->destAddr = parseIPAddrFromStr(fieldValue);
        } else if (strcmp(fieldName, "sport") == 0) {
            filterPtr->sourcePort = readAsInt(fieldValue);
        } else if (strcmp(fieldName, "dport") == 0) {
            filterPtr->destPort = readAsInt(fieldValue);
        } else if (strcmp(fieldName, "proto") == 0) {
            filterPtr->proto = parseStrToIPProto(fieldValue);
        } else if (strcmp(fieldName, "interface") == 0) {
            strcpy(filterPtr->interface, fieldValue);
        } else if (strcmp(fieldName, "permit") == 0) {
            filterPtr->permit = readAsInt(fieldValue);
        }
    }

    printf("deserialize: %s", convertFilterToString(filterPtr));

    return filterPtr;
}

int readAsInt(char* str) {
    int p = 0;
    int res;
    for (; str[p] != '\0'; p++) {
        res *= 10;
        res += str[p] - '0';
    }

    return res;
}

char *convertFilterToString(FilterPtr filterPtr) {
    char *filterStr = (char *) malloc(sizeof(char) * 100);
    sprintf(
            filterStr,
            "sip: %s, dip: %s, sport: %d, dport: %d, interface: %s, proto: %s, permit: %d",
            parseIPAddrToStr(filterPtr->sourceAddr),
            parseIPAddrToStr(filterPtr->destAddr),
            filterPtr->sourcePort,
            filterPtr->destPort,
            filterPtr->interface,
            parseIPProtoStr(filterPtr->proto),
            filterPtr->permit
    );

    printf("serialize: %s\n", filterStr);

    return filterStr;
}
