//
// Created by caprus on 2020/12/2.
//

#ifndef NETFILTERLAB_FILTERCONVERTOR_H
#define NETFILTERLAB_FILTERCONVERTOR_H

#include "Filter.h"

// 将字符串反序列化为规则对象
FilterPtr convertStrToFilter(char* str);

// 将规则对象序列化为字符串
char* convertFilterToString(FilterPtr filterPtr);

#endif //NETFILTERLAB_FILTERCONVERTOR_H
