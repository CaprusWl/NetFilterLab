//
// Created by bytedance on 2020/12/2.
//

#ifndef NETFILTERLAB_FILTERCONVERTOR_H
#define NETFILTERLAB_FILTERCONVERTOR_H

#include "Filter.h"

FilterPtr convertStrToFilter(char* str);

char* convertFilterToString(FilterPtr filterPtr);

#endif //NETFILTERLAB_FILTERCONVERTOR_H
