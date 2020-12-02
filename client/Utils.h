//
// Created by caprus on 2020/11/26.
//

#ifndef NETFIREWALL_UTILS_H
#define NETFIREWALL_UTILS_H

unsigned int parseIPAddrFromStr(char *str);

char *parseIPAddrToStr(unsigned int ipAddr);

char *parseIPProtoStr(int protoType);

int parseStrToIPProto(char *str);

#endif //NETFIREWALL_UTILS_H
